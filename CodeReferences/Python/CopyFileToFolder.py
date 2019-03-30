# -*- coding: utf-8 -*-
#@package Copy files to folders
import sys
from shutil import copyfile
import os.path

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

def SetArguments():
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

def MakeFileListInFolder(folder_path):
    file_list = []
    for filename in os.listdir(folder_path):
        if filename.endswith("_Lane.xml"):
            origin_name = filename[:-9]
            os.makedirs(folder_path + '/' + origin_name)
            src_path = folder_path + '/' + origin_name + "_Lane.xml"
            dst_path = folder_path + '/' + origin_name + '/' + origin_name + "_Lane.xml" 
            copy_file(src_path, dst_path)
            file_list.append(origin_name)

    return file_list


def main():
    working_dir = SetArguments()
    if working_dir == '':
        working_dir = "D:\GitRepository\\tools\AlgorithmEvaluator\LabelingTool_v1.58\GroundTruth"
    working_dir = working_dir.replace("\\", "/")
    file_list = MakeFileListInFolder(working_dir)

if __name__ == '__main__':
    main()