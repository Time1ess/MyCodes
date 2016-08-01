#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-07-20 15:40
# Last modified: 2016-07-20 15:47
# Filename: amazing.py
# Description:
n = 3
m = 1<<n

for i in range(n):
    print 'In round', i
    for j in range(m):
        print '<', j, '> VS. ',
        for k in range(1<<i, 1<<(i+1)):
            print j^k,
        print
