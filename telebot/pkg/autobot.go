package pkg

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

// Pinging bot status.
var ping bool = false

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

func (b *Autobot) Register() (bot *telebot.BotAPI, err error) {
	bot, err = telebot.NewBotAPI(b.Auth)
	bot.Debug = true
	return
}

func (b *Autobot) User() string {
	bot, err := b.Register()
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Println(out)
	}

	userInfo := fmt.Sprintf("User(ID, Name): (%d, %s)", bot.Self.ID, bot.Self.UserName)
	return userInfo
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

func (b *Autobot) HandleMessage(message *telebot.Message) {
	user := message.From
	if user == nil {
		return
	}
	text := message.Text

	// Debugging:
	logger.Tracer.Printf("%s wrote %s", b.User(), text)

	bot, err := b.Register()
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Println(out)
	}

	if strings.HasPrefix(text, "/") {
		err = b.HandleCommand(message.Chat.ID, text)
	} else if ping && len(text) > 0 {
		// NOTE: The `ping` default condition used to prevent duplicate response as sender, from bot.
		msg := telebot.NewMessage(message.Chat.ID, strings.ToUpper(text))
		// To preserve markdown, we attach entities (bold, italic, etc).
		msg.Entities = message.Entities
		_, err = bot.Send(msg)
	} else {
		// This is equivalent to forwarding, but without the sender's name.
		copyMsg := telebot.NewCopyMessage(message.Chat.ID, message.Chat.ID, message.MessageID)
		_, err = bot.CopyMessage(copyMsg)
	}

	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Println(out)
	}
}

func (b *Autobot) HandleButton(query *telebot.CallbackQuery) {
	markup := telebot.NewInlineKeyboardMarkup()
	message := query.Message

	listMenu := craftLayout()
	if query.Data == Next {
		b.Data = SecondMenuTitle
		markup = listMenu[1]
	} else if query.Data == Back {
		b.Data = FirstMenuTitle
		markup = listMenu[0]
	}

	bot, err := b.Register()
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Println(out)
	}
	callbackCfg := telebot.NewCallback(query.ID, "")
	bot.Send(callbackCfg)

	// Replace menu text and keyboard.
	msg := telebot.NewEditMessageTextAndMarkup(message.Chat.ID, message.MessageID, b.Data, markup)
	msg.ParseMode = telebot.ModeHTML
	bot.Send(msg)
}

func (b *Autobot) HandleCommand(chatId int64, command string) error {
	var err error
	switch command {
	case "/ping":
		ping = true
	case "/menu":
		err = b.SendMenu(chatId)
	case "/welcome":
		err = b.ResponseWithText(chatId)
	}
	return err
}

func (b *Autobot) SendMenu(chatId int64) error {
	bot, err := b.Register()
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Println(out)
	}

	listMenu := craftLayout()
	msg := telebot.NewMessage(chatId, FirstMenuTitle)
	msg.ParseMode = telebot.ModeHTML
	msg.ReplyMarkup = listMenu[0]
	_, err = bot.Send(msg)
	return err
}

func (b *Autobot) ResponseWithText(chatId int64) error {
	bot, err := b.Register()
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Println(out)
	}

	msg := telebot.NewMessage(chatId, b.Data)
	_, err = bot.Send(msg)
	return err
}
