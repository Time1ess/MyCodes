from threading import RLock, Thread, Lock


N = 10
M = 10


class Counter:
    def __init__(self):
        self.__count = 0
        self.lock = RLock()

    def add(self):
        with self.lock:
            cnt = self.__count
            self.__count = cnt + 1
            self.print_info()

    def print_info(self, prefix=''):
        with self.lock:
            print('{}{}'.format(prefix, self.__count))


def counter_add(counter, is_printer):
    if is_printer:
        for _ in range(N):
            counter.print_info('>>>')
    else:
        for _ in range(N):
            counter.add()


counter = Counter()


ts = []

for i in range(M):
    ts.append(Thread(target=counter_add, args=(counter, i % 5 == 0)))

for t in ts:
    t.start()

for t in ts:
    t.join()
