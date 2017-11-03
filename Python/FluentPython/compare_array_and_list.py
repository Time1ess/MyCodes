import pickle
import os.path as osp

from array import array
from random import random
from time import time
from tempfile import TemporaryDirectory, gettempdir


def timeit(func):
    def _wrapper(*args, **kwargs):
        s = time()
        ret = func(*args, **kwargs)
        e = time()
        print(func.__name__, e-s)
        return ret
    return _wrapper


tmp_name = gettempdir()


@timeit
def create_floats_array(size=10**7):
    floats = array('d', (random() for _ in range(size)))
    return floats

@timeit
def create_floats_list(size=10**7):
    floats = [random() for _ in range(size)]
    return floats


@timeit
def save_floats_array(floats, fname='floats_array.bin'):
    with open(osp.join(tmp_name, fname), 'wb') as f:
        floats.tofile(f)

@timeit
def save_floats_array_pickle(floats, fname='floats_array.pkl'):
    with open(osp.join(tmp_name, fname), 'wb') as f:
        pickle.dump(floats, f)


@timeit
def save_floats_list(floats, fname='floats_list.bin'):
    with open(osp.join(tmp_name, fname), 'wb') as f:
        pickle.dump(floats, f)


@timeit
def save_floats_array_txt(floats, fname='floats_array.txt'):
    with open(osp.join(tmp_name, fname), 'w') as f:
        for num in floats:
            f.write(str(num) + '\n')


@timeit
def save_floats_list_txt(floats, fname='floats_list.txt'):
    with open(osp.join(tmp_name, fname), 'w') as f:
        for num in floats:
            f.write(str(num) + '\n')


@timeit
def load_floats_array(size=10**7, fname='floats_array.bin'):
    floats = array('d')
    with open(osp.join(tmp_name, fname), 'rb') as f:
        floats.fromfile(f, size)
    return floats


@timeit
def load_floats_array_pickle(fname='floats_array.pkl'):
    with open(osp.join(tmp_name, fname), 'rb') as f:
        floats = pickle.load(f)
    return floats


@timeit
def load_floats_list(fname='floats_list.bin'):
    with open(osp.join(tmp_name, fname), 'rb') as f:
        floats = pickle.load(f)
    return floats


@timeit
def load_floats_array_txt(fname='floats_array.txt'):
    floats = []
    with open(osp.join(tmp_name, fname), 'r') as f:
        for line in f:
            floats.append(float(line.strip()))
    return floats


@timeit
def load_floats_list_txt(fname='floats_list.txt'):
    floats = []
    with open(osp.join(tmp_name, fname), 'r') as f:
        for line in f:
            floats.append(float(line.strip()))
    return floats


floats_array = create_floats_array()
floats_list = create_floats_list()
save_floats_array(floats_array)
save_floats_array_pickle(floats_array)
save_floats_list(floats_list)
load_floats_array()
load_floats_array_pickle()
load_floats_list()
