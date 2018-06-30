from hand import Hand
from black_jack_card import BlackJackCard


class BlackJackHand(Hand):
    @property
    def score(self):
        max_under = int(-1e9)
        min_over = int(1e9)

        for score in self.possible_scores:
            if score > 21 and score < min_over:
                min_over = score
            elif score <= 21 and score > max_under:
                max_under = score
        return min_over if max_under == int(-1e9) else max_under

    def check_card(self, card):
        '''Overwrite this method to support only BlackJackCard.'''
        assert isinstance(card, BlackJackCard)

    @property
    def possible_scores(self):
        scores = {self._cards[0].min_value, self._cards[1].max_value}
        for card in self._cards[1:]:
            min_value, max_value = card.min_value, card.max_value
            new_min_scores = {score + min_value for score in scores}
            new_max_scores = {score + max_value for score in scores}
            scores = new_min_scores | new_max_scores
        return scores

    @property
    def is_busted(self):
        return self.score > 21

    @property
    def is_21(self):
        return self.score == 21

    @property
    def is_black_jack(self):
        if len(self._cards) != 2:
            return False
        first, second = self._cards[0], self._cards[1]
        return ((first.is_ace and second.is_faced_card) or
                (second.is_ace and first.is_faced_card))
