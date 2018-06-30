from random import shuffle

from card import Card


class Deck:
    '''Deck is responsible for dealing cards.

    props
    -----
    _cards: The list of Card
    _dealt_index: The index of the card int _cards should be dealt next
    '''
    _cards = []
    _dealt_index = 0

    def set_cards(self, cards):
        assert isinstance(cards, list)
        for card in cards:
            assert isinstance(card, Card)
        self._cards = cards
        self._dealt_index = 0

    def reset(self):
        shuffle(self._cards)
        for card in self._cards:
            card.setAvailable()
        self._dealt_index = 0

    @property
    def remaining_cards(self):
        return len(self._cards) - self._dealt_index

    def deal_card(self):
        '''Deal one card.'''
        if self.remaining_cards == 0:
            return None
        card = self._cards[self._dealt_index]
        self._dealt_index += 1
        card.setUnavailable()
        return card

    def deal_hand(self, num_cards):
        '''Deal specified number of cards.'''
        if num_cards > self.remaining_cards:
            return None
        return [self.deal_card() for _ in range(num_cards)]
