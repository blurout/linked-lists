package print

import( 
	"fmt"
)

type node struct {
	val  int
	next *node
}

func Plist(head *node) {
	if head == nil {
		fmt.Println("list empty")
		return
	}
	currentNode := head
	for currentNode != nil {
		fmt.Println(currentNode.val)
		currentNode = currentNode.next
	}
}