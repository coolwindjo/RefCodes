cat test.sh
insmod devtest.ko
./apptest Q DIS
./apptest Q EN
cat /proc/interrupts
rmmod devtest.ko
