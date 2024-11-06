package main

import (
	"fmt"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func middleNode(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	nodeMap := make(map[int]*ListNode, 100)
	counter := 1
	nodeMap[counter] = head
	for cur := head; cur.Next != nil; counter++ {
		nodeMap[counter] = cur.Next
		cur = cur.Next
	}
	return nodeMap[counter/2+1]
}

func main() {
	nodes := new(ListNode)
	nodes.Val = 0
	next1 := new(ListNode)
	next1.Val = 0
	nodes.Next = next1
	next2 := new(ListNode)
	next2.Val = 0
	next1.Next = next2

	fmt.Printf("%#v", middleNode(nodes))
}
