class SLList:

    class Node:
        def __init__(self, x):
            self.x = x
            self.next = None

    def __init__(self):
        self.n = 0
        self.head = None
        self.tail = None

    def new_node(self, x):
        return SLList.Node(x)

    def clear(self):
        self.__init__()
    
    # Handles invalid index
    def error(self, i):
        if i < 0 or i >= self.n : raise IndexError

    # Stack operations (LIFO); time complexity: O(1)
    
    def pop(self):
        if self.n == 0: return None
        x = self.head.x
        self.head = self.head.next
        self.n -= 1
        if self.n == 0: 
            self.tail = None
        return x

    def push(self, x):
        node = self.new_node(x)
        node.next = self.head
        self.head = node
        if self.n == 0:
            self.tail = node
        self.n += 1
        return True

# Queue operations (FIFO); time complexity: O(1)

    def _remove(self):
        return self.pop()
    
    def _add(self, x):
        node = self.new_node(x)
        if self.n == 0:
            self.head = node
        else:
            self.tail.next = node
        self.tail = node
        self.n += 1
        return True
#

    # Time complexity: O(n)
    def get(self, i):
        self.error(i)

        node = self.head
        for _ in range(i):
            node = node.next

        return node

    # Time complexity: O(n)
    def set(self, i, x):
        node = self.get(i)
        y = node.x
        node.x = x
        return y

    # Time complexity: O(n)
    def add(self, i, x):
        if i < 0 or i > self.n : raise IndexError
        if i == 0: 
            self.push(x)
            return True

        u = self.head
        for _ in range(i-1):
            u = u.next

        node = self.new_node(x)
        node.next = u.next
        u.next = node
        self.n += 1
        return True

    # Time complexity: O(n)
    def remove(self, i):
        self.error(i)
        if i == 0: return self.pop()

        u = self.head
        for _ in range(i-1):
            u = u.next     

        x = u.next.x
        u.next = u.next.next   
        self.n -= 1
        return x

    def show(self):
        s = "["
        u = self.head
        while u is not None:
            s += "%r" % u.x
            u = u.next
            if u is not None:
                s += ","
        return s + "]"
    