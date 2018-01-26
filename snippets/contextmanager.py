from contextlib import contextmanager


@contextmanager
def func():
    print('A')
    yield
    print('B')


with func():
    print('In')
