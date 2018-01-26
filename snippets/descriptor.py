from weakref import WeakKeyDictionary

class Score:
    _insts = WeakKeyDictionary()

    @staticmethod
    def __validate_score(score):
        if score < 0 or score > 100:
            raise ValueError('Score can not be negative')

    def __get__(self, instance, owner):
        return self._insts.get(instance, None)

    def __set__(self, instance, value):
        self.__validate_score(value)
        self._insts[instance] = value

class ExamResult:
    student = ''
    score = Score()

    def __init__(self, student, score):
        self.student = student
        self.score = score


res = ExamResult('sam', 50)
res.score = -10
