import random
import time
import logging
import sys

from collections import deque

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

UP = 0x1
DOWN = 0x10
ALL = 0x11

MAX_ROOMS = 10
MAX_FLOOR = 10
MIN_FLOOR = 1
EVENT_PROB = 1
ELEVATORS = 5

logging.basicConfig(
    stream=sys.stdout,
    level=logging.INFO)

events = set()


class Event:
    def __init__(self, floor, direction):
        self.floor = floor
        self.direction = direction

    def get_destinations(self, direction):
        if direction == UP:
            min_floor, max_floor = self.floor + 1, MAX_FLOOR
        else:
            min_floor, max_floor = MIN_FLOOR, self.floor - 1
        num_floors = max((max_floor - min_floor) // 3, 1)
        floors = list(range(min_floor, max_floor + 1))
        random.shuffle(floors)
        floors = floors[:num_floors]
        destinations = {f: random.randint(1, 3) for f in floors}
        return destinations

    def __str__(self):
        return '<Event {:2d}>'.format(self.floor)

    def __hash__(self):
        return self.floor * (1 if self.direction == UP else -1)


class Elevator:
    def __init__(self, idx):
        self.idx = idx
        self.floor = 1
        self.direction = UP
        self.room = MAX_ROOMS
        self.event = None
        self.floor_passengers_out = {
            floor: 0 for floor in range(MIN_FLOOR, MAX_FLOOR+1)}

    @property
    def idle(self):
        return self.empty and not self.event

    @property
    def full(self):
        return self.room == 0

    @property
    def empty(self):
        return self.room == MAX_ROOMS

    def report_idle(self):
        logging.info('Elevator {:2d}: Floor: {:2d}, Idle'.format(
            self.idx, self.floor))

    def process_event(self):
        # Check event happened at this floor
        e = self.event
        if not e or e.floor != self.floor:
            return
        events.remove(e)
        # Set to event direction
        self.direction = e.direction
        logging.info('Elevator {:2d}: Floor: {:2d}, Process event {}'.format(
            self.idx, self.floor, e))
        self.event = None
        destinations = e.get_destinations(self.direction)
        for floor, _num_passengers in destinations.items():
            num_passengers = min(self.room, _num_passengers)
            if num_passengers != 0:
                fmt = 'Elevator {:2d}: Floor: {:2d}, Onboard(->{:2d}): {:2d}'
                logging.info(
                    fmt.format(self.idx, self.floor, floor, num_passengers))
            self.room -= num_passengers
            self.floor_passengers_out[floor] += num_passengers

    def handle_event(self, e):
        logging.info('Elevator {:2d}: Floor: {:2d}, Handle event {}'.format(
            self.idx, self.floor, e))
        assert self.event is None
        self.event = e
        # Move to event floor
        if self.floor > e.floor:
            self.direction = DOWN
        elif self.floor < e.floor:
            self.direction = UP

    def available(self, e):
        if self.idle:
            return True
        if self.event is not None:
            return False
        if self.direction != e.direction:
            return False
        if self.direction == UP and self.floor > e.floor:
            return False
        elif self.direction == DOWN and self.floor < e.floor:
            return False
        return True

    def passengers_in_and_out(self):
        num_passengers_out = self.floor_passengers_out[self.floor]
        self.room += num_passengers_out
        self.floor_passengers_out[self.floor] = 0
        fmt = ('Elevator {:2d}: Floor: {:2d} '
               'Out: {:2d}, Remain: {:2d}')
        logging.info(fmt.format(
            self.idx, self.floor,
            num_passengers_out,
            MAX_ROOMS - self.room))

    def step(self):
        if self.idle:
            self.report_idle()
            return
        self.process_event()
        self.passengers_in_and_out()
        if self.idle:
            return
        # Move to next floor
        if self.direction == UP:
            self.floor += 1
        elif self.direction == DOWN:
            self.floor -= 1
        if self.floor == MAX_FLOOR:
            self.direction = DOWN
        elif self.floor == MIN_FLOOR:
            self.direction = UP


class Scheduler:
    def __init__(self, elevators):
        self.events = deque()
        self.elevators = elevators

    def add_event(self, e):
        self.events.append(e)

    def run(self):
        unhandled_events = deque()
        while self.events:
            e = self.events.popleft()
            best_elevator = None
            for elevator in self.elevators:
                if elevator.available(e):
                    best_elevator = elevator
            if best_elevator is None:
                unhandled_events.append(e)
                logging.info("No elevators available")
                continue
            best_elevator.handle_event(e)
        self.events = unhandled_events
        for elevator in self.elevators:
            elevator.step()


def should_generate_event():
    return random.random() < EVENT_PROB


def generate_event():
    floor = random.randint(MIN_FLOOR, MAX_FLOOR)
    if floor == MIN_FLOOR:
        direction = UP
    elif floor == MAX_FLOOR:
        direction = DOWN
    else:
        direction = random.choice((UP, DOWN))
    e = Event(floor, direction)
    return e


class ElevatorDrawer:
    def __init__(self, num_floors=MAX_FLOOR - MIN_FLOOR + 1,
                 num_elevators=ELEVATORS, floor_height=200, floor_width=200,
                 elevator_width=200, margin=20):
        self.num_floors = num_floors
        self.num_elevators = num_elevators
        self.floor_height = floor_height
        self.floor_width = floor_width
        self.elevator_width = elevator_width
        self.margin = margin
        self.flush_canvas()

    def flush_canvas(self):
        h = self.num_floors * self.floor_height
        w = self.floor_width \
            + self.margin \
            + self.num_elevators * self.elevator_width
        self.pixels = np.zeros((h, w))
        self.shape = self.pixels.shape

    def draw_elevators(self, elevators):
        margin = self.margin
        fw = self.floor_width
        fh = self.floor_height
        ew = self.elevator_width
        for idx, e in enumerate(elevators):
            floor = e.floor
            self.pixels[fh*(floor-1):fh*floor,
                        fw + margin + idx*ew: fw + margin + (idx+1)*ew] = 255

    def draw_events(self, events):
        fh = self.floor_height
        fw = self.floor_width
        for e in events:
            floor = e.floor
            direction = e.direction
            fs = int(fh * (floor - (1 if direction == DOWN else 0.5)))
            fe = int(fh * (floor - (0.5 if direction == DOWN else 0)))
            for idx, row in enumerate(range(fs, fe)):
                if direction == UP:
                    # UP triangle
                    w = int(fw * (1 - idx / (fe - fs)))
                    tw = int((fw - w) / 2)
                else:
                    w = int(fw * idx / (fe - fs))
                    tw = int((fw - w) / 2)
                self.pixels[row, tw:tw+w] = 255

    def draw_floor_lines(self):
        fh = self.floor_height
        for floor in range(self.num_floors):
            fs = floor * fh
            self.pixels[fs:fs+fh//20, :] = 255

    def draw(self, elevators, events):
        self.flush_canvas()
        self.draw_elevators(elevators)
        self.draw_events(events)
        self.draw_floor_lines()

    @property
    def canvas(self):
        return self.pixels


def main():
    elevators = [Elevator(i) for i in range(ELEVATORS)]
    scheduler = Scheduler(elevators)
    drawer = ElevatorDrawer()
    fig = plt.figure()
    im = plt.imshow(drawer.canvas, animated=True, cmap='gray',
                    vmin=0, vmax=255)

    def updatefig(*args):
        if should_generate_event():
            e = generate_event()
            if e not in events:
                logging.info(" " * 10 + "New event: {}".format(e))
                scheduler.add_event(e)
                events.add(e)
        scheduler.run()
        drawer.draw(elevators, events)
        im.set_array(drawer.canvas)
        return im,

    plt.title("Elevators scheduling =.=")
    ani = animation.FuncAnimation(fig, updatefig, interval=50, blit=True)
    plt.show()

if __name__ == '__main__':
    main()
