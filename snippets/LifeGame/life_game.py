import sys
import multiprocessing as mp

import pygame

from concurrent.futures import ProcessPoolExecutor

from time import time

from life_game_core import (
    init_generation, next_generation, next_generation_pool, Pool)

pygame.init()
size = (100, 100)
display = pygame.display.set_mode(size)

running = True

# pixels, old_shared, new_shared = init_generation(size)
pixels = init_generation(size, shared=False)

cores = 4
generation = 1
kwargs = {}
# barrier = mp.Barrier(cores+1)
# kwargs = {'barrier': barrier, 'old_shared': old_shared,
#          'new_shared': new_shared}
# with Pool(cores, initargs=(old_shared, new_shared, barrier)) as executor:
with ProcessPoolExecutor(cores) as executor:
    s = time()
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        surf = pygame.surfarray.make_surface(pixels)
        display.blit(surf, (0, 0))
        pygame.display.update()
        # pixels = next_generation_pool(pixels, executor, cores,
        #                              generation=generation, **kwargs)
        pixels = next_generation(pixels, executor, cores, **kwargs)
        sys.stdout.flush()
        sys.stdout.write('FPS: {:.3f} Generation: {}\r'.format(
            1 / (time() - s), generation))
        generation += 1
        s = time()
pygame.quit()
