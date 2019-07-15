#!/bin/bash
for i in {135..140}; do
    echo "test $i"
    ./bof7 `python2 -c "print('a'*$i)"`
done
