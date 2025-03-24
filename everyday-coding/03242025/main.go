package main

import (
	"fmt"
	"iter"
	"slices"
)

type Req struct {
	args    []int
	f       func([]int) int
	resChan chan int
}

// Server-side //

func sum(a []int) (s int) {
	if len(a) == 0 {
		return s
	}

	for _, v := range a {
		s += v
	}
	return s
}

func handle(queue chan *Req) {
	for req := range queue {
		req.resChan <- req.f(req.args)
	}
}

func toSlice(s iter.Seq[int]) (l []int) {
	nxt, stop := iter.Pull(s)
	defer stop()

	for {
		v, ok := nxt()
		if !ok {
			break
		}
		l = append(l, v)
	}
	// for _ = range s {
	// 	v, ok := nxt()
	// 	if !ok {
	// 		break
	// 	}
	// 	l = append(l, v)
	// }

	return l
}

// Server-side //

func main() {
	scores := []int{1, 2, 4, 5, 8, 1, 3}
	scoresIter := slices.Values(scores)

	// @Note: The buffer size is the number of elements
	// 	that can be sent to the channel without the send blocking.
	rq := &Req{toSlice(scoresIter), sum, make(chan int)}

	rqQueue := make(chan *Req, 5)
	for _ = range 5 {
		rqQueue <- rq
	}
	go handle(rqQueue)

	for _ = range 5 {
		fmt.Printf("Ans: %d\n", <-rq.resChan)
	}
}
