package main

import (
	"bufio"
	"context"
	"fmt"
	"net/url"
	"os"
	"telebot/bot"
	"telebot/cmd"
	"telebot/logger"

	telebot "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

func main() {
	logger.Generate(os.Stdout, os.Stdout, os.Stdout, os.Stderr)

	s := cmd.NewStatement("Get-Item", ".")
	s.Execute()
	fmt.Print(s.CaptureOutput())

	urls := make([]*url.URL, 0)

	// TODO: Find out a better solution to store Telegram authentication token.
	token := os.Getenv("teletoken")
	autobot := bot.NewAutobot(token, "WIZ-Team Innovation", urls)
	bot.WizBot = autobot.Register()

	update := telebot.NewUpdate(0)
	update.Timeout = 60

	// Create a new cancellable background context. Calling `cancel()` leads to the cancellation of the current context.
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)

	updates := bot.WizBot.GetUpdatesChan(update)
	go autobot.ReceiveUpdates(ctx, updates)

	// Tell the user the bot is online.
	logger.Tracer.Print("Start listening for updates. Press enter to stop!")

	// Wait for a newline symbol, then cancel handling updates.
	bufio.NewReader(os.Stdin).ReadBytes('\n')
	cancel()
}
