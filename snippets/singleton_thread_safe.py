from inspect import isfunction
from time import time
from threading import Lock, Thread, RLock


class SingletonThreadSafe(type):
    cls_locks = {}

    def __new__(cls, name, bases, attrs):
        cls.cls_locks[name] = Lock()

        def thread_safe(func, lock):
            def _wrapper(*args, **kwargs):
                with lock:
                    return func(*args, **kwargs)
            return _wrapper

        def _lazy_instance():
            if not hasattr(target, '_inst'):
                with cls.cls_locks[name]:
                    if not hasattr(target, '_inst'):
                        target._inst = target(lazy=False)
            return target._inst

        instance_lock = RLock()  # Reentrant lock
        for func_name in attrs:
            attr = attrs[func_name]
            if isfunction(attr):
                attrs[func_name] = thread_safe(attr, instance_lock)
        target = super().__new__(cls, name, bases, attrs)
        target._lazy_instance = _lazy_instance
        return target

    def __call__(cls, *args, **kwargs):
        if not kwargs.get('lazy', True):
            return super().__call__(cls, *args, **kwargs)
        return cls._lazy_instance()


class A(metaclass=SingletonThreadSafe):
    cnt = 0

    def __init__(self, *args, **kwargs):
        pass

    def incr_and_decr(self, by=1):
        self.incr(1)
        self.incr(-1)

    def incr(self, by=1):
        type(self).cnt += by


def create_A():
    s = time()
    a = A()
    e = time()
    a.incr_and_decr()
    with tot_lock:
        global tot
        tot += e - s


ts = []
N = 10000
tot = 0
tot_lock = Lock()
for i in range(N):
    ts.append(Thread(target=create_A))

for t in ts:
    t.start()

for t in ts:
    t.join()
spo = tot / N
print('Seconds per object: {:.4e}, Object per second: {}'.format(
    spo, int(1 / spo)))

a = A()
print(a.cnt)
