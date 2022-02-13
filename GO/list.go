package main

import (
	"linkedList/GO/printList"
)

type node struct {
	val  int
	next *node
}

func main() {
	myList := node{next: nil}
	n := node{val: 1, next: nil}
	myList = n

	newNode0 := node{val: 2, next: nil}
	myList.next = &newNode0

	newNode1 := node{val: 3, next: nil}
	myList.next.next = &newNode1

	printList.Plist()
}
