package main

import (
	"fmt"
)

type node struct {
	data int
	next *node
}

func main() {
	list := appendNode(nil, 3)
	appendNode(list, 32)
	list.printlist()
	list = removeNode(list, 3)
	list = removeNode(list, 32)
	list.printlist()
}

func appendNode(head *node, data int) *node {
	n := node{data: data}
	n.next = nil
	if head == nil {
		return &n
	}
	for head.next != nil {
		head = head.next
	}
	head.next = &n
	return &n
}

func (head *node) printlist(){
	if head == nil {
		fmt.Println("list empty")
		return
	}
	currentNode := head
	for currentNode != nil {
		fmt.Println(currentNode.data)
		currentNode = currentNode.next
	}
}

func removeNode(head *node, val int) *node {
	remove := head
	previous := head

	if remove != nil && remove.data == val {
		head = head.next
		return head
	}
	for remove.data != val {
		previous = remove
		remove = remove.next
	}
	previous.next = remove.next
	return head
}
