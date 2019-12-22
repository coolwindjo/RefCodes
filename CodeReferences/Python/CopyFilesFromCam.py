# -*- coding: utf-8 -*-
#@package Copy files to folders
import sys
from shutil import copyfile
from shutil import move
import os.path
import time
import datetime
from pathlib import Path
from PIL import Image
from PIL.ExifTags import TAGS
'''
import cv2
'''

DRIVE_CAM = 'E:'
PHOTO_DIR_IN_CAM = 'DCIM'
PHOTO_EXT = 'GIF'
# VIDEO_DIR_IN_CAM = 'MP_ROOT'
VIDEO_DIR_IN_CAM = PHOTO_DIR_IN_CAM
VIDEO_EXT = 'MP4'
DIR_COPY_TO = 'U:/Pics'

'''
def get_exif(path):
    ret = {}
    i = Image.open(path)
    info = i._getexif()
    for tag, value in info.items():
        decoded = TAGS.get(tag, tag)
        ret[decoded] = value
    return ret

def get_video_info(path):
    cap = cv2.VideoCapture(path)
    fps    = cap.get(cv2.CAP_PROP_FPS)
    print('fps=',fps)
    length_of_video = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    width  = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    return fps
'''

def get_date_taken(path):
    if (path[-3:] == 'jpg') or (path[-3:] == 'JPG'):
        try:
            ret = Image.open(path)._getexif()[36867]
            return ret
        except :
            print(sys.exc_info()[0]) 
    date = datetime.datetime.strptime(time.ctime(os.path.getmtime(path)), "%a %b %d %H:%M:%S %Y")
    print("Last modified: %s" % time.ctime(os.path.getmtime(path)))
    return date.strftime("%Y:%m:%d")

def copy_file(src, dst):
    ret = os.path.isfile(src) and os.access(src, os.R_OK)
    if ret == True:
        if os.path.isfile(dst) and os.access(dst, os.R_OK):
            print(src + " already exists.")
        else:
            copyfile(src, dst)
    else:
        print(src + " does not exist.")
        print("Error: " + src + " is failed to be copied.")
        exit(-1)

def move_file(src, dst):
    ret = os.path.isfile(src) and os.access(src, os.R_OK)
    if ret == True:
        if os.path.isfile(dst) and os.access(dst, os.R_OK):
            print(src + " already exists.")
        else:
            move(src, dst)
    else:
        print(src + " does not exist.")
        print("Error: " + src + " is failed to be copied.")
        exit(-1)

def set_args():
    program_name = sys.argv[0]
    arguments = sys.argv[1:]
    arg_cnt = len(arguments)
    working_dir = ''
    if arg_cnt == 1:
        working_dir = arguments[0]
        print("Working directory is " + working_dir)
    else:
        print("Error: check the usage [" + program_name + " <working directory>]")
    return working_dir

def make_date_pics_list(date_dir, src_path):
    date_and_pics = []
    pics = []
    date_and_pics.append(date_dir)
    date_and_pics.append(pics)
    pics.append(src_path)
    return date_and_pics

def make_date_dir(dir_path, trgt_dir_name, trgt_ext):
    date_and_pics_list = []
    previous_date = ''
    total_num_pics = 0
    for dir_name in os.listdir(dir_path):
        if dir_name == trgt_dir_name:
            root_path = os.path.join(dir_path, dir_name).replace('\\','/')
            for inner_root, s, files in os.walk(root_path):
                if len(files) > 0:
                    for pic in files:
                        if (pic[-3:] == trgt_ext) or (pic[-3:] == trgt_ext.lower()):
                            pic_abs_path = os.path.join(inner_root, pic).replace('\\','/')
                            pic_date = get_date_taken(pic_abs_path)
                            pic_date = pic_date[:10].replace(':', '_')
                            src_path = inner_root.replace('\\','/') + '/' + pic
                            total_num_pics+=1
                            if (pic_date != previous_date) or (previous_date == ''):
                                date_dir = DIR_COPY_TO + '/' + pic_date
                                try:
                                    Path(date_dir).mkdir(parents=True, exist_ok=True)
                                    print("New directory " + pic_date + " is created!")
                                except FileExistsError:
                                    print("Warning: ", sys.exc_info()[0]) 
                                date_and_pics = make_date_pics_list(date_dir, src_path)
                                date_and_pics_list.append(date_and_pics)
                                previous_date = pic_date
                            else:
                                date_and_pics[1].append(src_path)
    return date_and_pics_list, total_num_pics

def move_images(working_dir, trgt_dir_name, trgt_ext):
    date_and_pics_list, total_num_pics = make_date_dir(working_dir, trgt_dir_name, trgt_ext)
    num_dir_pics = 0
    for date_and_pics in date_and_pics_list:
        date_dir = date_and_pics[0]
        num_dir_pics += len(date_and_pics[1])
        print("Pictures or Videos[" + str(num_dir_pics) + "/" + str(total_num_pics)
               + "(" + str(100*round(num_dir_pics/total_num_pics,3)) + "%)] are being moved to " + date_dir)
        for pic_path in date_and_pics[1]:
            idx = pic_path.rfind('/')
            pic = pic_path[idx:]
            dst_path = date_dir + pic 
            move_file(pic_path, dst_path)
    return


def main():
    working_dir = set_args()
    if working_dir == '':
        working_dir = DRIVE_CAM + '/'
    working_dir = working_dir.replace("\\", "/")
    move_images(working_dir, PHOTO_DIR_IN_CAM, PHOTO_EXT)
    move_images(working_dir, VIDEO_DIR_IN_CAM, VIDEO_EXT)

if __name__ == '__main__':
    main()