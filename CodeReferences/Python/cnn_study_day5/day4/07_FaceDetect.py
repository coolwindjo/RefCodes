import cv2
import matplotlib.pyplot as plt

cascade_file = 'data/haarcascade_frontalface_alt.xml'
cascade = cv2.CascadeClassifier(cascade_file)

img = cv2.imread('images/family.jpg')
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

face_list = cascade.detectMultiScale(img_gray, minSize=(150, 150))

if len(face_list) == 0:
    print('can not find face')
    quit()

for (x, y, w, h) in face_list:
    print('face point (x, y, w, h) = ({}, {}, {}, {})'.format(x, y, w, h))
    red = (0, 0, 255) #opencv는 BGR 사용
    cv2.rectangle(img, (x, y), (x+w, y+h), red, thickness=20)

cv2.imwrite('face-detect.png', img)
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.show()

