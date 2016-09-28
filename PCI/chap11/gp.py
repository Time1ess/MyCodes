#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-09-27 10:09
# Last modified: 2016-09-28 10:08
# Filename: gp.py
# Description:
__metaclass__ = type
from random import random, randint, choice
from copy import deepcopy
from math import log


class fwrapper:
    def __init__(self, function, child_count, name):
        self.function = function
        self.child_count = child_count
        self.name = name


class node:
    def __init__(self, fw, children):
        self.function = fw.function
        self.name = fw.name
        self.children = children

    def evaluate(self, inp):
        results = [n.evaluate(inp) for n in self.children]
        return self.function(results)

    def display(self, indent=0):
        print ' '*indent + self.name
        for c in self.children:
            c.display(indent+1)


class param_node:
    def __init__(self, idx):
        self.idx = idx

    def evaluate(self, inp):
        return inp[self.idx]

    def display(self, indent=0):
        print '%sp%d' % (' '*indent, self.idx)


class const_node:
    def __init__(self, v):
        self.v = v

    def evaluate(self, inp):
        return self.v

    def display(self, indent=0):
        print '%s%d' % (' '*indent, self.v)


addw = fwrapper(lambda l: l[0]+l[1], 2, 'add')
subw = fwrapper(lambda l: l[0]-l[1], 2, 'subtract')
mulw = fwrapper(lambda l: l[0]*l[1], 2, 'multiply')


def if_func(l):
    if l[0]:
        return l[1]
    else:
        return l[2]


ifw = fwrapper(if_func, 3, 'if')


def is_greater(l):
    if l[0] > l[1]:
        return True
    else:
        return False


gtw = fwrapper(is_greater, 2, 'is_greater')

func_list = [addw, subw, mulw, ifw, gtw]


def example_tree():
    return node(ifw,
                [node(gtw, [param_node(0), const_node(3)]),
                 node(addw, [param_node(1), const_node(5)]),
                 node(subw, [param_node(1), const_node(2)])])


def make_random_tree(pc, max_depth=4, fpr=0.5, ppr=0.6):
    if random() < fpr and max_depth > 0:
        f = choice(func_list)
        children = [make_random_tree(pc, max_depth-1, fpr, ppr)
                    for i in xrange(f.child_count)]
        return node(f, children)
    elif random() < ppr:
        return param_node(randint(0, pc-1))
    else:
        return const_node(randint(0, 10))


def hidden_function(x, y):
    return x**2+2*y+3*x+5


def build_hidden_set():
    rows = []
    for i in xrange(200):
        x = randint(0, 40)
        y = randint(0, 40)
        rows.append([x, y, hidden_function(x, y)])
    return rows


def score_function(tree, s):
    dif = 0
    for data in s:
        v = tree.evaluate([data[0], data[1]])
        dif += abs(v-data[2])
    return dif


def mutate(t, pc, prob_change=0.1):
    if random() < prob_change:
        return make_random_tree(pc)
    else:
        result = deepcopy(t)
        if isinstance(t, node):
            result.children = [mutate(c, pc, prob_change) for c in t.children]
        return result


def crossover(t1, t2, prob_swap=0.7, top=1):
    if random() < prob_swap and not top:
        return deepcopy(t2)
    else:
        result = deepcopy(t1)
        if isinstance(t1, node) and isinstance(t2, node):
            result.children = [crossover(c, choice(t2.children), prob_swap, 0)
                               for c in t1.children]
        return result


def evolve(pc, popsize, rank_function, max_gen=500,
           mutation_rate=0.1, breeding_rate=0.4, pexp=0.7, pnew=0.05):
    def select_index():
        return int(log(random())/log(pexp))

    population = [make_random_tree(pc) for i in xrange(popsize)]
    for i in xrange(max_gen):
        scores = rank_function(population)
        print 'Generation %d / %d: ' % (i+1, max_gen), scores[0][0]
        if scores[0][0] == 0:
            break

        new_pop = [scores[0][1], scores[1][1]]
        while len(new_pop) < popsize:
            if random() > pnew:
                new_pop.append(
                    mutate(crossover(scores[select_index()][1],
                                     scores[select_index()][1],
                                     prob_swap=breeding_rate),
                           pc, prob_change=mutation_rate))
            else:
                new_pop.append(make_random_tree(pc))
        population = new_pop

    scores[0][1].display()
    return scores[0][1]


def get_rank_function(dataset):
    def rank_function(population):
        scores = [(score_function(t, dataset), t) for t in population]
        scores.sort()
        return scores
    return rank_function

def grid_game(p):
    max_grid = (3, 3)
    last_move = [-1, -1]
    location = [[randint(0, max_grid[0]), randint(0, max_grid[1])]]

    location.append([(location[0][0]+2)%4, (location[0][1]+2)%4])

    for o in xrange(50):
        for i in xrange(2):
            locs = location[i][:]+location[1-i][:]
            locs.append(last_move[i])
            move = p[i].evaluate(locs)%4

            if last_move[i] == move:
                return 1-i
            last_move[i] = move
            if move == 0:
                location[i][0] -= 1
                if location[i][0] < 0:
                    location[i][0] = 0
            elif move == 1:
                location[i][0] += 1
                if location[i][0] > max_grid[0]:
                    location[i][0] = max_grid[0]
            elif move == 2:
                location[i][1] -= 1
                if location[i][1] < 0:
                    location[i][1] = 0
            elif move == 3:
                location[i][1] += 1
                if location[i][1] > max_grid[1]:
                    location[i][1] = max_grid[1]

            if location[i] == location[1-i]:
                return i
    return -1


def tournament(pl):
    losses = [0 for p in pl]

    for i in xrange(len(pl)):
        for j in xrange(len(pl)):
            if i == j:
                continue

            winner = grid_game([pl[i], pl[j]])

            if winner == 0:
                losses[j] += 2
            elif winner == 1:
                losses[i] += 2
            elif winner == -1:
                losses[i] += 1
                losses[j] += 1
    z = zip(losses, pl)
    z.sort()
    return z


class human_player:
    def evaluate(self, board):
        me = tuple(board[0:2])
        others = [tuple(board[x:x+2]) for x in xrange(2, len(board)-1, 2)]

        for i in xrange(4):
            for j in xrange(4):
                if (i, j) == me:
                    print 'O',
                elif (i, j) in others:
                    print 'X',
                else:
                    print '.',
            print

        print 'Your last move was %d' % board[len(board)-1]
        print ' 0'
        print '2 3'
        print ' 1'
        print 'Enter move: ',
        move = int(raw_input())
        return move
