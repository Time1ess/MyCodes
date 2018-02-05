import sys
import multiprocessing as mp

from concurrent.futures import ProcessPoolExecutor

from time import time

from life_game_core import (
    init_generation, next_generation, next_generation_pool, Pool)


size = (100, 100)

running = True

pixels, old_shared, new_shared = init_generation(size)
# pixels = init_generation(size, shared=False)

cores = 4
generation = 1
barrier = mp.Barrier(cores+1)
kwargs = {'barrier': barrier}
with Pool(cores, initargs=(old_shared, new_shared, barrier)) as executor:
# with ProcessPoolExecutor(cores) as executor:
    s = time()
    while running:
        pixels = next_generation_pool(pixels, executor, cores, **kwargs)
        # pixels = next_generation(pixels, executor, cores, **kwargs)
        sys.stdout.flush()
        sys.stdout.write('FPS: {:.3f} Generation: {}\r'.format(
            1 / (time() - s), generation))
        generation += 1
        s = time()
