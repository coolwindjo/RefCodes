import statistics

from day2.record import Record

class MainMenu:
    use_guide = '''메인 메뉴)
1.입력
2.출력
3.검색
4.종료
번호를 입력하세요:'''

    data = {}

    @classmethod
    def start(cls):
        menu_funcs = {1:cls.input, 2:cls.show, 3:cls.search, 4:cls.quit}
        menu = int(input(cls.use_guide))
        func = menu_funcs.get(menu, cls.start)
        func()


    @classmethod
    def input(cls):
        records = Record.input()
        for r in records:
            cls.data[r.name] = r
        cls.start()

    @classmethod
    def show(cls):
        lang_scores = [0,]
        eng_scores = [0,]
        math_scores = [0,]
        print("------------------------------------------------------------------")
        print("이름\t국어\t영어\t수학\t총점\t평균")
        print("------------------------------------------------------------------")
        for r in cls.data.values():
            scores = (r.get_score('국어'), r.get_score('영어'), r.get_score('수학'))
            lang_scores.append(scores[0])
            eng_scores.append(scores[1])
            math_scores.append(scores[2])
            print("{}\t{}\t{}\t{}".format(r.name, scores[0], scores[1], scores[2]), end="\t")
            print("{}\t{}".format(sum(scores), statistics.mean(scores) ))
        print("------------------------------------------------------------------")
        print("총점: 국어 {}, 영어 {}, 수학 {}".format(sum(lang_scores), sum(eng_scores), sum(math_scores)))
        print("평균: 국어 %.2f, 영어 %.2f, 수학 %.2f"%(statistics.mean(lang_scores), statistics.mean(eng_scores), statistics.mean(math_scores)))
        print("최고점수: 국어 {}, 영어 {}, 수학 {}".format(max(lang_scores), max(eng_scores), max(math_scores)))

        cls.start()

    @classmethod
    def search(cls):
        keyword = input("검색할 이름을 입력하세요:")
        r = cls.data.get(keyword, None)
        if r:
            print("------------------------------------------------------------------")
            print("이름\t국어\t영어\t수학\t총점\t평균")
            print("------------------------------------------------------------------")
            print("{}\t{}\t{}\t{}".format(r.name, r.get_score('국어'), r.get_score('영어'), r.get_score('수학')))
            print("------------------------------------------------------------------")
        else:
            print("존재하지 않습니다")
        cls.start()


    @classmethod
    def quit(cls):
        print("종료합니다")


MainMenu.start()


