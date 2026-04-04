class Stack:
    def __init__(self, data_type, max_size):
        self.stack = []
        self.data_type = data_type
        self.max_size = max_size

    def push(self, item):
        if len(self.stack) < self.max_size and isinstance(item, self.data_type):
            self.stack.append(item)
        else:
            raise ValueError("Stack overflow or invalid data type")

    def pop(self):
        if not self.isempty():
            return self.stack.pop()
        else:
            raise IndexError("Stack underflow")

    def isempty(self):
        return len(self.stack) == 0

    def top(self):
        if not self.isempty():
            return self.stack[-1]
        else:
            raise IndexError("Stack is empty")


class ListNode:
    def __init__(self, char):
        self.char = char
        self.next = None


class SinglyLinkedList:
    def __init__(self):
        self.head = None

    def insert(self, string):
        for char in string:
            new_node = ListNode(char)
            if self.head is None:
                self.head = new_node
            else:
                current = self.head
                while current.next:
                    current = current.next
                current.next = new_node

    def to_string(self):
        result = ""
        current = self.head
        while current:
            result += current.char
            current = current.next
        return result


def is_palindrome(s):
    stack = Stack(str, len(s))  # Creating a stack for the string characters
    
    for char in s:
        stack.push(char)  # Push all characters onto the stack
    
    reversed_s = ""  # To store the reversed string
    while not stack.isempty():
        reversed_s += stack.pop()
    
    return s == reversed_s  # Check if original and reversed strings are the same


# Example Usage
string = "3120213"
linked_list = SinglyLinkedList()
linked_list.insert(string)
linked_list_string = linked_list.to_string()

print(f"'{string}' is a palindrome.") if is_palindrome(linked_list_string) else print(f"'{string}' is not a palindrome.")