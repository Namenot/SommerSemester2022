""" DO NOT MODIFY THE FOLLOWING CODE """

class DoublyLinkedList:
    
    class Iterator:
        
        def __init__(self, dllist):
            self._list = dllist
            self._curr_elem = self._list.head
            
        def __next__(self):
            if self._curr_elem is not None:
                elem = self._curr_elem
                self._curr_elem = self._curr_elem.successor
                return elem
            raise StopIteration
    
    class Element:
        
        def __init__(self, data):
            self._data = data
            self._predecessor = None
            self._successor = None
            
        @property
        def data(self):
            return self._data
        
        @property
        def predecessor(self):
            return self._predecessor
        
        @property
        def successor(self):
            return self._successor
        
        @property
        def data(self):
            return self._data
        
        @property
        def has_predecessor(self):
            return self.predecessor is not None
        
        @property
        def has_successor(self):
            return self.successor is not None
        
        def __repr__(self):
            return str(self.data)
        
        def __str__(self):
            return str(self.data)
        
    def __init__(self):
        self._head = None
        self._tail = None
        self._len = 0
        
    @property
    def first(self):
        return self._head
    
    @property
    def last(self):
        return self._tail
    
    @property
    def head(self):
        return self._head
    
    @property
    def tail(self):
        return self._tail
    
    def __repr__(self):
        elements = [element for element in self]
        return str(elements)
    
    def __len__(self):
        return self._len
    
    def __iter__(self):
        return self.Iterator(self)
    
    def append(self, data):
        self._len += 1
        new_element = self.Element(data)
        if self.head is None:
            self._head = new_element
            self._tail = new_element
        else:
            new_element._predecessor = self.tail
            self._tail._successor = new_element
            self._tail = new_element
    
    def remove(self, data):
        for element in self:
            if element.data == data:
                self._len -= 1
                if element.has_predecessor:
                    if element.has_successor:
                        element.predecessor._successor = element.successor
                        element.successor._predecessor = element.predecessor
                    else:
                        self._tail = element.predecessor
                        element.predecessor._successor = None
                else:
                    if element.has_successor:
                        self._head = element._successor
                        element.successor._predecessor = None
                    else:
                        self._head = None
                        self._tail = None
    
    def contains(self, data):
        for element in self:
            if element.data == data:
                return True
        return False
    
    def reverse(self):
        nhead = self.tail
        ntail = self.head
        elem = ntail
        while elem is not None:
            successor = None
            predecessor = None
            if elem.has_successor:
                successor = elem.successor
            if elem.has_predecessor:
                predecessor = elem.predecessor
            elem._successor = predecessor
            elem._predecessor = successor
            elem = successor
        self._head = nhead
        self._tail = ntail
        return self
    
class DynamicArray:
    
    class Iterator:
        
        def __init__(self, array):
            self._array = array
            self._index = 0
        
        def __next__(self):
            if self._index < len(self._array):
                index = self._index
                self._index += 1
                return self._array[index]
            raise StopIteration
        
    class Element:
        
        def __init__(self, data):
            self._data = data
            
        @property
        def data(self):
            return self._data
        
        def __str__(self):
            return str(self.data)
        
        def __repr__(self):
            return str(self.data)
    
    def __init__(self):
        self._len = 0
        self._data = list()
        
    def __len__(self):
        return self._len
    
    def __getitem__(self, i):
        if len(self) == 0:
            raise IndexError("no data")
        return self._data[i]
    
    def __repr__(self):
        return str(self._data)
    
    @property
    def first(self):
        return self[0]
    
    @property
    def last(self):
        return self[-1]
    
    def append(self, data):
        if self._data is None:
            self._data = [self.Element(data)]
        else:
            ndata = [None] * (len(self) + 1)
            for i, elem in enumerate(self):
                ndata[i] = elem
            ndata[-1] = self.Element(data)
            self._data = ndata
        self._len += 1
    
    def remove(self, data):
        c = 0
        for elem in self:
            if elem.data == data:
                c += 1
        nlen = len(self) - c
        ndata = [None] * nlen
        c = 0
        for elem in self:
            if elem.data != data:
                ndata[c] = elem
                c+= 1
        self._data = ndata
        self._len = nlen
                
    def contains(self, data):
        for element in self:
            if element.data == data:
                return True
        return False
    
    def reverse(self):
        ndata = [None] * len(self)
        n = len(self) - 1
        for i, elem in enumerate(self):
            ndata[n - i] = elem
        self._data = ndata
        return self
    
import time

def measure_time(method, argument):
    start = time.process_time()
    method(argument)
    end = time.process_time()
    return end-start

""" Student code """

def eratosthenes(ds):
    """ Your code here """
    
    for i in ds:

        if i.data < 2:
            continue

        for k in ds:
            if k.data % i.data == 0 and k.data > i.data:
                ds.remove(k.data)

    return ds

def eratosthenes_fast(n):
    """ Your code here """
    dllist = DoublyLinkedList()

    # fill dllist (n + 1 to include the highest index which would otherwise vanish)
    for i in range(2, n+1):
        dllist.append(i)
    
    eratosthenes(dllist)

    return dllist

def eratosthenes_slow(n):
    """ Your code here """

    darray = DynamicArray()

    # fill darray (n + 1 to include the highest index which would otherwise vanish)
    for i in range(2, n+1):
        darray.append(i)
    
    eratosthenes(darray)

    return darray
    
def prime_factors(n):
    """ Your code here """

    primes = eratosthenes_fast(n)
    prifacts = DoublyLinkedList()

    while primes.contains(n) == False and n > 1:
        for i in primes:
            while n % i.data == 0:
                n /= i.data
                prifacts.append(i.data)

    return prifacts
            
matrikelnummern = [108018266786] # Enter your Matrikelnummer here
                     # for example matrikelnummern = [123] for one student 
                     # or matrikelnummern = [123, 456] for two students

print(measure_time(eratosthenes_fast,1000))
print(measure_time(eratosthenes_slow,1000))