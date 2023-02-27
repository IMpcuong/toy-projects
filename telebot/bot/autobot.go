package bot

import (
	"context"
	"fmt"
	"os"
	"strings"
	"telebot/logger"

	telebot "github.com/go-telegram-bot-api/telegram-bot-api/v5"
	"github.com/google/go-github/v49/github"
	"github.com/shurcooL/githubv4"
	"golang.org/x/oauth2"
)

const (
	// Menu description.
	FirstMenuTitle  string = "<b>Autobot Menu 1</b>\n\nWIZ-Team projects' current status."
	SecondMenuTitle string = "<b>Autobot Menu 2</b>\n\nWIZ-Team projects' current status."

	// Available commands.
	Disable string = "/disable"
	Enable  string = "/enable"
	Help    string = "/help"
	Menu    string = "/menu"
	Todo    string = "/todo"

	// Button texts.
	Next     string = "Next"
	Back     string = "Back"
	Github   string = "WIZ's Github"
	Tutorial string = "Tutorial"

	// Redirect URLs.
	TutorialURL string = "https://core.telegram.org/bots/api"
	GithubURL   string = "https://github.com/orgs/WIZ-Innovation/projects"

	OrgName string = "WIZ-Innovation"
)

type Autobot struct {
	Enable       bool              // Enable CLI to trigger bot.
	Data         *Report           // Data collected from GithubAPI.
	Commands     []string          // Command receives from user input.
	Titles       []string          // List of menu's title/description.
	RedirectURLs []string          // GithubAPI endpoints to request essential data for daily report.
	Buttons      map[string]string // Button action receiver.
	Auth         map[string]string // Basic authentication token for TelegramAPI.
}

func NewAutobot(data *Report, cmds, titles, urls []string, buttons, auth map[string]string) *Autobot {
	return &Autobot{
		Enable:       true,
		Data:         data,
		Commands:     cmds,
		Titles:       titles,
		RedirectURLs: urls,
		Buttons:      buttons,
		Auth:         auth,
	}
}

func GatherToken(key string) string {
	token, exist := os.LookupEnv(key)
	if !exist {
		logger.Error.Fatalln("Cannot detect environment variable")
	}
	return token
}

func (b *Autobot) RegisterBotAPI() *telebot.BotAPI {
	if b.Auth["TeleAPI"] == "" {
		logger.Error.Fatalln("Missing authentication token to activate bot")
	}

	bot, err := telebot.NewBotAPI(b.Auth["TeleAPI"])
	if err != nil {
		out := logger.CustomError(logger.AuthError, err)
		logger.Error.Print(out)
	}
	bot.Debug = true
	return bot
}

func (b *Autobot) RegisterGHClient(ctx context.Context) (*github.Client, *githubv4.Client) {
	if b.Auth["GithubAPI"] == "" {
		logger.Error.Fatalln("Missing authentication token for bot to collect Github datasource")
	}

	oauth2Token := &oauth2.Token{AccessToken: b.Auth["GithubAPI"]}
	tokenSrc := oauth2.StaticTokenSource(oauth2Token)

	httpCLient := oauth2.NewClient(ctx, tokenSrc)
	return github.NewClient(httpCLient), githubv4.NewClient(httpCLient)
}

func getBotInfo(botAPI *telebot.BotAPI) string {
	botInfo := fmt.Sprintf("WIZ-Bot(ID, Name): (%d, %s)", (*botAPI).Self.ID, (*botAPI).Self.UserName)
	return botInfo
}

func (b *Autobot) ReceiveUpdates(ctx context.Context, updates telebot.UpdatesChannel, botAPI *telebot.BotAPI) {
	for {
		select {
		case <-ctx.Done():
			return
		case update := <-updates:
			b.HandleUpdate(update, botAPI)
		}
	}
}

func (b *Autobot) HandleUpdate(update telebot.Update, botAPI *telebot.BotAPI) {
	switch {
	case update.Message != nil:
		b.HandleMessage(update.Message, botAPI)
	case update.CallbackQuery != nil:
		b.HandleButton(update.CallbackQuery, botAPI)
	}
}

func (b *Autobot) HandleMessage(message *telebot.Message, botAPI *telebot.BotAPI) {
	user := message.From
	text := message.Text
	if user == nil {
		return
	}

	// Debugging:
	logger.Tracer.Printf("%s, Room: %d", getBotInfo(botAPI), message.Chat.ID)
	logger.Tracer.Printf("%v wrote %s", user, text)

	var err error
	if b.Enable || text == b.Commands[1] {
		if strings.HasPrefix(text, "/") {
			err = b.HandleCommand(message.Chat.ID, text, botAPI)
		} else if len(text) > 0 {
			nonsense := "Stop writing silly thing like: " + strings.ToUpper(text)
			// To preserve markdown, we attach entities (bold, italic, etc).
			// customMsg.Entities = message.Entities

			err = b.SendNonsense(message.Chat.ID, nonsense, botAPI)
		} else {
			// This is equivalent to forwarding, but without the sender's name.
			err = b.ForwardMsg(message.MessageID, message.Chat.ID, botAPI)
		}
	} else {
		err = b.SendNonsense(message.Chat.ID, "To enable WIZ-Bot, please type: /enable", botAPI)
	}

	if err != nil {
		out := logger.CustomError(logger.RuntimeError, err)
		logger.Error.Print(out)
	}
}

func (b *Autobot) HandleButton(query *telebot.CallbackQuery, botAPI *telebot.BotAPI) {
	markup := telebot.NewInlineKeyboardMarkup()
	message := query.Message

	listMenu := b.CraftLayout()
	var title string
	if query.Data == b.Buttons["Next"] {
		title = b.Titles[1]
		markup = listMenu[1]
	} else if query.Data == b.Buttons["Back"] {
		title = b.Titles[0]
		markup = listMenu[0]
	}

	callbackCfg := telebot.NewCallback(query.ID, "")
	botAPI.Send(callbackCfg)

	// Replace menu text and keyboard.
	msg := telebot.NewEditMessageTextAndMarkup(message.Chat.ID, message.MessageID, title, markup)
	msg.ParseMode = telebot.ModeHTML
	botAPI.Send(msg)
}

func (b *Autobot) HandleCommand(chatId int64, cmd string, botAPI *telebot.BotAPI) error {
	var err error
	switch cmd {
	case b.Commands[0]:
		b.Enable = false
	case b.Commands[1]:
		b.Enable = true
	case b.Commands[2]:
		err = b.SendHelp(chatId, botAPI)
	case b.Commands[3]:
		err = b.SendMenu(chatId, botAPI)
	case b.Commands[4]:
		err = b.SendFetchedData(chatId, botAPI)
	}
	return err
}

func (b *Autobot) SendHelp(chatId int64, botAPI *telebot.BotAPI) error {
	var help string = "<b>Available commands: </b>\n\n"
	listCmd := func(cmds []string) string {
		for _, cmd := range cmds {
			help += fmt.Sprintf("%s\n", cmd)
		}
		return help
	}(b.Commands)

	msg := telebot.NewMessage(chatId, listCmd)
	msg.ParseMode = telebot.ModeHTML
	_, err := botAPI.Send(msg)
	return err
}

func (b *Autobot) CraftLayout() (markups []telebot.InlineKeyboardMarkup) {
	// Keyboard layout for the first menu: [two buttons, one per row].
	firstMenuMarkup := telebot.NewInlineKeyboardMarkup(
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonData(b.Buttons["Next"], b.Buttons["Next"]),
		),
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonURL(b.Buttons["Github"], b.RedirectURLs[1]),
		),
	)

	// Keyboard layout for the second menu: [two buttons, one per row].
	secondMenuMarkup := telebot.NewInlineKeyboardMarkup(
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonData(b.Buttons["Back"], b.Buttons["Back"]),
		),
		telebot.NewInlineKeyboardRow(
			telebot.NewInlineKeyboardButtonURL(b.Buttons["Tutorial"], b.RedirectURLs[0]),
		),
	)

	markups = append(markups, firstMenuMarkup, secondMenuMarkup)
	return
}

func (b *Autobot) SendMenu(chatId int64, botAPI *telebot.BotAPI) error {
	listMenu := b.CraftLayout()
	msg := telebot.NewMessage(chatId, b.Titles[0])
	msg.ParseMode = telebot.ModeHTML
	msg.ReplyMarkup = listMenu[0]

	_, err := botAPI.Send(msg)
	return err
}

func (b *Autobot) SendFetchedData(chatId int64, botAPI *telebot.BotAPI) error {
	msg := telebot.NewMessage(chatId, b.Data.Stringify())
	_, err := botAPI.Send(msg)
	return err
}

func (b *Autobot) SendNonsense(chatId int64, nonsense string, botAPI *telebot.BotAPI) error {
	// NOTE: Only available for peer to peer room (1vs1).
	msg := telebot.NewMessage(chatId, nonsense)
	_, err := botAPI.Send(msg)
	return err
}

func (b *Autobot) ForwardMsg(msgId int, chatId int64, botAPI *telebot.BotAPI) error {
	copyMsg := telebot.NewCopyMessage(chatId, chatId, msgId)
	_, err := botAPI.CopyMessage(copyMsg)
	return err
}
