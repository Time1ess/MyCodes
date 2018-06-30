from card import Card


class Hand:
    _cards = None

    def __init__(self):
        self._cards = []

    def check_card(self, card):
        assert isinstance(card, Card)

    def add_card(self, card):
        self.check_card(card)
        self._cards.append(card)

    @property
    def score(self):
        return sum(card.value for card in self._cards)

    def print_hand(self):
        for card in self._cards:
            card.print_card()
            print(' ', end='')
