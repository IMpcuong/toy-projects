package main

import (
	"fmt"
	"io"
	"os"
	"telebot/cmd"
	"telebot/logger"
)

func main() {
	fmt.Println("This is WIZ Team's Telegram bot!")
	logger.Generate(io.Discard, os.Stdout, os.Stdout, os.Stderr)

	s := cmd.NewStatement("Get-Item", ".")
	s.Execute()
	fmt.Println(s.CaptureOutput())

	s = cmd.NewStatement("dir")
	s.Execute()
	fmt.Println(s.CaptureOutput())
}
