package main

import (
	"fmt"
	"math/rand"
	"time"
)

type node struct {
	data int
	next *node
}

func main() {
	list := appendNode(nil, 1)
	appendNode(list, Randomint())
	appendNode(list, Randomint())
	appendNode(list, Randomint())
	appendNode(list, Randomint())
	appendNode(list, Randomint())
	list.printlist()
	fmt.Println("   ")
	list = reverseKGroup(list, 4)
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
func removeAllNodesWithvalue(head *node, val int) *node {
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

func swap_nodes(head *node, k int) *node {
	firstswap := head
    i := 0
    for i < k-1 {
        firstswap = firstswap.next
        i++
    }
    
    secondswap := head
    for fast := firstswap.next; fast != nil; fast = fast.next {
        secondswap = secondswap.next
    }
    
    firstswap.data, secondswap.data = secondswap.data, firstswap.data
    return head
}

func reverseKGroup(head *node, k int) *node{
    var groupPrev *node
    var groupNext *node
    var KthNode *node
    var tmp *node
    // nodes for reversing group
    var curr *node
    var prev *node
    var placeHolder *node
    
    dummyNode := &node{data: 0}
    dummyNode.next = head
    groupPrev = dummyNode
    
    for true {
        KthNode = getKthNode(groupPrev, k);
        if KthNode == nil {
            break;
        }
        groupNext = KthNode.next;
        
        // reversing group
        prev = KthNode.next;
        curr = groupPrev.next;
        for curr != groupNext {
            placeHolder = curr.next;
            curr.next = prev;
            prev = curr;
            curr = placeHolder;
        }
        
        tmp = groupPrev.next;
        groupPrev.next = KthNode;
        groupPrev = tmp; 
    }
    return dummyNode.next;
}
func getKthNode(curr *node, k int) *node{
    for curr != nil && k > 0 {
        curr = curr.next;
        k--;
    }
    return curr;
}
var randomnum int = int(time.Now().UnixMicro())

func Randomint() int {
	arr := [10]int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,}
    x := rand.NewSource(time.Now().UnixNano())
    y := rand.New(x)
    rand.Shuffle(len(arr), func(i, j int) {
        arr[i], arr[j] = arr[j], arr[i]
    })
	return arr[y.Intn(10)]
}


