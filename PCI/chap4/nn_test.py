#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-02 15:23
# Last modified: 2016-08-02 15:52
# Filename: nn_test.py
# Description:
import nn
mynet = nn.searchnet()
mynet.drop_tables()
mynet.make_tables()

wWorld, wRiver, wBank = 101, 102, 103
uWorldBank, uRiver, uEarth = 201, 202, 203

# Test one
mynet.generate_hiddennode([wWorld, wBank], [uWorldBank, uRiver, uEarth])
mynet.cur.execute('select * from wordhidden')
for c in mynet.cur.fetchall():
    print c[1:]
mynet.cur.execute('select * from hiddenurl')
for c in mynet.cur.fetchall():
    print c[1:]

# Test two
print mynet.get_result([wWorld,wBank], [uWorldBank, uRiver, uEarth])

# Test three
print
mynet.train_query([wWorld, wBank], [uWorldBank, uRiver, uEarth], uWorldBank)
print mynet.get_result([wWorld, wBank], [uWorldBank, uRiver, uEarth])

# Test four
print
all_urls = [uWorldBank, uRiver, uEarth]
for i in xrange(30):
    mynet.train_query([wWorld, wBank], all_urls, uWorldBank)
    mynet.train_query([wRiver, wBank], all_urls, uRiver)
    mynet.train_query([wWorld], all_urls, uEarth)

print mynet.get_result([wWorld, wBank], all_urls)
print mynet.get_result([wRiver, wBank], all_urls)
print mynet.get_result([wBank], all_urls)
