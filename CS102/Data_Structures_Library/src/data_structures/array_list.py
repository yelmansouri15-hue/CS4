import numpy

class ArrayList:
    def __init__(self):
        self.a = numpy.empty(1, dtype=object)
        self.n = 0

    def clear(self):
        self.__init__()

    # Handles invalid index
    def error(self, i):
        if i < 0 or i >= self.n : raise IndexError

    # Time complexity: O(1) [base adress + i * size element]
    def get(self, i):
        self.error(i)
        return self.a[i]

    # Time complexity: O(1)
    def set(self, i, x):
        self.error(i)
        y = self.a[i] # Get is O(1)
        self.a[i] = x # O(1) + O(1) = O(1)
        return y

    # Time complexity: O(n); Amortized time: O(1) [when resize: a.length = 2n; n add/remove availables --> O(n)/n]
    def add(self, i, x):
        if i < 0 or i > self.n : raise IndexError
        if self.n == len(self.a) : self.resize()  # Copy n elements: O(n)
        self.a[i + 1:self.n + 1] = self.a[i:self.n]
        self.a[i] = x  # O(1) + O(n) = O(n)
        self.n += 1

    # ""
    def remove(self, i):
        self.error(i)
        x = self.a[i]
        self.a[i:self.n - 1] = self.a[i + 1:self.n]
        self.n -= 1
        if len(self.a) >= 3*self.n : self.resize()
        return x

    def resize(self):
        b = numpy.empty(max(2*self.n, 1), dtype=object)
        b[:self.n] = self.a[:self.n]
        self.a = b
    
