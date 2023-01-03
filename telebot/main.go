package main

import (
	"fmt"
	"telebot/cmd"
)

func main() {
	fmt.Println("This is WIZ Team's Telegram bot!")
	s := cmd.NewStatement("ls", "-la")
	s.Execution()
	fmt.Println(s.CaptureOutput())
}
