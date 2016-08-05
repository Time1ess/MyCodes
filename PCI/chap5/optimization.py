#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-03 14:18
# Last modified: 2016-08-03 16:15
# Filename: optimization.py
# Description:
import time
import random
import math


people = [('Seymour', 'BOS'),
          ('Franny', 'DAL'),
          ('Zooey', 'CAK'),
          ('Walt', 'MIA'),
          ('Buddy', 'ORD'),
          ('Les', 'OMA')]

destination = 'LGA'

flights = {}
with open("schedule.txt", "r") as f:
    for line in f:
        origin, dest, depart, arrive, price = line.strip().split(',')
        flights.setdefault((origin, dest), [])
        flights[(origin, dest)].append((depart, arrive, int(price)))


def get_minutes(t):
    x = time.strptime(t, '%H:%M')
    return x[3]*60 + x[4]


def print_schedule(r):
    for d in xrange(len(r)/2):
        name = people[d][0]
        origin = people[d][1]
        out = flights[(origin, destination)][r[2*d]]
        ret = flights[(destination, origin)][r[2*d + 1]]
        print '%10s%10s  %5s-%5s $%3s %5s-%5s $%3s' %\
            (name, origin, out[0], out[1], out[2], ret[0], ret[1], ret[2])


def schedule_cost(sol):
    total_price = 0
    latest_arrival = 0
    earliest_dep = 24*60

    for d in xrange(len(sol)/2):
        origin = people[d][1]
        out = flights[(origin, destination)][int(sol[2*d])]
        ret = flights[(destination, origin)][int(sol[2*d+1])]

        total_price += out[2] + ret[2]

        if latest_arrival < get_minutes(out[1]):
            latest_arrival = get_minutes(out[1])
        if earliest_dep > get_minutes(ret[0]):
            earliest_dep = get_minutes(ret[0])

    total_wait = 0
    for d in xrange(len(sol)/2):
        origin = people[d][1]
        out = flights[(origin, destination)][int(sol[2*d])]
        ret = flights[(destination, origin)][int(sol[2*d+1])]

        total_wait += latest_arrival - get_minutes(out[1])
        total_wait += get_minutes(ret[0]) - earliest_dep

    if latest_arrival > earliest_dep:
        total_price += 50

    return total_price+total_wait


def random_optimize(domain, cost_func, iter_times=1000):
    best = 1e10-1
    best_r = None
    for i in xrange(iter_times):
        r = [random.randint(domain[j][0], domain[j][1])
             for j in xrange(len(domain))]

        cost = cost_func(r)

        if cost < best:
            best = cost
            best_r = r
    print 'Solution:', best_r, '|Cost:', cost
    return r


def hill_climb(domain, cost_func):
    sol = [random.randint(domain[j][0], domain[j][1])
           for j in xrange(len(domain))]

    while True:
        neighbors = []
        for j in xrange(len(domain)):
            if sol[j] > domain[j][0]:
                neighbors.append(sol[0:j]+[sol[j]-1]+sol[j+1:])
            if sol[j] < domain[j][1]:
                neighbors.append(sol[0:j]+[sol[j]+1]+sol[j+1:])

        current = cost_func(sol)
        best = current
        for j, tmp in enumerate(neighbors):
            cost = cost_func(tmp)
            if cost < best:
                best = cost
                sol = tmp
        if best == current:
            break
    return sol


def annealing_optimization(domain, cost_func, T=10000, cool=0.95, step=1):
    vec = [random.randint(domain[i][0], domain[i][1])
           for i in xrange(len(domain))]

    while T > 0.1:
        i = random.randint(0, len(domain)-1)

        direction = random.randint(-step, step)

        vecb = vec[:]
        vecb[i] += direction
        vecb[i] = max(domain[i][0], vecb[i])
        vecb[i] = min(domain[i][1], vecb[i])

        ea = cost_func(vec)
        eb = cost_func(vecb)

        if eb < ea or random.random() < pow(math.e, -(eb-ea)/T):
            vec = vecb

        T *= cool
    return vec


def genetic_optimization(domain, cost_func, popsize=50, step=1,
                         mutprob=0.2, elite=0.2, iter_times=100):
    def mutate(vec):
        while True:
            i = random.randint(0, len(domain)-1)
            if random.random() < 0.5 and vec[i] > domain[i][0]:
                return vec[0:i]+[vec[i]-step]+vec[i+1:]
            elif vec[i] < domain[i][1]:
                return vec[0:i]+[vec[i]+step]+vec[i+1:]

    def crossover(r1, r2):
        i = random.randint(1, len(domain)-2)
        return r1[0:i]+r2[i:]

    pop = []
    for i in xrange(popsize):
        vec = [random.randint(domain[j][0], domain[j][1])
               for j in xrange(len(domain))]
        pop.append(vec)

    top_elite = int(elite*popsize)

    for i in xrange(iter_times):
        scores = [(cost_func(v), v) for v in pop]
        scores.sort()
        ranked = [v for s, v in scores]
        pop = ranked[0:top_elite]

        while len(pop) < popsize:
            if random.random() < mutprob:
                c = random.randint(0, top_elite)
                pop.append(mutate(ranked[c]))
            else:
                c1 = c2 = -1
                while c1 == c2:
                    c1 = random.randint(0, top_elite)
                    c2 = random.randint(0, top_elite)
                pop.append(crossover(ranked[c1], ranked[c2]))
        print scores[0][0]
    return scores[0][1]
