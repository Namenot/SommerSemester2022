from aufgabe2 import *

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
    
    print("merge_sort works with numbers:", is_sorted(merge_sort(s_n.copy())))
    print("merge_sort works with strings:", is_sorted(merge_sort(s_s.copy())))
    print("quick_sort_mid works with numbers:", is_sorted(quick_sort_mid(s_n.copy())))
    print("quick_sort_mid works with strings:", is_sorted(quick_sort_mid(s_s.copy())))
    print("quick_sort_rand works with numbers:", is_sorted(quick_sort_rand(s_n_b.copy())))
    print("quick_sort_rand works with strings:", is_sorted(quick_sort_rand(s_s_b.copy())))
    print()
    print("merge_sort time on numbers: {:5.3f}".format(measure_time(merge_sort, s_n.copy())))
    print("merge_sort time on strings: {:5.3f}".format(measure_time(merge_sort, s_s.copy())))
    print("quick_sort_mid time on numbers: {:5.3f}".format(measure_time(quick_sort_mid, s_n.copy())))
    print("quick_sort_mid time on string: {:5.3f}".format(measure_time(quick_sort_mid, s_s.copy())))
    print("quick_sort_rand time on numbers: {:5.3f}".format(measure_time(quick_sort_rand, s_n_b.copy())))
    print("quick_sort_rand time on string: {:5.3f}".format(measure_time(quick_sort_rand, s_s_b.copy())))
