# Each card instance has exactly one suit
class Suit:
    CLUB = 0
    DIAMOND = 1
    HEART = 2
    SPADE = 3

    _suit_type = -1
    _insts = {}

    def __new__(cls, suit_type):
        if not cls._insts:
            for st in cls.get_all_suit_types():
                suit = super().__new__(cls)
                suit._suit_type = st
                cls._insts[st] = suit
        return cls._insts[suit_type]

    def __init__(self, suit_type):
        assert suit_type in self.get_all_suit_types()
        self._suit_type = suit_type

    @classmethod
    def get_all_suit_types(cls):
        return [cls.CLUB, cls.DIAMOND, cls.HEART, cls.SPADE]

    def print_suit(self):
        print(str(self), end='')

    def __str__(self):
        suits = ['♦', '♣', '♥', '♠']
        return suits[self._suit_type]
