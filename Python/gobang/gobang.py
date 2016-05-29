#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-05-22 14:02
# Last modified: 2016-05-22 14:02
# Filename: gobang.py
# Description:

from random import choice
import sys

BLACK = u'●'
WHITE = u'○'
BLANK = u'  '
STAR = u'★'
BOARD_SIZE = 15

EVEN = 0
W_WIN = 1
B_WIN = 2

chessboard = [[BLANK for i in xrange(BOARD_SIZE)]
              for j in xrange(BOARD_SIZE)]
available_pos = [(i, j) for i in xrange(1, BOARD_SIZE+1)
                 for j in xrange(1, BOARD_SIZE+1)]


def reset():
    global chessboard
    global available_pos
    chessboard = [[BLANK for i in xrange(BOARD_SIZE)]
                  for j in xrange(BOARD_SIZE)]
    available_pos = [(i, j) for i in xrange(1, BOARD_SIZE+1)
                     for j in xrange(1, BOARD_SIZE+1)]


def POS_VALID(func):
    def wrapper(*args, **kwargs):
        if kwargs.get('pos', None):
            pos = kwargs['pos']
        else:
            pos = args[0]
        if pos[0] < 1 or pos[0] > BOARD_SIZE or pos[1] < 1 or \
                pos[1] > BOARD_SIZE:
                    print pos[0], pos[1]
                    raise Exception("POS NOT VALID")
        if chessboard[pos[0]-1][pos[1]-1] != BLANK:
            raise Exception("WRONG MOVE")
        func(*args, **kwargs)
    return wrapper


def show_board(keys=[]):
    print '='*77
    formats = ' '*5 + '%-5d'*BOARD_SIZE
    print (formats+'\n') % tuple([i+1 for i in xrange(BOARD_SIZE)])
    for index, line in enumerate(chessboard):
        print '%-2d' % (index+1), ' ',
        for elem in line:
            if elem in keys:
                print elem, ' ',
            else:
                print '  ', ' ',
        print '\n'


@POS_VALID
def chess_move(pos, color):
    x = pos[0]
    y = pos[1]
    chessboard[x-1][y-1] = color


def count_same_color(pos, color, last_cnt):
    cnt = last_cnt
    if chessboard[pos[0]][pos[1]] == color:
        cnt += 1
    else:
        cnt = 0
    return cnt


def win(pos, color):
    x = pos[0] - 1
    y = pos[1] - 1
    top = max(pos[0]-4, 1) - 1
    bottom = min(pos[0]+4, BOARD_SIZE) - 1
    left = max(pos[1]-4, 1) - 1
    right = min(pos[1]+4, BOARD_SIZE) - 1

    # Vertical
    cnt = 0
    for row in xrange(top, bottom+1):
        cnt = count_same_color([row, y], color, cnt)
        if cnt == 5:
            for i in xrange(row, row-5, -1):
                chessboard[i][y] = STAR
            return True
    # Horizontal
    cnt = 0
    for col in xrange(left, right+1):
        cnt = count_same_color([x, col], color, cnt)
        if cnt == 5:
            for i in xrange(col, col-5, -1):
                chessboard[x][i] = STAR
            return True
    # Diagonal-lt
    cnt = 0
    row, col = x, y
    while row >= top and col >= left:
        cnt = count_same_color([row, col], color, cnt)
        if cnt == 5:
            for i in xrange(row, row+5, 1):
                chessboard[i][i] = STAR
            return True
        row, col = row-1, col-1
    # Diagonal-lb
    cnt = 0
    row, col = x, y
    while row <= bottom and col >= left:
        cnt = count_same_color([row, col], color, cnt)
        if cnt == 5:
            for i in xrange(row, row-5, -1):
                chessboard[i][row*2 - i] = STAR
            return True
        row, col = row+1, col-1
    # Diagonal-rt
    cnt = 0
    row, col = x, y
    while row >= top and col <= right:
        cnt = count_same_color([row, col], color, cnt)
        if cnt == 5:
            for i in xrange(row, row+5, 1):
                chessboard[i][row*2 - i] = STAR
            return True
        row, col = row-1, col+1
    # Diagonal-rb
    cnt = 0
    row, col = x, y
    while row <= top and col <= right:
        cnt = count_same_color([row, col], color, cnt)
        if cnt == 5:
            for i in xrange(row, row-5, -1):
                chessboard[i][i] = STAR
            return True
        row, col = row+1, col+1
    return False


def test_game(white_moves, black_moves, white_first, print_board):
    if white_first:
        flag = False
        first = white_moves
        second = black_moves
    else:
        flag = True
        first = black_moves
        second = white_moves
    index = 0
    while True:
        if index > len(first)-1:
            break
        pos = first[index]
        color = BLACK if flag else WHITE
        chess_move(pos, color)
        if print_board:
            show_board()
        if win(pos, color):
            return W_WIN if color == WHITE else B_WIN
        flag = not flag
        if index > len(second)-1:
            break
        pos = second[index]
        color = BLACK if flag else WHITE
        chess_move(pos, color)
        if print_board:
            show_board()
        if win(pos, color):
            return W_WIN if color == WHITE else B_WIN
        flag = not flag
        index += 1
    return EVEN


def test(white_moves, black_moves, white_first, print_board, status_code):
    reset()
    _status = test_game(white_moves, black_moves, white_first, print_board)
    if status_code == _status:
        print 'Case passed.'
    else:
        print 'Case failed.'


def all_test():
    white_moves = [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5]]
    black_moves = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6]]
    test(white_moves, black_moves, True, False, W_WIN)
    test(white_moves, black_moves, False, False, B_WIN)
    white_moves = [[6, 5], [6, 6], [6, 7], [6, 8], [6, 9]]
    black_moves = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6]]
    test(white_moves, black_moves, True, False, W_WIN)
    test(white_moves, black_moves, False, False, B_WIN)
    white_moves = [[7, 6], [8, 3], [9, 8], [10, 4], [9, 1]]
    black_moves = [[8, 2], [2, 3], [3, 4], [4, 5], [5, 6]]
    test(white_moves, black_moves, True, False, EVEN)
    test(white_moves, black_moves, False, False, EVEN)


if __name__ == '__main__':
    flag = False
    b_wins = 0
    w_wins = 0
    while True:
        pos = choice(available_pos)
        available_pos.remove(pos)
        color = BLACK if flag else WHITE
        chess_move(pos, color)
        if win(pos, color):
            if color == BLACK:
                b_wins += 1
                sys.stdout.flush()
                sys.stdout.write('BLACK!B:'+str(b_wins)+'W:'+str(w_wins)+'\r')
            else:
                w_wins += 1
                sys.stdout.flush()
                sys.stdout.write('BLACK!B:'+str(b_wins)+'W:'+str(w_wins)+'\r')
            show_board(keys=[STAR])
            raw_input()
            reset()
            continue
        if not available_pos:
            print 'EVEN!'
            reset()
        flag = not flag
