import cv2
import matplotlib.pyplot as plt

# 이미지 읽어 들이고 크기 변경하기 --- (*1)
img = cv2.imread("images/hagaki1.png")

# 색공간 변경하기 --- (*2)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

gray = cv2.GaussianBlur(gray, (7, 7), 0)  #이미지를 블러 처리 => 복잡하고 세부적인 모양이 뭉개지면서 이미지가 흐려진다.

im2 = cv2.threshold(gray, 140, 255, cv2.THRESH_BINARY)[1]
# 흐리게 만든 이진화 이미지를 화면에 출력(흰색, 블랙)
# THRESH_BINARY_INV => 픽셀 값이 threshold_value 보다 크면 0, 작은면 value로 할당

# 화면 왼쪽에 변환한 이미지 출력하기 --- (*3)
plt.subplot(1, 2, 1)
plt.imshow(im2, cmap="gray")
# plt.show()

#이미지와 윤곽 정보, 윤곽의 상하구조(hierachy) 정보를 출력한다.
cnts, hierarchy = cv2.findContours(im2.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE) #윤곽 위에 있는 모든 점을 반환한다.

img_list = []
# 검출한 윤곽 그리기 --- (*5)
for pt in cnts:
    x, y, w, h = cv2.boundingRect(pt)
    # 너무 크거나 너무 작은 부분 제거하기
    if w < 30 or w > 200: continue
    print(x,y,w,h) # 결과 출력하기
    cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)
    img_list.append(img.copy()[y:y+h, x:x+w])

for i, countur_image in enumerate(img_list):
    cv2.imshow("{}".format(i), countur_image)
cv2.waitKey(0)


# 화면 오른쪽에 결과 출력하기 --- (*6)
plt.subplot(1, 2, 2)
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
# plt.savefig("find_contours.png", dpi=200)
plt.show()

