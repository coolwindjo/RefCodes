# -*- coding: utf-8 -*-
##  @package Homography
#   Documentation for this module
#
#   More details
import sys
import numpy as np
import cv2
import matplotlib.pyplot    as plt

class ManageImage(object):
    """A class for getting input from a user"""
    
    def __init__(self, *args, **kwargs):
        return super(ManageImage, self).__init__(*args, **kwargs)
    
    def handle_image(self):
        imgfile='camera_image.png'
        img = cv2.imread(imgfile, cv2.IMREAD_COLOR)

        cv2.imshow('Plot', img)
        cv2.waitKey(0)
        cv2.destroyAllWinodws()


def main():
    
    from mpl_toolkits.mplot3d   import axes3d
    try:
        print("len(H) = " + str(len(H)))

    except :
        print("[Error] Unexpected error at main().", sys.exc_info()[0])
        print("len(H) = " + str(len(H)))

    return

if __name__ == "__main__":
    main()