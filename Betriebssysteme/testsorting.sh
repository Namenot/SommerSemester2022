#! /bin/bash

# SECONDS is a bash special variable that returns the seconds since set.
start_time=$(date +%s)

echo "Sorting all files"
./wsort < sortierlisten/wlist0 > sortierlisten/wlist0.mine
./wsort < sortierlisten/wlist0 > sortierlisten/wlist0.mine
./wsort < sortierlisten/wlist1 > sortierlisten/wlist1.mine
./wsort < sortierlisten/wlist2 > sortierlisten/wlist2.mine
./wsort < sortierlisten/wlist3 > sortierlisten/wlist3.mine
./wsort < sortierlisten/wlist4 > sortierlisten/wlist4.mine
./wsort < sortierlisten/wlist5 > sortierlisten/wlist5.mine
./wsort < sortierlisten/wlist6 > sortierlisten/wlist6.mine

echo "Done sorting"
echo "Comparing the output"

diff -q -s sortierlisten/wlist0.mine sortierlisten/wlist0.bsteam
diff -q -s sortierlisten/wlist1.mine sortierlisten/wlist1.bsteam
diff -q -s sortierlisten/wlist2.mine sortierlisten/wlist2.bsteam
diff -q -s sortierlisten/wlist3.mine sortierlisten/wlist3.bsteam
diff -q -s sortierlisten/wlist4.mine sortierlisten/wlist4.bsteam
diff -q -s sortierlisten/wlist5.mine sortierlisten/wlist5.bsteam
diff -q -s sortierlisten/wlist6.mine sortierlisten/wlist6.bsteam

end_time=$(date +%s)
elapsed=$(( end_time - start_time ))
echo $elapsed