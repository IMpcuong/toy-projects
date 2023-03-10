package main

import (
	"bufio"
	"context"
	"os"
	"telebot/bot"
	"telebot/cmd"
	"telebot/logger"

	telebot "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

var (
	urls []string = []string{
		bot.TutorialURL,
		bot.GithubURL,
	}
	commands []string          = []string{bot.Disable, bot.Enable, bot.Help, bot.Menu, bot.Todo}
	titles   []string          = []string{bot.FirstMenuTitle, bot.SecondMenuTitle}
	buttons  map[string]string = map[string]string{
		"Back":     bot.Back,
		"Next":     bot.Next,
		"Github":   bot.Github,
		"Tutorial": bot.Tutorial,
	}
)

func main() {
	logger.Generate(os.Stdout, os.Stdout, os.Stdout, os.Stderr)

	s := cmd.NewStatement("Get-Item", ".")
	s.Execute()
	logger.Tracer.Print(s.CaptureOutput())

	// Create a new cancellable background context. Calling `cancel()` leads to the cancellation of the current context.
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)

	// TODO: Find out a better solution to store Telegram authentication teleToken.
	teleToken := bot.GatherToken("teletoken")
	// NOTE: Fine-grained API credentials cannot be used on this case.
	ghToken := bot.GatherToken("ghtoken")
	auth := map[string]string{
		"TeleAPI":   teleToken,
		"GithubAPI": ghToken,
	}
	autobot := bot.NewAutobot(new(bot.Report), commands, titles, urls, buttons, auth)

	clientV3, clientV4 := autobot.RegisterGHClient(ctx)
	bot.SetRateLimits(ctx, 100, clientV3)
	tasks, _ := bot.CollectTaskV3(ctx, bot.OrgName, clientV3)
	if len(tasks) == 0 {
		tasks, _ = bot.CollectTaskV4(ctx, bot.OrgName, 20, clientV4)
	}
	report := bot.DailyReport(tasks)
	autobot.Data = &report

	// Global Telegram bot:
	botAPI := autobot.RegisterBotAPI()

	update := telebot.NewUpdate(0)
	update.Timeout = 60

	updates := botAPI.GetUpdatesChan(update)
	go autobot.ReceiveUpdates(ctx, updates, botAPI)

	// Tell the user the bot is online.
	logger.Tracer.Print("Start listening for updates. Press enter to stop!")

	// Wait for a newline symbol, then cancel handling updates.
	bufio.NewReader(os.Stdin).ReadBytes('\n')
	cancel()
}
