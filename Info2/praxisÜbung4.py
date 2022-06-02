class Hashtable:
    
    def __init__(self):
        self._table = dict()
        
    @property
    def table(self):
        return self._table
        
    def __str__(self):
        result = ""
        for key in self._table.keys():
            result += str(key) + ": " + str(self._table[key]) + "\n\n"
        return result[:-2]
        
    def __repr__(self):
        return str(self)
    
    def __eq__(self, s):
        for hash in s.table:
            if hash not in self.table:
                return False
        for hash in self.table:
            if hash not in s.table:
                return False
        for hash in self.table:
            if s.table[hash] != self.table[hash]:
                return False
        return True
    
    def __copy__(self):
        t = Hashtable()
        t._table = self.table
        return t
    
    def build(self, a):
        for e in a:
            self.insert(e)
    
    def _hash(self, e):
        """ e is a tuple with first element 'int', which is the key and second element 'str' 
        
            returns key mod 10
        """
        return e[0] % 10
            
    def insert(self, e):
        """ e is tuple with first element 'int', which is the key and second element 'str' """
        
        hashkey = self._hash(e)
        
        hashvalues = list()

        if hashkey in self.table.keys():
            hashvalues += self.table[hashkey]
        
        hashvalues.append(e[1])

        self.table[hashkey] = hashvalues


    def find(self, e):
        """ e is tuple with first element 'int', which is the key and second element 'str' 
        
            returns None if e is not in table, else e
        """
        hashkey = self._hash(e)

        if(hashkey in self.table.keys()):
            if(e[1] in self.table[hashkey]):
                return e
        
        return None
    
    def remove(self, e):
        """ e is tuple with first element 'int', which is the key and second element 'str' """
        hashkey = self._hash(e)

        if(self.find(e)):
            
            self.table[hashkey].remove(e[1])

            if(len(self.table[hashkey]) == 0):
                del self.table[hashkey]    
            
                
    
if __name__ == "__main__":
    import random
    import copy
    
    name_to_key = lambda name: sum([elem * i**3 for elem, i in enumerate(bytearray(name, "utf-8"))])
    
    pnames = ['Lynn Weaver', 'Marlana Rangnow', 'Keena Armwood', 'William Vale', 'Sandra Shu', 'Alexander Sims', 'Joseph Alexander', 'Ruth Aldous', 'Henry Rew', 'Jeffery Mikolajczyk', 'Brett Munroe', 'Eleanor May', 'Jeffrey German', 'David Martinez', 'Francis Lockhart', 'Theresa Pishko', 'Randall Henderson', 'Harvey Mccracken', 'Nicole Allen', 'Jonathan Freeland', 'Lois Morris', 'Florence Frazier', 'Brandi Cox', 'Joseph Davis', 'Virginia Pearson', 'Christopher Langholz', 'Deanna Bowman', 'Weston Keeler', 'Allie Melancon', 'Jackie Finneran', 'John Furnace', 'Jesus Isaacson', 'Yuette Dalessio', 'Ronald Eastman', 'Brian Harrison', 'Erin Wallace', 'Lawrence Rand', 'James Schlossberg', 'Jeffrey Mccrary', 'Jesse Phillips', 'Katie Gillis', 'Randall Tyler', 'Rose Gonzales', 'Jacalyn Randolph', 'Angela Mease', 'Linda Wagner', 'Lacey Wraight', 'Patsy Lefort', 'Judith Song', 'Carmen Markham', 'Mark Weinstein', 'Brian Evans', 'Nicole Sikes', 'Gertrude Morales', 'Imelda Hemming', 'Freddy Lunde', 'Patricia Mcdonald', 'Beverly Cargill', 'Imelda Smith', 'Phillip Bonner', 'Michael Winkelpleck', 'Damion Spann', 'Josue Hirschman', 'Carla Plummer', 'Wilma Canales', 'Elizabeth Matthews', 'Norman Friedman', 'Jack Sutton', 'Leanne Rodriguez', 'Aaron Bragg', 'Mary Saucier', 'Kathleen Fleming', 'Virginia Cleveland', 'Latrice Thorn', 'George Massey', 'Tom Hampton', 'Mary Scott', 'Cory Saunders', 'Brian Williams', 'Patrick Wolfinger', 'Charles Cuevas', 'Robert Ellis', 'Michael Hinson', 'Charles Martinez', 'Evelyn Rowe', 'Andy Patillo', 'Deanna Collins', 'Richard Bryant', 'Joel Barash', 'Royce Jones', 'Jessica Jones', 'Alex Hancock', 'Joseph Champion', 'Brandon Grant', 'Dale Green', 'Kathy Petersen', 'Nancy Landry', 'Joan Kershner', 'Michael White', 'Robert Joseph']
    pkeys = [name_to_key(name) for name in pnames]
    
    nnames = ['Jennifer Kolinski', 'Bill Inman', 'Marvin Patterson', 'Robert Wilson', 'Linda Wang', 'Daniel Heise', 'Jacqueline Dicicco', 'Charles Weston', 'Cynthia Jackson', 'Miriam Treisch', 'Carlos Ewing', 'John Rogers', 'Lisa Kay', 'Traci Johnson', 'Hannah Vant', 'Jeanne Westendorf', 'Sarah Mullins', 'Lucius Sadler', 'Sheila Pullon', 'Horace Wentz', 'Maureen Hall', 'Irene Cook', 'Elizabeth Kearney', 'Luis Hixon', 'Theodore Acosta', 'Michael Benbow', 'Nicholas Pierce', 'Madeline Averitt', 'Mary Leake', 'Jimmie Hurt', 'David Decker', 'Timothy Johnson', 'Kenneth Kaplan', 'Shirley Fitch', 'Dana Peterson', 'Jonathan Wiggins', 'Courtney Hudson', 'Jo Wickus', 'Kareem Reidy', 'Laura Beirne', 'Jeanne Vega', 'Charles Taylor', 'Barbara Woods', 'Clifford Reid', 'Nancy Jackson', 'Ernest Viles', 'Gary Johnson', 'Janice Quick', 'Lara Peter', 'Jesse Gaunce', 'Douglas Jones', 'Norma Naber', 'Lou Dickey', 'Maria Stocker', 'Don Krause', 'Jeffrey Yap', 'Gene Carney', 'Francis Shackley', 'Michael Pimenta', 'Robbie Williams', 'Miguel Soltys', 'Janice Drummond', 'Lisa Hoy', 'Timothy Hedrick', 'Donald Mckenna', 'William Young', 'Robert Sanders', 'Sheridan Pears', 'Maricela Schoenfeld', 'Jane Faw', 'Victoria Meyer', 'Aaron Gentry', 'Eugene Isom', 'David Johnson', 'Rosella Frye', 'Martha Jaworowski', 'Louis Brandly', 'Herbert Hayes', 'Donita Alessio', 'Nancy Jacksohn', 'Ernest Baughn', 'Richard Gibbs', 'Maria Lassalle', 'Andres Moreles', 'Gilberte Ambrose', 'Kermit Ayer', 'Tori Henschel', 'Peter Benett', 'Robert Ryan', 'John Funk', 'Jennifer Miller', 'Anne Brown', 'Jacqueline Fillare', 'Randy Kornreich', 'Emily Carl', 'Charles Liddle', 'Maryjane Henderson', 'Margaret Ramon', 'William Zamora', 'Teresa Depew']
    nkeys = [name_to_key(name) for name in nnames]
    
    pdata = [entry for entry in zip(pkeys, pnames)]
    ndata = [entry for entry in zip(nkeys, nnames)]
    
    t = Hashtable()
    
    print("test build")

    t.build(pdata)
    
    if len(t.table) == 0:
        print("unsuccessfull")
    else:
        print("successfull")
    
        print(t)
        print()
        print("test find with data not in table")
        
        for i in range(10):
            print("successfull" if t.find(random.choice(ndata)) is None else "unsuccessfull")
            
        print("test find with data in table")
            
        for i in range(10):
            print("successfull" if t.find(random.choice(pdata)) is not None else "unsuccessfull")
            
        print("test remove with elements not in table")
        
        s = copy.copy(t)
        
        for i in range(10):
            elem = random.choice(ndata)
            t.remove(elem)
            print("successfull" if t == s else "unsuccessfull")
        
        print("test remove with elements in table")
        
        for i in range(10):
            elem = random.choice(pdata)
            t.remove(elem)
            print("successfull" if t.find(elem) is None else "unsuccessfull")
