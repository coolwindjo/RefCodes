import cv2
import matplotlib.pyplot as plt

# 이미지 읽어 들이고 크기 변경하기 --- (*1)
img = cv2.imread("images/flower.jpg")
img = cv2.resize(img, (300, 169))

# 색공간 변경하기 --- (*2)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

#화이트 노이즈를 제거하는 효과가 있다.
#가우시안 함수를 사용하여 생성하고, 이 커널 함수를 통해 커널 영역 내의 픽셀값을 가중평균한 값으로 해당 픽셀을 대체한다.
#매개변수 (이미지, 커널의 크기, 가로방향 표준편차(0이면 전체크기를 기반으로 자동으로 지정된다))
gray = cv2.GaussianBlur(gray, (7, 7), 0)  #이미지를 블러 처리 => 복잡하고 세부적인 모양이 뭉개지면서 이미지가 흐려진다.

im2 = cv2.threshold(gray, 140, 240, cv2.THRESH_BINARY_INV)[1]
# 흐리게 만든 이진화 이미지를 화면에 출력(흰색, 블랙)
# THRESH_BINARY_INV => 픽셀 값이 threshold_value 보다 크면 0, 작은면 value로 할당

# 화면 왼쪽에 변환한 이미지 출력하기 --- (*3)
plt.subplot(1, 2, 1)
plt.imshow(im2, cmap="gray")


'''
cv2.findContours()의 파라미터
image - 그레이스케일 이미지 혹은 이진화한 이미지
mode : 컨투어를 찾는 방법으로 각 방법들에 대한 설명은 다음 표로 정리했다.
    mode	컨투어를 찾는 방법
        cv2.RETR_EXTERNAL	가장 외곽에 있는 윤곽만 검출
        cv2.RETR_LIST	단순한 윤곽 검출
        cv2.RETR_CCOMP	 계층을 고려해 2레벨 윤곽을 검출
        cv2.RETR_TREE	모든 윤곽을 검출하고 계층 구조로 저장
method : 컨투어를 찾을 때 사용하는 근사치 방법으로 이것 역시 다음 표로 정리했다.
    mode	컨투어를 표현하는 방법
        cv2.CHAIN_APPROX_NONE	모든 윤곽에 있는 모든 점을 반환
        cv2.CHAIN_APPROX_SIMPLE	의미없는 정보를 제거하고 점을 반환한다.
        cv2.CHAIN_APPROX_TC89_L1	Teh_Chin 연결 근사 알고리즘을 적용하여 컨투어 포인트를 줄임
        cv2.CHAIN_APPROX_TC89_KCOS	Teh_Chin 연결 근사 알고리즘을 적용하여 컨투어 포인트를 줄임
'''
#이미지와 윤곽 정보, 윤곽의 상하구조(hierachy) 정보를 출력한다.
cnts, hierarchy = cv2.findContours(im2.copy(),cv2.RETR_LIST,cv2.CHAIN_APPROX_SIMPLE) #윤곽 위에 있는 모든 점을 반환한다.

# 검출한 윤곽 그리기 --- (*5) 
for pt in cnts:
    x, y, w, h = cv2.boundingRect(pt)
    # 너무 크거나 너무 작은 부분 제거하기
    if w < 30 or w > 200: continue
    print(x,y,w,h) # 결과 출력하기
    cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)

# 화면 오른쪽에 결과 출력하기 --- (*6)
plt.subplot(1, 2, 2)
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.savefig("find_contours.png", dpi=200)
plt.show()

