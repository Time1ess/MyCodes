#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-04 14:44
# Last modified: 2016-08-05 14:52
# Filename: dorm.py
# Description:
import random
import math

dorms = ['Zeus', 'Athena', 'Hercules', 'Bacchus', 'Pluto']

prefs = [('Toby', ('Bacchus', 'Hercules')),
         ('Steve', ('Zeus', 'Pluto')),
         ('Andrea', ('Athena', 'Zeus')),
         ('Sarah', ('Zeus', 'Pluto')),
         ('Davd', ('Athena', 'Bacchus')),
         ('Jeff', ('Hercules', 'Pluto')),
         ('Fred', ('Pluto', 'Ahtena')),
         ('Suzie', ('Bacchus', 'Hercules')),
         ('Laura', ('Bacchus', 'Hercules')),
         ('Neil', ('Hercules', 'Athena'))]

domain = [(0, (len(dorms)*2)-i-1) for i in xrange(0, len(dorms)*2)]


def print_solution(vec):
    slots = []
    for i in xrange(len(dorms)):
        slots += [i, i]

    for i in xrange(len(vec)):
        x = int(vec[i])

        dorm = dorms[slots[x]]
        print prefs[i][0], dorm
        del slots[x]

def dorm_cost(vec):
    cost = 0
    slots = []
    for i in xrange(len(dorms)):
        slots += [i, i]

    for i in xrange(len(vec)):
        x = int(vec[i])
        dorm = dorms[slots[x]]
        pref = prefs[i][1]

        if pref[0] == dorm:
            cost += 0
        elif pref[1] == dorm:
            cost += 1
        else:
            cost += 3

        del slots[x]

    return cost
