from black_jack_hand import BlackJackHand
from black_jack_card import BlackJackCard
from deck import Deck
from suit import Suit


class BlackJackGameAutomator:
    _deck = None
    _hands = []
    HIT_UNTIL = 16

    def __init__(self, num_players):
        self._hands = [BlackJackHand() for _ in range(num_players)]

    def deal_initial(self):
        for hand in self._hands:
            card1 = self._deck.deal_card()
            card2 = self._deck.deal_card()
            if card1 is None or card2 is None:
                return False
            hand.add_card(card1)
            hand.add_card(card2)
        return True

    def get_black_jacks(self):
        return [i for i, hand in enumerate(self._hands)
                if hand.is_black_jack]

    def play_hand(self, i):
        hand = self._hands[i]
        return self._play_hand(hand)

    def _play_hand(self, hand):
        while hand.score < self.HIT_UNTIL:
            card = self._deck.deal_card()
            if card is None:
                return False
            hand.add_card(card)
        return True

    def play_all_hands(self):
        for hand in self._hands:
            if not self._play_hand(hand):
                return False
        return True

    def get_winners(self):
        winners = []
        winning_score = 0
        for idx, hand in enumerate(self._hands):
            if not hand.is_busted:
                if hand.score > winning_score:
                    winning_score = hand.score
                    winners = [idx]
                elif hand.score == winning_score:
                    winners.append(idx)
        return winners

    def initialize_deck(self):
        cards = []
        for value in range(1, 14):
            cards.extend(BlackJackCard(value, Suit(st))
                         for st in Suit.get_all_suit_types())
        deck = Deck()
        deck.set_cards(cards)
        deck.reset()
        self._deck = deck

    def print_hands_and_score(self):
        for idx, hand in enumerate(self._hands):
            print("Hand {} ({})".format(idx, hand.score))
            hand.print_hand()
            print()
