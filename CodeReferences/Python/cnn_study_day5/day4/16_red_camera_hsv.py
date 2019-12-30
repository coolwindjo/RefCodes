import cv2
import numpy as np
#HSV = > Hue(색상) Saturation(채도)  ValueBrightness(명도)
#붉은색으로 추출한 후 흰색으로 출력
# 웹 카메라로부터 입력받기
cap = cv2.VideoCapture(0)
while True:
    # 이미지 추출하고 축소하기
    _, frame = cap.read()
    frame = cv2.resize(frame, (500,300))
    # 색공간을 HSV로 변환하기
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV_FULL)
    # HSV 분할하기
    h = hsv[:, :, 0] #Hue(색상)
    s = hsv[:, :, 1] #Saturation(채도)
    v = hsv[:, :, 2] #ValueBrightness(명도)
    # 붉은색을 가진 요소만 출력하기
    img = np.zeros(h.shape, dtype=np.uint8)
    img[((h < 50) | (h > 200)) & (s > 100)] = 255 #붉은 색을 흰색으로 변환
    # 윈도우에 이미지 출력하기
    cv2.imshow('RED Camera', img)
    if cv2.waitKey(1) == 13: break

cap.release() # 카메라 해제하기
cv2.destroyAllWindows() # 윈도우 제거하기

