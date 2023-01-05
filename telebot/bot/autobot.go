package bot

import (
	"context"
	"fmt"
	"net/url"
	"strings"
	"telebot/logger"

	telebot "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

const (
	// Menu description.
	FirstMenuTitle  string = "<b>Autobot Menu 1</b>\n\nWIZ-Team projects' current status."
	SecondMenuTitle string = "<b>Autobot Menu 2</b>\n\nWIZ-Team projects' current status."

	// Button texts.
	Next     string = "Next"
	Back     string = "Back"
	Github   string = "WIZ's Github"
	Tutorial string = "Tutorial"
)

type Autobot struct {
	Enable bool       // Enable CLI to trigger bot.
	Auth   string     // Basic authentication token for TelegramAPI.
	Data   string     // Data collected from GithubAPI.
	ReqURL []*url.URL // GithubAPI endpoints to request essential data for daily report.
}

func NewAutobot(auth, data string, urls []*url.URL) *Autobot {
	return &Autobot{
		Enable: true,
		Auth:   auth,
		Data:   data,
		ReqURL: urls,
	}
}

func (b *Autobot) Register() *telebot.BotAPI {
	if b.Auth == "" {
		logger.Error.Fatalln("Missing authentication token to activate bot")
	}

	bot, err := telebot.NewBotAPI(b.Auth)
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Print(out)
	}
	bot.Debug = true
	return bot
}

func (b *Autobot) Info() string {
	bot := b.Register()
	botInfo := fmt.Sprintf("WIZ-Bot(ID, Name): (%d, %s)", bot.Self.ID, bot.Self.UserName)
	return botInfo
}

func craftLayout() (markups []telebot.InlineKeyboardMarkup) {
	const TutorialURL string = "https://core.telegram.org/bots/api"
	const GithubURL string = "https://github.com/orgs/WIZ-Innovation/projects"

	// Keyboard layout for the first menu: [two buttons, one per row].
	firstMenuMarkup := telebot.NewInlineKeyboardMarkup(
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonData(Next, Next),
		),
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonURL(Github, GithubURL),
		),
	)

	// Keyboard layout for the second menu: [two buttons, one per row].
	secondMenuMarkup := telebot.NewInlineKeyboardMarkup(
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonData(Back, Back),
		),
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonURL(Tutorial, TutorialURL),
		),
	)

	markups = append(markups, firstMenuMarkup, secondMenuMarkup)
	return
}

func (b *Autobot) ReceiveUpdates(ctx context.Context, updates telebot.UpdatesChannel) {
	for {
		select {
		case <-ctx.Done():
			return
		case update := <-updates:
			b.HandleUpdate(update)
		}
	}
}

func (b *Autobot) HandleUpdate(update telebot.Update) {
	switch {
	case update.Message != nil:
		b.HandleMessage(update.Message)
	case update.CallbackQuery != nil:
		b.HandleButton(update.CallbackQuery)
	}
}

var WizBot *telebot.BotAPI

func (b *Autobot) HandleMessage(message *telebot.Message) {
	user := message.From
	text := message.Text
	if user == nil {
		return
	}

	// Debugging:
	logger.Tracer.Printf("%s, Room: %d", b.Info(), message.Chat.ID)
	logger.Tracer.Printf("%v wrote %s", user, text)

	var err error
	if b.Enable || text == commands[1] {
		if strings.HasPrefix(text, "/") {
			err = b.HandleCommand(message.Chat.ID, text)
		} else if len(text) > 0 {
			nonsense := "Stop writing silly thing like: " + strings.ToUpper(text)
			// To preserve markdown, we attach entities (bold, italic, etc).
			// msg.Entities = message.Entities

			err = b.SendNonsense(message.Chat.ID, nonsense)
		} else {
			// This is equivalent to forwarding, but without the sender's name.
			err = b.ForwardMsg(message.MessageID, message.Chat.ID)
		}
	} else {
		err = b.SendNonsense(message.Chat.ID, "To enable WIZ-Bot, please type: /enable")
	}

	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Print(out)
	}
}

func (b *Autobot) HandleButton(query *telebot.CallbackQuery) {
	markup := telebot.NewInlineKeyboardMarkup()
	message := query.Message

	listMenu := craftLayout()
	var title string
	if query.Data == Next {
		title = SecondMenuTitle
		markup = listMenu[1]
	} else if query.Data == Back {
		title = FirstMenuTitle
		markup = listMenu[0]
	}

	callbackCfg := telebot.NewCallback(query.ID, "")
	WizBot.Send(callbackCfg)

	// Replace menu text and keyboard.
	msg := telebot.NewEditMessageTextAndMarkup(message.Chat.ID, message.MessageID, title, markup)
	msg.ParseMode = telebot.ModeHTML
	WizBot.Send(msg)
}

var commands = []string{
	"/disable",
	"/enable",
	"/help",
	"/menu",
	"/task",
}

func (b *Autobot) HandleCommand(chatId int64, command string) error {
	var err error
	switch command {
	case commands[0]:
		b.Enable = false
	case commands[1]:
		b.Enable = true
	case commands[2]:
		err = b.SendHelp(chatId)
	case commands[3]:
		err = b.SendMenu(chatId)
	case commands[4]:
		err = b.SendFetchedData(chatId)
	}
	return err
}

func (b *Autobot) SendHelp(chatId int64) error {
	var help string = "<b>Available commands: </b>\n\n"
	listCmd := func(cmds []string) string {
		for _, cmd := range cmds {
			help += fmt.Sprintf("%s\n", cmd)
		}
		return help
	}(commands)

	msg := telebot.NewMessage(chatId, listCmd)
	msg.ParseMode = telebot.ModeHTML
	_, err := WizBot.Send(msg)
	return err
}

func (b *Autobot) SendMenu(chatId int64) error {
	listMenu := craftLayout()
	msg := telebot.NewMessage(chatId, FirstMenuTitle)
	msg.ParseMode = telebot.ModeHTML
	msg.ReplyMarkup = listMenu[0]

	_, err := WizBot.Send(msg)
	return err
}

func (b *Autobot) SendFetchedData(chatId int64) error {
	msg := telebot.NewMessage(chatId, b.Data)
	_, err := WizBot.Send(msg)
	return err
}

func (b *Autobot) SendNonsense(chatId int64, nonsense string) error {
	// NOTE: Only available for peer to peer room (1vs1).
	msg := telebot.NewMessage(chatId, nonsense)
	_, err := WizBot.Send(msg)
	return err
}

func (b *Autobot) ForwardMsg(msgId int, chatId int64) error {
	copyMsg := telebot.NewCopyMessage(chatId, chatId, msgId)
	_, err := WizBot.CopyMessage(copyMsg)
	return err
}
