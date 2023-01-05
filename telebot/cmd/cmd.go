package cmd

import (
	"os/exec"
	"runtime"
	"telebot/logger"
)

type Statement struct {
	Status bool
	Cmd    string
	Output []byte
	Args   []string
}

func NewStatement(cmd string, args ...string) Statement {
	if len(args) == 1 && args[0] == "" {
		return Statement{
			Cmd: cmd,
		}
	}
	return Statement{
		Cmd:  cmd,
		Args: args,
	}
}

func (s *Statement) CaptureOutput() string {
	return string(s.Output)
}

func (s *Statement) Execute() {
	// NOTE: We currently only support MinGW-w64 (runtime environment for GCC & LLVM)
	// or any other Linux terminal emulator on Windows.
	if runtime.GOOS != "windows" {
		return
	}

	stdOut, err := exec.Command(s.Cmd, s.Args...).Output()
	if err != nil {
		out := logger.CustomError(logger.CommandError, err)
		logger.Error.Print(out)
	}
	s.Status = true
	s.Output = stdOut
}
