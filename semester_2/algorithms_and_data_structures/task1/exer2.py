class Stack:
    def __init__(self, max_size):
        self.max_size = max_size
        self.stack = [None] * max_size
        self.top_index = -1

    def push(self, item):
        if self.top_index >= self.max_size - 1:
            raise Exception("Stack overflow")
        self.top_index += 1
        self.stack[self.top_index] = item

    def pop(self):
        if self.isempty():
            raise Exception("Stack underflow")
        item = self.stack[self.top_index]
        self.top_index -= 1
        return item

    def top(self):
        if self.isempty():
            raise Exception("Stack is empty")
        return self.stack[self.top_index]

    def isempty(self):
        return self.top_index == -1

    def size(self):
        return self.top_index + 1

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node

    def traverse(self):
        current = self.head
        while current:
            yield current.data
            current = current.next


def is_palindrome(s):
    ll = LinkedList()
    for ch in s:
        ll.insert(ch)

    stack = Stack(len(s))
    for ch in ll.traverse():
        stack.push(ch)

    for ch in ll.traverse():
        if ch != stack.pop():
            return False
    return True

def main():
    s = input("")
    if is_palindrome(s):
        print(f'"{s}" is a palindrome.')
    else:
        print(f'"{s}" is not a palindrome.')

if __name__ == "__main__":
    main()
