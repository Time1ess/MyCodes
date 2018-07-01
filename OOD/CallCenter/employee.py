import logging
import time

from random import random
from threading import Event, Thread

from level import Level


class Employee(Thread):
    SOLVE_PROB = 0
    _available = False
    _call_center = None
    _call = None
    RETRY_TIMES = 0

    def __init__(self):
        super().__init__()
        self._call_event = Event()
        self._level = Level(Level.NOTSET)

    @property
    def level(self):
        return self._level

    @property
    def call_center(self):
        return self._call_center

    @call_center.setter
    def call_center(self, cc):
        self._call_center = cc

    @property
    def available(self):
        return self._available

    def setAvailable(self):
        self._available = True

    def setUnavailable(self):
        self._available = False

    def handle_call(self, call):
        self._call = call
        self._call_event.set()

    def _handle(self):
        cnt = 0
        while cnt < self.RETRY_TIMES:
            prob = random()
            time.sleep(0.2)
            self._call.add_conversation('%d %f' % (self.level.level, prob))
            solved = prob <= self.SOLVE_PROB
            if solved:
                logging.debug('Succeed at level ' + str(self.level))
                self._call.set_solved()
                return True
            cnt += 1
        logging.debug('Failed at level ' + str(self.level))
        return False

    def run(self):
        while True:
            self._call_event.wait()
            self._call_event.clear()
            logging.debug('Handling call at level ' + str(self.level))
            self._handle()
            self._call_center.employee_finished(self, self._call)


class Respondent(Employee):
    SOLVE_PROB = 0.2
    RETRY_TIMES = 3

    def __init__(self):
        super().__init__()
        self._level = Level(Level.RESPONDENT)


class Director(Employee):
    SOLVE_PROB = 0.4
    RETRY_TIMES = 2

    def __init__(self):
        super().__init__()
        self._level = Level(Level.DIRECTOR)


class Manager(Employee):
    SOLVE_PROB = 0.7
    RETRY_TIMES = 1

    def __init__(self):
        super().__init__()
        self._level = Level(Level.MANAGER)
