package cmd

import (
	"os/exec"
	"runtime"
	"strings"
)

type Statement struct {
	Cmd    string
	Output []byte
	Args   []string
}

func NewStatement(cmd string, args ...string) Statement {
	if len(args) == 0 {
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

func (s *Statement) Execution() {
	var stdOut []byte

	strArgs := strings.Join(s.Args, " ")
	if runtime.GOOS != "windows" {
		return
	}
	stdOut, _ = exec.Command(s.Cmd, strArgs).Output()
	s.Output = stdOut
}
