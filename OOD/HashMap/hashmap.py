from collections import deque, defaultdict


class Cell:
    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __eq__(self, cell):
        return self.key_equal(cell.key)

    def key_equal(self, key):
        return self.key == key


class HashMap:
    def __init__(self):
        self.__storage = defaultdict(deque)

    @staticmethod
    def _hash(key):
        return 0  # To simulate collide
        # return hash(key)

    def insert(self, key, value):
        '''Insert <key, value> or Update exist key.

        If True returned, new pair inserted, else old pair updated.
        '''
        hash_key = self._hash(key)
        for cell in self.__storage[hash_key]:
            if cell.key_equal(key):
                cell.value = value
                return False
        cell = Cell(key, value)
        self.__storage[hash_key].append(cell)
        return True

    def lookup(self, key):
        hash_key = self._hash(key)
        for cell in self.__storage[hash_key]:
            if cell.key_equal(key):
                return cell.value
        return None

    def erase(self, key):
        '''Remove key in map.

        If True returned, pair deleted, else no pair found.
        '''
        hash_key = self._hash(key)
        target_cell = None
        for cell in self.__storage[hash_key]:
            if cell.key_equal(key):
                target_cell = cell
                break
        if target_cell is None:
            return False
        self.__storage[hash_key].remove(target_cell)
        return True
