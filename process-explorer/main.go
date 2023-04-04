package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"syscall"
	"unsafe"
)

func main() {
	procs, _ := findAllProcesses()
	for _, p := range procs {
		fmt.Printf("%+v\n", p)
	}
}

// Copyright belongs to: https://github.com/mitchellh/go-ps/
// Because of his kernel-knowledge, so I can make this happen.

type Process interface {
	// Pid is the process ID for this process.
	Pid() int

	// PPid is the parent process ID for this process.
	PPid() int

	// Executable name running this process. This is not a path to the
	// executable.
	Executable() string
}

type DarwinProcess struct {
	pid      int
	ppid     int
	binaries string
}

func (p *DarwinProcess) Pid() int           { return p.pid }
func (p *DarwinProcess) PPid() int          { return p.ppid }
func (p *DarwinProcess) Executable() string { return p.binaries }

func findExactProcess(pid int) (Process, error) {
	procs, err := findAllProcesses()
	if err != nil {
		return nil, err
	}
	for _, p := range procs {
		if p.Pid() == pid {
			return p, nil
		}
	}
	return nil, fmt.Errorf("ERROR")
}

const (
	_CTRL_KERN         = 1
	_KERN_PROC         = 14
	_KERN_PROC_ALL     = 0
	_KINFO_STRUCT_SIZE = 648
)

type kernelInfoProc struct {
	_    [40]byte
	Pid  int32
	_    [199]byte
	Comm [16]byte
	_    [301]byte
	PPid int32
	_    [84]byte
}

func findAllProcesses() ([]Process, error) {
	buf, err := darwinSyscall()
	if err != nil {
		return nil, err
	}

	kernelProcs := make([]*kernelInfoProc, 0, 50)
	cur := 0
	for i := _KINFO_STRUCT_SIZE; i < buf.Len(); i += _KINFO_STRUCT_SIZE {
		foundProc := new(kernelInfoProc)
		err := binary.Read(bytes.NewBuffer(buf.Bytes()[cur:i]), binary.LittleEndian, foundProc)
		if err != nil {
			return nil, err
		}
		cur = i
		kernelProcs = append(kernelProcs, foundProc)
	}

	darwinProcs := make([]Process, len(kernelProcs))
	for i, kProc := range kernelProcs {
		darwinProcs[i] = &DarwinProcess{
			pid:      int(kProc.Pid),
			ppid:     int(kProc.PPid),
			binaries: darwinCString(kProc.Comm),
		}
	}
	return darwinProcs, nil
}

func darwinSyscall() (*bytes.Buffer, error) {
	mib := [4]int32{_CTRL_KERN, _KERN_PROC, _KERN_PROC_ALL, 0}
	size := uintptr(0)

	_, _, errno := syscall.Syscall6(
		syscall.SYS___SYSCTL,
		uintptr(unsafe.Pointer(&mib[0])),
		4, 0,
		uintptr(unsafe.Pointer(&size)),
		0, 0,
	)
	if errno != 0 {
		return nil, errno
	}

	bytesData := make([]byte, size)
	_, _, errno = syscall.Syscall6(
		syscall.SYS___SYSCTL,
		uintptr(unsafe.Pointer(&mib[0])),
		4,
		uintptr(unsafe.Pointer(&bytesData[0])),
		uintptr(unsafe.Pointer(&size)),
		0, 0,
	)
	if errno != 0 {
		return nil, errno
	}
	return bytes.NewBuffer(bytesData[0:size]), nil
}

func darwinCString(out [16]byte) string {
	i := 0
	for _, b := range out {
		if b != 0 {
			i++
		} else {
			break
		}
	}
	return string(out[:i])
}
