import tkinter as tk


class Gobang:
    PLAYER_WHITE = 0b0
    PLAYER_BLACK = 0b1

    root = None
    side_canvas = None
    current_player = None
    winner = None
    gobang_board = None

    _current_player = PLAYER_BLACK
    _game_over = False
    black_pieces = []
    white_pieces = []
    pieces = {}

    def __init__(self, piece_size=5, cell_size=35):
        self.piece_size = 5
        self.cell_size = 35

        self.root = tk.Tk()
        self.root.title('Gobang')
        self.root.geometry('760x560')

        self.draw_sidebar()
        self.draw_gobang_board()
        self.draw_ticks()
        self.draw_stars()
        self.draw_interactables()

    def draw_stars(self):
        point_x = [3, 3, 11, 11, 7]
        point_y = [3, 11, 3, 11, 7]
        cell_size = self.cell_size
        piece_size = self.piece_size
        for i in range(5):
            x = cell_size * (1 + point_x[i])
            y = cell_size * (1 + point_y[i])
            self.gobang_board.create_oval(x - piece_size, y - piece_size,
                                          x + piece_size, y + piece_size,
                                          fill='black')

    def draw_interactables(self):
        cell_size = self.cell_size
        piece_size = self.piece_size
        for x in range(cell_size, cell_size * 16, cell_size):
            for y in range(cell_size, cell_size * 16, cell_size):
                self.gobang_board.create_oval(
                    x - piece_size, y - piece_size,
                    x + piece_size, y + piece_size,
                    width=0, tags=('__INTERACTABLE_PIECE', str(x), str(y)))

    def draw_sidebar(self):
        piece_size = self.piece_size
        side_canvas = tk.Canvas(self.root, width=220, height=50)
        side_canvas.grid(row=0, column=1)
        side_canvas.create_oval(110 - piece_size, 25 - piece_size,
                                110 + piece_size, 25 + piece_size,
                                fill=self.get_current_piece_color(),
                                tags=('curent_piece_color'))
        self.side_canvas = side_canvas

        current_player = tk.StringVar()
        self._current_player = self.PLAYER_BLACK
        self.current_player = current_player
        self.set_current_player()
        person_label = tk.Label(self.root, textvariable=current_player,
                                width=12, anchor=tk.CENTER, font=('Arial', 20))
        person_label.grid(row=1, column=1)

        winner = tk.StringVar()
        winner.set('')
        winner_label = tk.Label(self.root, textvariable=winner, width=12,
                                height=4, anchor=tk.CENTER, fg='red',
                                font=('Arial', 25))
        winner_label.grid(row=2, column=1)
        self.winner = winner

        game_status= tk.StringVar()
        game_status.set('')
        game_status_label = tk.Label(self.root, textvariable=game_status,
                                     width=12, height=4, anchor=tk.CENTER,
                                     font=('Arial', 18))
        game_status_label.grid(row=3, column=1)
        self.game_status = game_status

        # Reset button
        reset_button = tk.Button(self.root, text='重新开始', font=20, width=8,
                                 command=self.on_reset_game)
        reset_button.grid(row=4, column=1)

    def draw_gobang_board(self):
        gobang_board = tk.Canvas(self.root, bg='saddlebrown',
                                 width=540, height=540)
        gobang_board.bind('<Button-1>', self.on_mouse_click)
        gobang_board.grid(row=0, column=0, rowspan=5)

        for i in range(15):
            # horizontal
            gobang_board.create_line(35, (35* i + 35), 525, (35 * i + 35))
            # vertical
            gobang_board.create_line((35 * i + 35), 35, (35 * i + 35), 525)

        self.gobang_board = gobang_board

    def draw_ticks(self):
        for i in range(15):
            label = tk.Label(self.gobang_board, text=str(i + 1), fg='black',
                             bg='saddlebrown', width=2, anchor=tk.E)
            label.place(x=5, y=35 * i + 25)

        for i in range(15):
            label = tk.Label(self.gobang_board, text=chr(i + 65), fg='black',
                             bg='saddlebrown')
            label.place(x=35 * i + 30, y = 5)

    def on_reset_game(self):
        """When user clicks reset game button, reset game."""
        self._current_player = self.PLAYER_BLACK
        self.set_current_player()
        self.winner.set('')
        self.game_status.set('')
        self.black_pieces = []
        self.white_pieces = []
        self.pieces.clear()
        self.draw_current_piece_color()
        self.gobang_board.delete('PIECE')
        self._game_over = False

    def draw_current_piece_color(self):
        piece_size = self.piece_size
        piece_color = self.get_current_piece_color()
        self.side_canvas.delete('current_piece_color')
        self.side_canvas.create_oval(
            110 - piece_size, 25 - piece_size,
            110 + piece_size, 25 + piece_size,
            fill=piece_color, tags=('curent_piece_color'))

    def set_current_player(self):
        if self._current_player == self.PLAYER_BLACK:
            self.current_player.set('执黑棋')
        else:
            self.current_player.set('执白棋')

    def flip_internal_current_player(self):
        if self._current_player == self.PLAYER_BLACK:
            self._current_player = self.PLAYER_WHITE
        else:
            self._current_player = self.PLAYER_BLACK

    def get_current_piece_color(self):
        if self._current_player == self.PLAYER_BLACK:
            return 'black'
        return 'white'

    def on_mouse_click(self, event):
        """When user clicks mouse button, drop a piece."""
        if self._game_over:
            return
        gobang_board = self.gobang_board
        item = gobang_board.find_closest(event.x, event.y)
        tags = gobang_board.gettags(item)
        if len(tags) > 1 and tags[0] == '__INTERACTABLE_PIECE':
            x, y = [int(x) for x in list(tags)[1:3]]
            if (x, y) not in self.pieces:
                piece_color = self.get_current_piece_color()
                self.put_piece(x, y, piece_color)
                if self.check_win(x, y, piece_color):
                    return self.game_over()
                self.flip_internal_current_player()
                self.set_current_player()
                self.draw_current_piece_color()

    def put_piece(self, x, y, piece_color):
        piece_size = self.piece_size
        self.gobang_board.create_oval(
            x - 2 * piece_size, y - 2 * piece_size,
            x + 2 * piece_size, y + 2 * piece_size,
            fill=piece_color, tags=('PIECE',))
        if piece_color == 'white':
            colored_pieces = self.white_pieces
        else:
            colored_pieces = self.black_pieces
        colored_pieces.append((x, y))
        self.pieces[(x, y)] = piece_color

    def check_win(self, x, y, piece_color):
        for dir0, dir1 in (((-1, 0), (1, 0)),
                           ((-1, -1), (1, 1)),
                           ((0, -1), (0, 1)),
                           ((1, -1), (-1, 1))):
            cnt = -1  # To neutralize the extra cnt
            cnt += self._cnt_same_pieces_towards(x, y, piece_color, dir0)
            cnt += self._cnt_same_pieces_towards(x, y, piece_color, dir1)
            if cnt >= 5:
                return True
        return False

    def _cnt_same_pieces_towards(self, x, y, piece_color, direction):
        dir_x, dir_y = direction
        cell_size = self.cell_size
        cnt = 0
        while (x >= cell_size and x < 16 * cell_size and
               y >= cell_size and y < 16 * cell_size and
               (x, y) in self.pieces and self.pieces[(x, y)] == piece_color):
            cnt += 1
            x += cell_size * dir_x
            y += cell_size * dir_y
        return cnt

    def game_over(self):
        self._game_over = True
        self.game_status.set('游戏结束')
        self.winner.set('{}方胜利'.format(self.current_player.get()))

    def start(self):
        self.root.mainloop()


if __name__ == '__main__':
    gobang = Gobang()
    gobang.start()
