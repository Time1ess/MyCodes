import random
from random import shuffle, choice

import matplotlib.pyplot as plt
import numpy as np


class Mazer:
    def __init__(self, size, start=None):
        self.__default_maze = np.zeros(size, dtype=np.uint8)
        self.__default_maze[1::2, 1::2] = 1
        self.__start = start
        self._gen_path()
        self.__maze = self.__default_maze.copy().astype(np.float32)
        self.__solved = False

    @property
    def maze(self):
        return self.__default_maze

    @property
    def solved_maze(self):
        if not self.__solved:
            self.solve_maze()
        print(self.__solved)
        return self.__maze

    def _gen_path(self, method='random_prim'):
        self.__start = getattr(self, method)(self.__default_maze,
                                             self.__start)
        maze = self.__default_maze
        maze[maze == 2] = 1
        h, w = maze.shape
        end = (0, 0)
        while maze[end[0], end[1]] == 0:
            end = (h - 2, np.random.randint(1, w - 1))
        self.__end = end

    def random_prim(self, maze, start):
        dirs = ((0, 1), (0, -1), (1, 0), (-1, 0))
        h, w = maze.shape
        if start is None:
            start = (1, 1 + 2 * np.random.randint(0, w // 2))
        maze[start[0], start[1]] = 2
        maze[start[0]-1, start[1]] = 2
        cands = set()
        def _add_surroundings(x, y):
            for dx, dy in dirs:
                cx, cy = x + dx, y + dy
                nx, ny = x + 2 * dx, y + 2 * dy
                if not (self.valid_position(h, w, cx, cy)
                        and self.valid_position(h, w, nx, ny)):
                    continue
                if maze[nx][ny] == 2:
                    continue
                cands.add((cx, cy, nx, ny))
        _add_surroundings(*start)
        while cands:
            cx, cy, nx, ny = cands.pop()
            if maze[nx][ny] == 2:
                continue
            maze[cx][cy] = maze[nx][ny] = 2
            _add_surroundings(nx, ny)
        return start

    @staticmethod
    def valid_position(h, w, x, y):
        return x >= 0 and x < h and y >= 0 and y < w

    def random_direction_dfs(self, maze, start):
        """DFS maze generation.

        Warning: Maze size is limited since max recursion limitation.
        """
        dirs = ((0, 2), (0, -2), (2, 0), (-2, 0))
        h, w = maze.shape
        if start is None:
            start = (1, 1 + 2 * np.random.randint(0, w // 2))
        maze[start[0], start[1]] = 2
        maze[start[0]-1, start[1]] = 2
        depth = 0
        def _random_direction_dfs(maze, h, w, x, y, d):
            nonlocal depth
            depth = max(depth, d)
            valid_pos = []
            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if not self.valid_position(h, w, nx, ny) or maze[nx][ny] == 2:
                    continue
                valid_pos.append((nx, ny))
            if not valid_pos:
                return

            shuffle(valid_pos)
            for pos in valid_pos:
                if maze[pos[0]][pos[1]] == 2:
                    continue
                maze[pos[0]][pos[1]] = 2
                cross_pos = ((pos[0] + x) // 2, (pos[1] + y) // 2)
                maze[cross_pos[0]][cross_pos[1]] = 2
                _random_direction_dfs(maze, h, w, *pos, d + 1)
        _random_direction_dfs(maze, h, w, *start, 0)
        return start

    def solve_maze(self):
        maze = self.__maze
        start = self.__start
        end = self.__end
        dirs = ((0, 1), (0, -1), (1, 0), (-1, 0))
        h, w = maze.shape
        def _dfs(maze, h, w, end, x, y, d):
            if not self.valid_position(h, w, x, y) or maze[x][y] == 0:
                return False
            if end == (x, y):  # Find
                maze[end[0]][end[1]] = d
                return True
            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if (not self.valid_position(h, w, nx, ny)
                        or maze[nx][ny] > 1 or maze[nx][ny] == 0):
                    continue
                maze[nx][ny] = d
                if _dfs(maze, h, w, end, nx, ny, d+.01):
                    return True
                maze[nx][ny] = 1
            return False
        maze[start[0]-1][start[1]] = 2
        maze[start[0]][start[1]] = 2.01
        found = _dfs(maze, h, w, end, *start, 2.02)
        self.__solved = found


m = Mazer((51, 51))
maze = m.solved_maze
plt.imshow(maze, vmin=0, vmax=maze.max(), cmap='gray')
plt.show()
