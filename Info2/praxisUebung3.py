class Binary_Searchtree:
    
    class Node:
        
        def __init__(self, key):
            self._key = key
            self._lc = None
            self._rc = None
            self._parent = None
            
        @property
        def rc(self):
            return self._rc
        
        @property
        def lc(self):
            return self._lc
        
        @rc.setter
        def rc(self, entry):
            self._rc = entry
            
        @lc.setter
        def lc(self, entry):
            self._lc = entry
            
        @property
        def key(self):
            return self._key
        
        @property
        def parent(self):
            return self._parent
        
        @parent.setter
        def parent(self, entry):
            self._parent = entry
        
        def __repr__(self):
            return str(self.key)
        
        def __str__(self):
            return str(self.key)
            
    def __init__(self):
        self._root = None
        self._depth = 0
        
    @property
    def depth(self):
        return self._depth
        
    @property
    def root(self):
        return self._root
    
    @root.setter
    def root(self, entry):
        self._root = entry
        
    @property
    def depth(self):
        return self._depth
        
    def __repr__(self):
        return str(self)
    
    def __str__(self):
        levels = [["." for j in range(0, 2**i)] for i in range(0, self.depth + 1)]
        depth = 0
        self.to_str(self.root, depth, 0, levels)
        result = ""
        n_positions = 2**(self.depth + 1)
        for i, elem in enumerate(levels):
            t_result = [" "] * n_positions + [" ", "\n"]
            for j, val in enumerate(elem):
                position = int(2**(self.depth - i) + j * n_positions / 2**i)
                t_result[position] = val
            result += "".join(t_result[1:])
        return result[:-1]
        
    def to_str(self, node, depth, index, levels):
        levels[depth][index] = str(node)
        if node.lc is not None:
            self.to_str(node.lc, depth + 1, 2 * index, levels)
        if node.rc is not None:
            self.to_str(node.rc, depth + 1, 2 * index + 1, levels)
        
    def locate(self, key):
        """ key is of type 'int', 'float' or 'str' 
        
            returns a tuple current, depth
        """
        current = self.root
        depth = 0
        if current is None:
            return None, depth
        while current.lc is not None or current.rc is not None:
            """ Your code here """
            if current.key == key:
                return current, depth

            if current.key < key and current.rc != None:
                current = current.rc 
            
            elif current.key > key and current.lc != None:
                current = current.lc
            else:
                break
                
            depth += 1

        return current, depth

    def insert(self, key):
        """ key is of type 'int', 'float' or 'str' """
        parent, depth = self.locate(key)
        new_node = Binary_Searchtree.Node(key)
        new_node.parent = parent
        if parent is None:
            self.root = new_node
        else:
            """ Your code here """
            
            if parent.key > key:
                parent.lc = new_node
            
            if parent.key < key:
                parent.rc = new_node
            
            self._depth += int((depth+1) > self._depth) 

    def remove(self, key):
        """ key is of type 'int', 'float' or 'str' """


if __name__ == "__main__":
    a = Binary_Searchtree()
    a.insert(3)
    print(a)
    print()
    a.insert(1)
    print(a)
    print()
    a.insert(2)
    print(a)
    print()
    a.insert(0)
    print(a)
    print()
    a.insert(5)
    print(a)
    print()
    a.insert(4)
    print(a)
    print()
    a.insert(6)
    print(a)
    print()
    a.remove(5)
    print(a)
    print()
    a.remove(1)
    print(a)
    print()
    a.remove(2)
    print(a)
    print()
    a.remove(3)
    print(a)

    print("locate 3 : ", a.locate(3))
