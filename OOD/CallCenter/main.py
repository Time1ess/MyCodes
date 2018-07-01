import logging
import sys
import time

from random import choices, random
from string import ascii_lowercase
from itertools import chain

from call_center import CallCenter
from employee import Respondent, Director, Manager
from level import Level


logging.basicConfig(
    level=logging.DEBUG,
    stream=sys.stdout,
)
CALL_PROB = 0.3
SLEEP_TIME = 0.01


def main():
    center = CallCenter()
    respondents = [Respondent() for _ in range(10)]
    directors = [Director() for _ in range(5)]
    managers = [Manager() for _ in range(1)]
    center.set_employees(Level.RESPONDENT, respondents)
    center.set_employees(Level.DIRECTOR, directors)
    center.set_employees(Level.MANAGER, managers)
    center.initialize_queue_level_calls(Level.RESPONDENT, 20)
    center.initialize_queue_level_calls(Level.DIRECTOR, 10)
    center.initialize_queue_level_calls(Level.MANAGER, 3)
    for employee in chain(respondents, directors, managers):
        employee.start()
        employee.setAvailable()
    fmt = '[Status]L0:%2d L1:%2d L2:%2d\r'
    while True:
        if random() <= CALL_PROB:
            caller = ''.join(choices(ascii_lowercase, k=5))
            logging.debug('New caller: ' + caller)
            center.dispatch_call(caller)
        time.sleep(SLEEP_TIME)
        sys.stdout.flush()
        queue_calls = center.queue_calls
        sys.stdout.write(fmt % (queue_calls[Level.RESPONDENT].qsize(),
                                queue_calls[Level.DIRECTOR].qsize(),
                                queue_calls[Level.MANAGER].qsize()))


if __name__ == '__main__':
    main()
