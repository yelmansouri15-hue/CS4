class DLList:

    class Node:
        def __init__(self, x):
            self.x = x
            self.prev = None
            self.next = None

    def __init__(self):
        self.n = 0
        self.dummy = DLList.Node(None)
        self.dummy.prev = self.dummy
        self.dummy.next = self.dummy

    def new_node(self, x):
        return DLList.Node(x)

    def clear(self):
        self.__init__()
    
    # Handles invalid index
    def error(self, i):
        if i < 0 or i >= self.n : raise IndexError

    # ALL time complexity: O(1 + min{i, n-i})

    def get(self, i):
        self.error(i)

        if i < self.n/2:
            node = self.dummy.next
            for _ in range (i):  # O(i)
                node = node.next
        else:
            node = self.dummy
            for _ in range (self.n,i,-1):  # O(n-1)
                node = node.prev

        # The worst case is min{i, n-1}: O(1 + min{i, n-1})
        return node.x

    def set(self, i, x):
        self.error(i)

        if i < self.n/2:
            node = self.dummy.next
            for _ in range (i):  # O(i)
                node = node.next
        else:
            node = self.dummy
            for _ in range (self.n,i,-1):  # O(n-1)
                node = node.prev        
        y = node.x
        node.x = x
        return y

    def addBefore(self, u, x):
        node = self.new_node(x)
        node.prev = u.prev
        node.next = u
        node.next.prev = node
        node.prev.next = node
        self.n += 1

        return node

    def add(self, i, x):
        if i == self.n:
            node = self.new_node(x)
            node.prev = self.dummy.prev
            node.next = self.dummy
            self.dummy.prev = node
            node.prev.next = node
            self.n += 1
            return True

        if i < 0 or i > self.n : raise IndexError
        self.addBefore(self.get(i), x)
        return True

    def _remove(self, u):
        u.next.prev = u.prev
        u.prev.next = u.next
        self.n -= 1

    def remove(self, i):
        self.error(i)
        node = self.get(i)
        self._remove(node)
        return node.x

    def show(self):
        s = "["
        u = self.dummy.next
        while u != self.dummy:
            s += "%r" % u.x
            u = u.next
            if u != self.dummy:
                s += ","
        return s + "]"
            
    
