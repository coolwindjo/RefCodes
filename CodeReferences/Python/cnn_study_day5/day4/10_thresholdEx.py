import numpy as np
import cv2

img = cv2.imread('test.png', cv2.IMREAD_GRAYSCALE)
#threshold()는 문턱 값과 문턱 값이 적용된 이미지파일을 리턴
#매개 변수 (이미지, threshhold, maxvalue, 정책)
ret, thr1 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)# 픽셀 값이 threshold_value 보다 작으면 0, 크면 value로 할당
ret, thr2 = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY_INV)# 픽셀 값이 threshold_value 보다 크면 0, 작은면 value로 할당
ret, thr3 = cv2.threshold(img, 127, 255, cv2.THRESH_TRUNC)# 픽셀 값이 threshold_value 보다 크면 threshold_value, 작은면 픽셀 값 그대로 할당
ret, thr4 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO)# 픽셀 값이 threshold_value 보다 크면 픽셀 값, 작은면 0 할당
ret, thr5 = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO_INV) # 픽셀 값이 threshold_value 보다 크면 0, 작은면 픽셀 값 할당

cv2.imshow('original', img)
cv2.imshow('BINARY', thr1)
cv2.imshow('BINARY_INV', thr2)
cv2.imshow('TRUNC', thr3)
cv2.imshow('TOZERO', thr4)
cv2.imshow('TOZERO_INV', thr5)

cv2.waitKey(0)
cv2.destroyAllWindows()