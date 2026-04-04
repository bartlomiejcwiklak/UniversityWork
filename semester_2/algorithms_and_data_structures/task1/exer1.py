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

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

def infix_to_postfix(tokens):
    op_stack = Stack(len(tokens))
    postfix = []
    precedence = {'+': 2, '-': 2, '*': 1, '/': 1}

    for token in tokens:
        if is_number(token):
            postfix.append(token)
        elif token in precedence:
            while (not op_stack.isempty() and op_stack.top() != '(' and
                   precedence.get(op_stack.top(), 0) >= precedence[token]):
                postfix.append(op_stack.pop())
            op_stack.push(token)
        elif token == '(':
            op_stack.push(token)
        elif token == ')':
            while not op_stack.isempty() and op_stack.top() != '(':
                postfix.append(op_stack.pop())
            if not op_stack.isempty() and op_stack.top() == '(':
                op_stack.pop()
            else:
                raise Exception("Mismatched parentheses")
        else:
            raise Exception("Unknown token: " + token)
    while not op_stack.isempty():
        top_token = op_stack.pop()
        if top_token in ('(', ')'):
            raise Exception("Mismatched parentheses")
        postfix.append(top_token)
    return postfix

def evaluate_postfix(postfix_tokens):
    eval_stack = Stack(len(postfix_tokens))
    for token in postfix_tokens:
        if is_number(token):
            eval_stack.push(float(token))
        else:
            if eval_stack.size() < 2:
                raise Exception("Invalid expression")
            right = eval_stack.pop()
            left = eval_stack.pop()
            if token == '+':
                result = left + right
            elif token == '-':
                result = left - right
            elif token == '*':
                result = left * right
            elif token == '/':
                result = left / right
            else:
                raise Exception("Unknown operator: " + token)
            eval_stack.push(result)
    if eval_stack.size() != 1:
        raise Exception("Invalid expression evaluation")
    return eval_stack.pop()

def process_expression(expr_str):
    tokens = expr_str.split()
    postfix = infix_to_postfix(tokens)
    result = evaluate_postfix(postfix)
    return postfix, result

def main():
    expr = input("")
    try:
        postfix, result = process_expression(expr)
        print("Postfix notation:", " ".join(postfix))
        print("Result:", result)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()