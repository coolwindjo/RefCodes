import cv2
import urllib.request as req

url = 'http://uta.pw/shodou/img/28/214.png'
req.urlretrieve(url, 'test.png')

img = cv2.imread('test.png')
print(img)

# cv2.imshow("image", img)
# cv2.waitKey(0)

import matplotlib.pyplot as plt
img = cv2.imread('images/test.jpg')
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.show()

cv2.imwrite('out.png', img)

im2 = cv2.resize(img, (600, 300))
cv2.imwrite('out-resize.png', im2)
plt.imshow(cv2.cvtColor(im2, cv2.COLOR_BGR2RGB))
plt.show()

im3 = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
plt.imshow(im3, cmap='gray')
plt.show()

#반전
im4 = 255 - img
plt.imshow(cv2.cvtColor(im4, cv2.COLOR_BGR2RGB))
plt.show()