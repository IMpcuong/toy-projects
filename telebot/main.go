package main

import (
	"bufio"
	"context"
	"fmt"
	"io"
	"net/url"
	"os"
	"telebot/cmd"
	"telebot/logger"
	"telebot/pkg"

	telebot "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

func main() {
	logger.Generate(io.Discard, os.Stdout, os.Stdout, os.Stderr)

	s := cmd.NewStatement("Get-Item", ".")
	s.Execute()
	fmt.Println(s.CaptureOutput())

	urls := make([]*url.URL, 0)

	// TODO: Find out a better solution to store Telegram authentication token.
	token := ""
	autobot := pkg.NewAutobot(token, "WIZ-Team Innovation", urls)
	bot, _ := autobot.Register()

	update := telebot.NewUpdate(0)
	update.Timeout = 60

	// Create a new cancellable background context. Calling `cancel()` leads to the cancellation of the current context.
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)

	updates := bot.GetUpdatesChan(update)
	go autobot.ReceiveUpdates(ctx, updates)

	// Tell the user the bot is online.
	logger.Tracer.Println("Start listening for updates. Press enter to stop!")

	// Wait for a newline symbol, then cancel handling updates.
	bufio.NewReader(os.Stdin).ReadBytes('\n')
	cancel()
}
