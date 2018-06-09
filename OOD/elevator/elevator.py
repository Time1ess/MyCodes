import random
import time
import logging
import sys

from collections import deque

UP = 0x1
DOWN = 0x10
ALL = 0x11

MAX_ROOMS = 10
MAX_FLOOR = 10
MIN_FLOOR = 1
EVENT_PROB = 0.15
ELEVATORS = 2

logging.basicConfig(
    stream=sys.stdout,
    level=logging.INFO)


class Event:
    def __init__(self, floor):
        self.floor = floor

    def get_destinations(self, direction):
        if direction == UP:
            min_floor, max_floor = self.floor + 1, MAX_FLOOR
        else:
            min_floor, max_floor = MIN_FLOOR, self.floor - 1
        num_floors = max((max_floor - min_floor) // 2, 1)
        floors = list(range(min_floor, max_floor + 1))
        random.shuffle(floors)
        floors = floors[:num_floors]
        destinations = {f: random.randint(1, 3) for f in floors}
        return destinations

    def __str__(self):
        return '<Event {:2d}>'.format(self.floor)


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

    def available(self, e):
        if self.event is not None:
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
    return Event(floor)


def main():
    elevators = [Elevator(i) for i in range(ELEVATORS)]
    scheduler = Scheduler(elevators)
    while True:
        if should_generate_event():
            e = generate_event()
            logging.info(" " * 10 + "New event: {}".format(e))
            scheduler.add_event(e)
        scheduler.run()
        time.sleep(0.01)


if __name__ == '__main__':
    main()
