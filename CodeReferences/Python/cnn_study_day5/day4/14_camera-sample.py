import cv2

cap = cv2.VideoCapture(0)#0은 첫번째 카메라 만약 2개 있으면 1은 두번째 카메라를 지칭함
while True:
    _, frame = cap.read() #리턴값 ret(제대로 읽어오면 True 못읽어오면 False), frame(프레임 정보)
    frame = cv2.resize(frame, (500,300))
    cv2.imshow('OpenCV Web Camera', frame)
    k = cv2.waitKey(1) # 1msec 대기
    if k == 27 or k == 13: break #27 => esc키 13 => enter키

cap.release() # 카메라 해제하기
cv2.destroyAllWindows() # 윈도우 제거하기

