from suit import Suit


class Card:
    _value = 0
    _suit = None
    _available = True

    def __init__(self, value, suit):
        '''Initialize card instance.

        params
        ------
        value: int
            1 for ace, 11, 12, 13 for Jack, Queen, King, 15, 16 for Jokers.
        suit: Suit
        '''
        assert isinstance(suit, Suit)
        assert 1 <= value <= 16
        self._value = value
        self._suit = suit

    @property
    def suit(self):
        return self._suit

    @property
    def value(self):
        '''Value could be changed for different type of games.'''
        return self._value

    @property
    def available(self):
        '''Whether this card can be dealt.'''
        return self._available

    def setAvailable(self):
        self._available = True

    def setUnavailable(self):
        self._available = False

    def print_card(self):
        print(str(self), end='')

    def __str__(self):
        values = ('A', '2', '3', '4', '5', '6', '7',
                  '8', '9', '10', 'J', 'Q', 'K')
        return values[self._value-1] + str(self._suit)

    def __repr__(self):
        return str(self)
