from sys import argv
from random import gauss
from time import sleep
from queue import Queue
from multiprocessing.managers import BaseManager


class Job:
    def __init__(self, job_id):
        self.job_id = job_id

    def __str__(self):
        return '<Job id={}>'.format(self.job_id)


class Dispatcher:
    def __init__(self, rnd=5, batch=10):
        self.dispatch_queue = Queue()
        self.finished_queue = Queue()
        self.rnd = rnd
        self.batch = batch

    def get_dispatch_queue(self):
        return self.dispatch_queue

    def get_finished_queue(self):
        return self.finished_queue

    def start(self):
        BaseManager.register('get_dispatch_queue',
                             callable=self.get_dispatch_queue)
        BaseManager.register('get_finished_queue',
                             callable=self.get_finished_queue)

        manager = BaseManager(address=('0.0.0.0', 8000),
                              authkey=b'dispatcher')
        manager.start()

        dispatch_queue = manager.get_dispatch_queue()
        finished_queue = manager.get_finished_queue()

        job_id = 0
        unfinished = self.rnd * self.batch
        for rnd in range(self.rnd):
            for i in range(self.batch):
                job = Job(job_id=job_id)
                job_id += 1
                print('Dispatch Job {}'.format(job))
                dispatch_queue.put(job)

            while not dispatch_queue.empty():
                finished_job = finished_queue.get(60)
                unfinished -= 1
                print('Job finished {}'.format(finished_job))
        dispatch_queue.put(None)
        while unfinished > 0:
            finished_job = finished_queue.get(60)
            unfinished -= 1
            print('Job finished {}'.format(finished_job))
        manager.shutdown()


class Worker:
    def start(self):
        BaseManager.register('get_dispatch_queue')
        BaseManager.register('get_finished_queue')

        server = ('127.0.0.1', 8000)
        manager = BaseManager(address=server, authkey=b'dispatcher')
        manager.connect()
        print('Connected to server {}'.format(server))

        dispatch_queue = manager.get_dispatch_queue()
        finished_queue = manager.get_finished_queue()

        while True:
            job = dispatch_queue.get()
            if job is None:
                print('Sentinel Detected, terminating...')
                dispatch_queue.put(job)
                break
            print('Working on job: {}'.format(job))
            work_time = min(2, max(0.5, gauss(1, 1)))
            sleep(work_time)
            print('Job finished: {}'.format(job))
            finished_queue.put(job)


if __name__ == '__main__':
    args = argv[1:]
    if not args:
        print('Args needed')
        exit(-1)
    ptype = args[0]
    if ptype == 'd':
        dispatcher = Dispatcher(*[int(x) for x in args[1:]])
        dispatcher.start()
    else:
        worker = Worker()
        worker.start()
