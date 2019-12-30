class Record(object):
    def __init__(self, name):
        self.name = name
        self.scores = {}

    def set_score(self, subject, score):
        self.scores[subject] = score

    def get_score(self, subject):
        return self.scores.get(subject, 0)

    @classmethod
    def input(cls):
        result = []
        want_input = True
        while want_input:
            want_input, r = cls.create()
            result.append(r)
        return result

    @classmethod
    def create(cls):
        name = None
        while not name:
            name = input("이름:")

        r = Record(name)
        score_lang = None
        while not score_lang:
            score_lang = int(input("국어:"))
        r.set_score("국어", score_lang)

        score_eng = None
        while not score_eng:
            score_eng = int(input("영어:"))
        r.set_score("영어", score_eng)

        score_math = None
        while not score_math:
            score_math = int(input("수학:"))
        r.set_score("수학", score_math)

        want_continue = None
        while want_continue != "y" and \
            want_continue != "y" and \
            want_continue != "n" and \
            want_continue != "N" :
            want_continue = input("계속 입력하시겠습니까(y/n)?")
        if want_continue == 'n' or want_continue == 'N':
            return False, r
        else:
            return True, r
