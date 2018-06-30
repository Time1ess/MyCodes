from automator import BlackJackGameAutomator


def main():
    num_hands = 5
    automator = BlackJackGameAutomator(num_hands)
    automator.initialize_deck()
    success = automator.deal_initial()
    if not success:
        raise Exception('Error, Out of cards.')
    else:
        print('-- Initial --')
    automator.print_hands_and_score()
    black_jacks = automator.get_black_jacks()
    if black_jacks:
        print('Blackjack at ')
        for idx in black_jacks:
            print(idx, ', ', end='')
        print()
    else:
        success = automator.play_all_hands()
        if not success:
            raise Exception('Error, Out of cards.')
        else:
            print('\n-- Completed Game --')
            automator.print_hands_and_score()
            winners = automator.get_winners()
            if winners:
                print('Winners: ', end='')
                for idx in winners:
                    print('{}, '.format(idx), end='')
                print()
            else:
                print('Draw. All players have busted.')


if __name__ == '__main__':
    main()
