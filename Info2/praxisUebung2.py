def insertion_sort(s):
    """ s is of type 'list' with elements of type
    'str', 'float' or 'int'
    returns s sorted in ascending order """

    for a in range(0, len(s)-1):
        b = a+1
        tmp = s[b]

        while b > 0 and tmp < s[b-1]:
            s[b] = s[b-1]
            b -= 1
        
        s[b] = tmp

    return s
    
def selection_sort(s):
    """ s is of type 'list' with elements of type
    'str', 'float' or 'int'
    
    returns s sorted in ascending order """

    for i in range(0, len(s) - 1):
        mindex = i
        for j in range(i+1, len(s)):
            if s[j] < s[mindex]:
                mindex = j

        s[i], s[mindex] = s[mindex], s[i]

    return s
    
def bucket_sort(s, n):
    """ s is of type 'list' with elements of type
    'tuple' that contain as first element 'int' in range(1, n)
    and as second element 'str', 'float' or 'int'
    
    returns s sorted in ascending order by first elements of tuples """

    buckets = [[]for i in range(1, n)]

    for i in s:
        buckets[i[0]-1].append(i)
    
    s = []
    for i in buckets:
        s = s + i

    return s

if __name__ == "__main__":
    def is_sorted(s):
        if len(s) == 0: return True
        if not type(s[0]) == type(((),)):
            return all(s[i] <= s[i+1] for i in range(len(s)-1))
        else:
            return all(s[i][0] <= s[i+1][0] for i in range(len(s)-1))
        
    def measure_time(method, *arguments):
        import time
        start = time.process_time()
        method(*arguments)
        end = time.process_time()
        return end-start
    
    import numpy as np
    import string
    import random
    
    chars = string.ascii_uppercase + string.ascii_lowercase + string.digits
    
    n = 1000
    
    s_n = (np.random.rand(n) * n).tolist()
    s_s = ["".join([random.choice(chars) for i in range(6)]) for i in range(n)]
    s_n_b = [(random.randint(1, n-1), s_n[i]) for i in range(len(s_n))]
    s_s_b = [(random.randint(1, n-1), s_s[i]) for i in range(len(s_s))]
    
    print("insertion_sort works with numbers:", is_sorted(insertion_sort(s_n.copy())))
    print("insertion_sort works with strings:", is_sorted(insertion_sort(s_s.copy())))
    print("selection_sort works with numbers:", is_sorted(selection_sort(s_n.copy())))
    print("selection_sort works with strings:", is_sorted(selection_sort(s_s.copy())))
    print("bucket_sort works with numbers:", is_sorted(bucket_sort(s_n_b.copy(), n)))
    print("bucket_sort works with strings:", is_sorted(bucket_sort(s_s_b.copy(), n)))
    print()
    print("insertion_sort time on numbers: {:5.3f}".format(measure_time(insertion_sort, s_n.copy())))
    print("insertion_sort time on strings: {:5.3f}".format(measure_time(insertion_sort, s_s.copy())))
    print("selection_sort time on numbers: {:5.3f}".format(measure_time(selection_sort, s_n.copy())))
    print("selection_sort time on string: {:5.3f}".format(measure_time(selection_sort, s_s.copy())))
    print("bucket_sort time on numbers: {:5.3f}".format(measure_time(bucket_sort, s_n_b.copy(), n)))
    print("bucket_sort time on string: {:5.3f}".format(measure_time(bucket_sort, s_s_b.copy(), n)))
