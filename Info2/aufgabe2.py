def merge_sort(s):
    if len(s) <= 1:
        return s
    else:
        m = len(s) // 2
        s1 = merge_sort(s[:m])
        s2 = merge_sort(s[m:])
        return merge(s1, s2)
    
def merge(s1, s2):
    """ s1 and s2 are of type 'list' with elements of type
    'str', 'float' or 'int'
    
    returns s1 and s2 merged and sorted in ascending order """

def quick_sort(s, l, r, pivot_function):
    """ s is of type 'list' with elements of type
    'str', 'float' or 'int'; l and r are of type 'int'
    and determine the bounds to sort within;
    pivot_function is a function that gets l and r
    as input and returns an 'int' within l,...,r
    
    returns s sorted in ascending order """

def mid_pivot(l, r):
    return (l + r) // 2

def random_pivot(l, r):
    """ returns a random pivot within l,..,r
    where l and r are of type 'int' """
    
    import random
    return

def quick_sort_mid(s):
    quick_sort(s, 0, len(s) - 1, mid_pivot)
    return s
    
def quick_sort_rand(s):
    quick_sort(s, 0, len(s) - 1, random_pivot)
    return s

quick_sort_faster = False
merge_sort_faster = False

matrikelnummern = [] # Enter your Matrikelnummer here
                     # for example matrikelnummern = [123] for one student 
                     # or matrikelnummern = [123, 456] for two students
