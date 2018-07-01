from level import Level


class Call:
    def __init__(self, caller):
        self._caller = caller
        self._level = Level.get_initial_level()
        self._conversation = []  # Conversation logs
        self._solved = False

    @property
    def level(self):
        return self._level

    @property
    def solved(self):
        return self._solved

    def set_solved(self):
        self._solved = True

    def add_conversation(self, text):
        self._conversation.append(text)
