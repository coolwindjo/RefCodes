import cv2, os
import shutil

img_last = None # 이전 프레임을 저장할 변수
no = 0 # 이미지 장 수
save_dir = "./exfish" # 저장 디렉터리 이름
if os.path.exists(save_dir):
    shutil.rmtree(save_dir)
os.mkdir(save_dir) # 디렉터리 만들기

cv2.namedWindow("origin")
cv2.moveWindow("origin", 0, 20)
cv2.namedWindow("diff")
cv2.moveWindow("diff", 680, 20)

# 동영상 파일로부터 입력받기
cap = cv2.VideoCapture("images/fish.mp4")
while True:
    # 이미지 추출하기
    is_ok, frame = cap.read()
    if not is_ok: break
    frame = cv2.resize(frame, (640, 360))
    # 흑백 이미지로 변환하기
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (15, 15), 0)
    img_b = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)[1]
    # img_b = cv2.threshold(gray, 180, 255, cv2.THRESH_BINARY)[1]
    # 차이 확인하기
    if not img_last is None:
        frame_diff = cv2.absdiff(img_last, img_b)
        cnts, hierarchy = cv2.findContours(frame_diff.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

        cv2.imshow("origin", frame)
        cv2.imshow("diff", frame_diff)
        cv2.waitKey(22)

        # 차이가 있는 부분을 파일로 출력하기
        for pt in cnts:
            x, y, w, h = cv2.boundingRect(pt)
            if w < 100 or w > 500: continue # 노이즈 제거하기
            # 추출한 영역 저장하기
            imgex = frame[y:y+h, x:x+w]
            outfile = save_dir + "/" + str(no) + ".jpg"
            cv2.imwrite(outfile, imgex)
            no += 1

    img_last = img_b
cap.release()
print("ok")
