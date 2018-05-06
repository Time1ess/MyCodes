import string
import hashlib
import array

from random import choices


class StandardBloomFilter:
    """
    @param: k: An integer
    """
    def __init__(self, k, bit_length=1000000):
        # do intialization if necessary
        
        self.k = k
        self.bits = [0 for _ in range((bit_length + 8) // 8)]
        self.bit_length = bit_length

    def __calculate_hash_bits(self, word):
        bits = []
        for i in range(self.k):
            hasher = hashlib.md5()
            hasher.update(word.encode())
            bits.append(int(hasher.digest().hex(), base=16) % self.bit_length)
        return bits

    """
    @param: word: A string
    @return: nothing
    """
    def add(self, word):
        # write your code here
        bits = self.__calculate_hash_bits(word)
        for pos in bits:
            byte, offset = divmod(pos, 8)
            self.bits[byte] |= (1 << offset)

    """
    @param: word: A string
    @return: True if contains word
    """
    def contains(self, word):
        # write your code here
        bits = self.__calculate_hash_bits(word)
        for pos in bits:
            byte, offset = divmod(pos, 8)
            if (self.bits[byte] & (1 << offset)) == 0:
                return False
        return True
