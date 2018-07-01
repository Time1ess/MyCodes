class Level:
    NOTSET = -1
    RESPONDENT = 0
    DIRECTOR = 1
    MANAGER = 2

    _level = None

    def __init__(self, level):
        self._level = level

    @classmethod
    def get_initial_level(cls):
        return cls(cls.RESPONDENT)

    @property
    def level(self):
        return self._level

    def increment(self):
        self._level += 1
        if self._level <= self.MANAGER:
            return True
        return False

    def __str__(self):
        return '%d' % self._level
