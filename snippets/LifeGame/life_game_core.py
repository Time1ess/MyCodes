import math
import time
import ctypes
import multiprocessing as mp

from concurrent.futures import as_completed
from contextlib import contextmanager

import numpy as np


def _shared_init(size):
    count = size[0] * size[1]
    old_shared = mp.Array(ctypes.c_uint8, count, lock=False)
    new_shared = mp.Array(ctypes.c_uint8, count, lock=False)
    pixels = to_numpy_array(old_shared, count, size)
    pixels[:, :] = np.random.randint(0, 2, size, dtype=ctypes.c_uint8) * 255
    return pixels, old_shared, new_shared


def _non_shared_init(size):
    return np.random.randint(0, 2, size, dtype=ctypes.c_uint8) * 255


def init_generation(size, shared=True):
    if shared:
        return _shared_init(size)
    else:
        return _non_shared_init(size)


def to_numpy_array(buf, count, size, dtype=np.uint8):
    pixels = np.frombuffer(buf, dtype, count).reshape(size)
    return pixels


def dead_or_alive(pixels, m, n, i, j):
    cnt = 0
    for _i in range(max(0, i-1), min(m, i+2)):
        for _j in range(max(0, j-1), min(n, j+2)):
            if _i == i and _j == j:
                continue
            if pixels[_i][_j] == 255:
                cnt += 1
    if cnt == 3 or cnt == 2 and pixels[i][j] > 0:
        return True
    elif cnt == 2:
        return pixels[i][j] > 0
    else:
        return False


def _generate(old_pixels, m, n, i_s, i_e):
    _m = i_e - i_s
    pixels = np.zeros((_m, n), dtype=np.uint8)
    for i in range(i_s, i_e):
        for j in range(n):
            alive = dead_or_alive(old_pixels, m, n, i, j)
            pixels[i - i_s][j] = 1 if alive else 0
    return (i_s, i_e, pixels)


def _pool_generate(m, n, i_s, i_e, generation):
    count = m * n
    if generation % 2 == 1:
        old_pixels = to_numpy_array(old_shared, count, (m, n))
        new_pixels = to_numpy_array(new_shared, count, (m, n))
    else:
        old_pixels = to_numpy_array(new_shared, count, (m, n))
        new_pixels = to_numpy_array(old_shared, count, (m, n))
    for i in range(i_s, i_e):
        for j in range(n):
            alive = dead_or_alive(old_pixels, m, n, i, j)
            new_pixels[i][j] = 1 if alive else 0
    barrier.wait()


old_shared = None
new_shared = None
barrier = None


def pool_init(old_shared_, new_shared_, barrier_):
    global old_shared, new_shared, barrier
    old_shared = old_shared_
    new_shared = new_shared_
    barrier = barrier_


@contextmanager
def Pool(cores, initializer=pool_init, initargs=None):
    pool = mp.Pool(cores, initializer, initargs)
    yield pool
    pool.close()
    pool.join()


def print_debug():
    print('debug')


def next_generation_pool(pixels, pool, cores, **kwargs):
    m, n = pixels.shape
    barrier = kwargs.get('barrier')
    old_shared = kwargs.get('old_shared')
    new_shared = kwargs.get('new_shared')
    generation = kwargs.get('generation')
    barrier.reset()
    shared = new_shared if generation % 2 == 1 else old_shared
    new_pixels = to_numpy_array(shared, m * n, (m, n))
    chunk_size = int(math.ceil(m / cores))
    futures = []
    for i_s in range(0, m, chunk_size):
        pool.apply_async(_pool_generate,
                         (m, n, i_s, min(i_s + chunk_size, m), generation))
    barrier.wait()
    new_pixels *= 255
    return new_pixels


def next_generation(pixels, executor, cores, **kwargs):
    new_pixels = np.zeros_like(pixels, dtype=np.uint8)
    m, n = pixels.shape
    chunk_size = int(math.ceil(m / cores))
    futures = []
    for i_s in range(0, m, chunk_size):
        future = executor.submit(
            _generate, pixels, m, n, i_s, min(i_s + chunk_size, m))
        futures.append(future)
    for future in as_completed(futures):
        i_s, i_e, part_pixels = future.result()
        new_pixels[i_s:i_e, :] = part_pixels
    new_pixels *= 255
    return new_pixels
