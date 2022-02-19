package main

import (
	"fmt"
)

type node struct {
	data int
	next *node
}

func main() {
	list := appendNode(nil, 1)
	appendNode(list, 2)
	appendNode(list, 3)
	appendNode(list, 4)
	appendNode(list, 5)
	appendNode(list, 3)
	appendNode(list, 3)
	appendNode(list, 3)
	appendNode(list, 3)

	list = removeNode(list, 3)
	list.printlist()
	fmt.Printf("\n")

	appendNode(list, 3)	
	list = removeAllNodesWithValue(list, 3)
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
func removeAllNodesWithValue(head *node, val int) *node {
    var tmp *node
    if head == nil {
        return head
    }
    tmp = head
    for tmp.next != nil {
        if tmp.next.data == val {
            tmp.next = tmp.next.next
        } else {
            tmp = tmp.next
        }
    }
    if head.data == val {
        return head.next
    }
    return head
}