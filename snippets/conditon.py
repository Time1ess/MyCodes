from time import sleep
from threading import Thread, Condition, get_ident


N = 8
M = 3
T = 1


def customer(cond):
    cond.acquire()
    print('Customer {} waiting'.format(get_ident()))
    cond.wait()
    print('Customer {} satisfied'.format(get_ident()))
    cond.release()


def producer(cond):
    for i in range(1 + N // M):
        sleep(T)
        cond.acquire()
        cond.notify(M)
        print('Producer {} produce {} dishes'.format(get_ident(), M))
        cond.release()


ts = []
cond = Condition()

for _ in range(N):
    ts.append(Thread(target=customer, args=(cond,)))
ts.append(Thread(target=producer, args=(cond,)))

for t in ts:
    t.start()

for t in ts:
    t.join()
