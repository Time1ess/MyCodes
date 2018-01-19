from time import sleep
from threading import Thread, Event, get_ident


def celebrate(event):
    event.wait()
    print('[{}]:Happy New Year'.format(get_ident()))
    sleep(1)
    event.wait()
    print('[{}]:Happy Valentine\'s Day'.format(get_ident()))



ts = []
event = Event()
for _ in range(10):
    t = Thread(target=celebrate, args=(event,))
    t.start()
    ts.append(t)

N = 3
for i in range(N):
    print('New Year is coming in {}.'.format(N - i))
    sleep(1)
event.set()
sleep(0.1)
event.clear()
for i in range(N):
    print('Valentine\'s Day is coming in {}.'.format(N - i))
    sleep(1)
event.set()

for t in ts:
    t.join()
