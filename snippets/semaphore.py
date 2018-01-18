from random import random
from time import sleep
from threading import Thread, Semaphore, get_ident
from itertools import chain


N = 9
M = 3


def producer(semaphore):
    for _ in range(M):
        sleep(0.5 + random())
        print('Producer {} wakeup'.format(get_ident()))
        print('Producer {} produce'.format(get_ident()))
        semaphore.release()
    print('Producer {} exit'.format(get_ident()))


def customer(semaphore):
    cnt = 0
    while cnt < N:
        product = semaphore.acquire()
        if product:
            cnt += 1
            print('Customer {} consume'.format(get_ident()))
        else:
            print('No product, Customer {} sleep'.format(get_ident()))
            # sleep(1)
            print('Customer {} wakeup'.format(get_ident()))
    print('Customer {} exit'.format(get_ident()))


pts = []
cts = []

semaphore = Semaphore(0)

for i in range(N // M):
    pts.append(Thread(target=producer, args=(semaphore,)))

for i in range(1):
    cts.append(Thread(target=customer, args=(semaphore,)))

for t in chain(pts, cts):
    t.start()

for t in chain(pts, cts):
    t.join()
