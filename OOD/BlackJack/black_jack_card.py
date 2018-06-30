from card import Card


class BlackJackCard(Card):
    @property
    def value(self):
        if self.is_ace:
            return 1
        elif self.is_faced_card:
            return 10
        return self._value

    @property
    def min_value(self):
        if self.is_ace:
            return 1
        return self.value

    @property
    def max_value(self):
        if self.is_ace:
            return 11
        return self.value

    @property
    def is_ace(self):
        return self._value == 1

    @property
    def is_faced_card(self):
        return self._value >= 11 and self._value <= 13
