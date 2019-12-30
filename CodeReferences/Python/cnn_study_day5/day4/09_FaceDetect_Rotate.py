import cv2
import matplotlib.pyplot as plt
from scipy import ndimage

def face_detct(img):
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    face_list = cascade.detectMultiScale(img_gray, minSize=(150, 150))
    for (x, y, w, h) in face_list:
        print('face point (x, y, w, h) = ({}, {}, {}, {})'.format(x, y, w, h))
        red = (0, 0, 255)  # opencv는 BGR 사용
        cv2.rectangle(img, (x, y), (x + w, y + h), red, thickness=20)

cascade_file = 'data/haarcascade_frontalface_alt.xml'
cascade = cv2.CascadeClassifier(cascade_file)

img = cv2.imread('images/girl.jpg')

for i in range(0, 9):
    ang = i * 10
    print('-----', ang, '-----')
    img_r = ndimage.rotate(img, ang)
    face_detct(img_r)

    plt.subplot(3, 3, i+1)
    plt.axis('off')
    plt.title('angle: ' + str(ang))
    plt.imshow(cv2.cvtColor(img_r, cv2.COLOR_BGR2RGB))
plt.show()