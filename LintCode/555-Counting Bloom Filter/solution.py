import hashlib

from functools import lru_cache


@lru_cache(maxsize=None)
def calculate_blocks(word, K, M):
    blocks = []
    for i in range(K):
        hasher = hashlib.md5()
        hasher.update(('%d%s' % (i, word)).encode())
        pos = int(hasher.hexdigest(), base=16) % M
        blocks.append(pos)
    return blocks


class CountingBloomFilter:
    def __init__(self, k, bit_length=1000000):
        self.k = k
        self.blocks = [0 for _ in range(int((bit_length + 4) // 4))]
        self.blocks = int(bit_length // 4)

    def add(self, word):
        blocks = calculate_blocks(word, self.k, self.blocks)
        for block in blocks:
            pos, offset = divmod(block, 2)
            self.incr_blocks(pos, offset, 1)

    def incr_blocks(self, pos, offset, incr):
        cnt = self.blocks[pos]
        if offset == 1:
            cnt = cnt >> 4
            cnt = min(15, max(0, cnt + incr))
            self.blocks[pos] = (self.blocks[pos] & 0xf) | (cnt << 4)
        else:
            cnt = cnt & 0xf
            cnt = min(15, max(0, cnt + incr))
            self.blocks[pos] = (self.blocks[pos] & 0xf0) | cnt

    def check_block(self, pos, offset):
        cnt = self.blocks[pos]
        if offset == 1:
            cnt = cnt >> 4
        else:
            cnt = cnt & 0xf
        return cnt

    def remove(self, word):
        blocks = calculate_blocks(word, self.k, self.blocks)
        for block in blocks:
            pos, offset = divmod(block, 2)
            self.incr_blocks(pos, offset, -1)

    def contains(self, word):
        blocks = calculate_blocks(word, self.k, self.blocks)
        for block in blocks:
            pos, offset = divmod(block, 2)
            if self.check_block(pos, offset) == 0:
                return False
        return True
