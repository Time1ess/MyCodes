#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-09 09:50
# Last modified: 2017-02-09 11:03
# Filename: conway.py
# Description:
from random import sample, random
from collections import namedtuple


ALIVE = '*'
EMPTY = '-'
TICK = object()

Query = namedtuple('Query', ('y', 'x'))
Transition = namedtuple('Transition', ('y', 'x', 'state'))


def count_neighbors(y, x):
    n_ = yield Query(y+1, x+0)  # North
    ne = yield Query(y+1, x+1)  # Northeast
    e_ = yield Query(y+0, x+1)  # East
    se = yield Query(y-1, x+1)  # Southeast
    s_ = yield Query(y-1, x+0)  # South
    sw = yield Query(y-1, x-1)  # Southwest
    w_ = yield Query(y+0, x-1)  # West
    nw = yield Query(y+1, x-1)  # Northwest
    neighbor_states = [n_, ne, e_, se, s_, sw, w_, nw]
    count = 0
    for state in neighbor_states:
        if state == ALIVE:
            count += 1
    return count


def test_count_neighbors():
    it = count_neighbors(10, 5)
    q1 = next(it)
    print('1st yield: ', q1)
    q2 = it.send(ALIVE)
    print('2nd yield: ', q2)
    q3 = it.send(ALIVE)
    print('3rd yield: ', q3)
    q4 = it.send(ALIVE)
    print('4th yield: ', q4)
    q5 = it.send(ALIVE)
    print('5th yield: ', q5)
    q6 = it.send(ALIVE)
    print('6th yield: ', q6)
    q7 = it.send(ALIVE)
    print('7th yield: ', q7)
    q8 = it.send(ALIVE)
    print('8th yield: ', q8)
    try:
         count = it.send(EMPTY)
    except StopIteration as e:
        print('Count: ', e.value)


def game_logic(state, neighbors):
    if state == ALIVE:
        if neighbors < 2:
            return EMPTY
        elif neighbors > 3:
            return EMPTY
    else:
        if neighbors == 3:
            return ALIVE
    return state


def step_cell(y, x):
    state = yield Query(y, x)
    neighbors = yield from count_neighbors(y, x)
    next_state = game_logic(state, neighbors)
    yield Transition(y, x, next_state)


def test_step_cell():
    it = step_cell(10, 5)
    q0 = next(it)
    print('Me:        ', q0)
    q1 = it.send(ALIVE)
    print('Q1:        ', q1)
    q2 = it.send(ALIVE)
    print('Q2:        ', q2)
    q3 = it.send(ALIVE)
    print('Q3:        ', q3)
    q4 = it.send(ALIVE)
    print('Q4:        ', q4)
    q5 = it.send(ALIVE)
    print('Q5:        ', q5)
    q6 = it.send(ALIVE)
    print('Q6:        ', q6)
    q7 = it.send(ALIVE)
    print('Q7:        ', q7)
    q8 = it.send(ALIVE)
    print('Q8:        ', q8)
    t1 = it.send(EMPTY)
    print('Outcome:   ', t1)


def simulate(height, width):
    while True:
        for y in range(height):
            for x in range(width):
                yield from step_cell(y, x)
        yield TICK


class Grid:
    def __init__(self, height, width):
        self.height = height
        self.width = width
        self.rows = []
        for _ in range(self.height):
            self.rows.append([EMPTY for i in range(self.width)])

    def __str__(self):
        return '\n'.join([''.join(row) for row in self.rows])

    def query(self, y, x):
        return self.rows[y % self.height][x % self.width]

    def assign(self, y, x, state):
        self.rows[y % self.height][x % self.width] = state


def live_a_generation(grid, sim):
    progeny = Grid(grid.height, grid.width)
    item = next(sim)
    while item is not TICK:
        if isinstance(item, Query):
            state = grid.query(item.y, item.x)
            item = sim.send(state)
        else:
            progeny.assign(item.y, item.x, item.state)
            item = next(sim)
    return progeny


def test_gen_grid(height=5, width=9, alives=5):
    grid = Grid(height, width)
    alive_grids = sample(
        [(y, x) for y in range(height) for x in range(width)], alives)
    for y, x in alive_grids:
        grid.assign(y, x, ALIVE)
#    grid.assign(0, 3, ALIVE)
#    grid.assign(1, 4, ALIVE)
#    grid.assign(2, 2, ALIVE)
#    grid.assign(2, 3, ALIVE)
#    grid.assign(2, 4, ALIVE)
    return grid


def mutation(grid, mute_rate=0.2):
    for y in range(grid.height):
        for x in range(grid.width):
            if random() < mute_rate:
                grid.assign(y, x,
                            EMPTY if grid.query(y, x) == ALIVE else ALIVE)


def test_live_a_generation():
    grid = test_gen_grid()
    print(grid)


class ColumnPrinter:
    def __init__(self, height, width):
        self.height = height
        self.width = width
        self.gens = 0
        self._columns = [[] for i in range(self.height)]

    def append(self, grid_s):
        grid_s = grid_s.split('\n')
        for idx, s in enumerate(grid_s):
            self._columns[idx].append(s)
        self.gens += 1

    def __str__(self):
        fmt = [('{:^'+str(self.width)+'}').format(i) for i in range(self.gens)]
        head = '|'.join(fmt)
        content = '\n'.join(['|'.join(row) for row in self._columns])
        return '\n'.join([head, content])


def test_ColumnPrinter(height=5, width=9, alives=10):
    grid = test_gen_grid(height, width, alives)
    columns = ColumnPrinter(height, width)
    sim = simulate(grid.height, grid.width)
    for i in range(5):
        columns.append(str(grid))
        grid = live_a_generation(grid, sim)
    print(columns)


def test_game(height=5, width=9, alives=5):
    grid = test_gen_grid(height, width, alives)
    sim = simulate(grid.height, grid.width)
    while True:
        print('\n')
        print(grid)
        grid = live_a_generation(grid, sim)
        mutation(grid, 0.01)

test_game(30, 60, 800)
