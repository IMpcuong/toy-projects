package logger

import (
	"errors"
	"fmt"
	"io"
	"log"
)

var (
	Tracer  *log.Logger // Logging the traceback of an error.
	Info    *log.Logger // Logging the information of an error.
	Warning *log.Logger // Logging the warning may cause all errors.
	Error   *log.Logger // Logging the compiler/runtime error message.
)

func Generate(logTracer, logInfo, logWarning, logErr io.Writer) {
	Tracer = log.New(logTracer, "TRACE: ", log.Ldate|log.Ltime|log.Lshortfile)
	Info = log.New(logInfo, "INFO: ", log.Ldate|log.Ltime|log.Lshortfile)
	Warning = log.New(logWarning, "WARNING: ", log.Ldate|log.Ltime|log.Lshortfile)
	Error = log.New(logErr, "ERROR: ", log.Ldate|log.Ltime|log.Lshortfile)
}

var (
	AuthError    string = "AuthError"
	CommandError string = "CommandError"
	CompileError string = "CompileError"
	RuntimeError string = "RuntimeError"
	UnknownError string = "UnknownError"
)

func CustomError(desc string, err error) string {
	return fmt.Sprintf("Type: %v, Detail: %v", errors.New(desc), err.Error())
}
