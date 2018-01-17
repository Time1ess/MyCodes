from random import random
from time import sleep
from threading import Thread, Semaphore, Lock, get_ident
from itertools import chain


N = 4
M = 2
def producer(lock, semaphore):
    for _ in range(M):
        print('Producer {} sleep'.format(get_ident()))
        sleep(1 + random())
        print('Producer {} wakeup'.format(get_ident()))
        lock.acquire()
        print('Producer {} produce'.format(get_ident()))
        semaphore.release()
        lock.release()
    print('Producer {} exit'.format(get_ident()))


def customer(lock, semaphore):
    cnt = 0
    while cnt < N:
        lock.acquire()
        product = semaphore.acquire(blocking=False)
        lock.release()
        if product:
            cnt += 1
            print('Customer {} consume'.format(get_ident()))
        else:
            print('No product, Customer {} sleep'.format(get_ident()))
            sleep(1)
            print('Customer {} wakeup'.format(get_ident()))
    print('Customer {} exit'.format(get_ident()))



pts = []
cts = []

semaphore = Semaphore(0)
lock = Lock()

for i in range(N // M):
    pts.append(Thread(target=producer, args=(lock, semaphore)))

for i in range(1):
    cts.append(Thread(target=customer, args=(lock, semaphore)))

for t in chain(pts, cts):
    t.start()

for t in chain(pts, cts):
    t.join()
