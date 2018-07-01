import logging

from queue import Queue

from call import Call
from level import Level


class CallCenter:
    def __init__(self):
        self._employees = {}
        self._queue_calls = {}

    @property
    def employees(self):
        return self._employees

    @property
    def queue_calls(self):
        return self._queue_calls

    def set_employees(self, level, employees):
        self._employees[level] = employees
        for employee in employees:
            employee.call_center = self

    def initialize_queue_level_calls(self, level, num_max_calls):
        assert (level not in self._queue_calls
                or len(self._queue_calls[level]) == 0)
        self._queue_calls[level] = Queue(num_max_calls)

    def get_employee(self, level):
        '''Return a employee for this call.

        If return is None, then no employee is available at this time.
        '''
        for employee in self.employees[level]:
            if employee.available:
                return employee
        return None

    def dispatch_call(self, caller):
        '''Assign a call to an employee.

        If no employees are available, queue this call.
        '''
        call = Call(caller)
        self._dispatch_call(call)

    def _dispatch_call(self, call):
        level = call.level.level
        employee = self.get_employee(level)
        if employee is not None:
            employee.setUnavailable()
            employee.handle_call(call)
            return True
        elif not self._queue_calls[level].full():
            self._queue_calls[level].put(call)
            return True
        return False

    def employee_finished(self, employee, call):
        '''Handle result of the call assigned to employee.

        If call is None, no need to process, else a high level employee
        required.
        '''
        employee.setAvailable()
        if call.solved:
            logging.debug('Call solved at level ' + str(call.level))
            return
        if not call.level.increment():
            # Max level exceed, cannot to continue
            return
        logging.debug("Increment Level")
        self._dispatch_call(call)
        self.dispatch_queue_calls()

    def _dispatch_queue_level_calls(self, level):
        employee = self.get_employee(level)
        while not self._queue_calls[level].empty() and employee:
            call = self._queue_calls[level].get()
            employee.handle_call(call)
            employee = self.get_employee(level)

    def dispatch_queue_calls(self):
        '''Try to resolve calls in queue.'''
        self._dispatch_queue_level_calls(Level.RESPONDENT)
        self._dispatch_queue_level_calls(Level.DIRECTOR)
        self._dispatch_queue_level_calls(Level.MANAGER)
