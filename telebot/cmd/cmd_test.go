package cmd

import (
	"fmt"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestWindowsCmd(t *testing.T) {
	s := NewStatement("dir")
	s.Execute()
	fmt.Println(s.CaptureOutput())
}

func TestPwshCmd(t *testing.T) {
	s := NewStatement("Get-Item", ".")
	fmt.Printf("%#v\n", s)
	s.Execute()
	assert.Equal(t, false, s.Status)
}

func TestMultiArgs(t *testing.T) {
	s := NewStatement("ls", "-h", "-a", "-l", "-t")
	s.Execute()
	fmt.Println(s.CaptureOutput())
}

func TestCompoundArg(t *testing.T) {
	s := NewStatement("ps", "aux")
	s.Execute()
	fmt.Println(s.CaptureOutput())
}
