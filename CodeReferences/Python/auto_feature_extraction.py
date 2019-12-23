import urllib
import sys
import os.path
import extract_zip as ext
import params as pa
import glob
import threading
import re
import os
import glob
import subprocess
import threading, Queue
import requests
import psutil
import time
from shutil import copyfile
from shutil import copytree
from filelock import FileLock
import utility as ut
import multiprocessing
import threading


list_file = pa.list_file
destination = pa.database_path
drive_list = pa.drive_list
download_lock = FileLock("")
converted_file_list = []

def run_mpc55(database_path, src_file):

    mpc_path = pa.mpc_path + "/build\images"

    cvt_postfix = pa.cvt_postfix

    list_converted_dat = []

    # set converter working directory.
    mpc_working_dir = mpc_path

    mpc_working_dir = mpc_working_dir.replace("\\", "/")
    os.chdir(mpc_working_dir)

    # DAT play list back-up
    datplaylist_src = mpc_path + "/DATplayList/MonoDATList.datpls"
    datplaylist_dst = datplaylist_src + ".bak"

    datplaylist_src = datplaylist_src.replace("/", "\\")
    datplaylist_dst  = datplaylist_dst.replace("/", "\\")

    if os.path.isfile(datplaylist_src) and os.access(datplaylist_src, os.R_OK):
        copyfile(datplaylist_src, datplaylist_dst)

    converted_dat = glob.glob(database_path + "/" + src_file + cvt_postfix + "*.dat")
    num_dat = len(converted_dat)
    if  num_dat > 0 :
        print "MPC path: " + mpc_path
        print "Database path: " + database_path
        org_name = converted_dat[:-4]

        dat_file_name = converted_dat[0]
         
        # update play list.
        playlist_file_name = mpc_path + "/DATplayList/MonoDATList.datpls";
        f = open(playlist_file_name, "w")
        f.write(dat_file_name)
        f.close()

        # run MPC
        bin_path = mpc_path + "/../win64_vs2015/x64/Release_SingleThread/adas_mpc55.exe"
        exec_path = bin_path + " B0/config/run_win64.sh"
        
        print('mpc path' + exec_path)
        print('debugger path' + pa.debugger_path)
        run_debugger(pa.debugger_path)        
        time.sleep(4)
       
        if subprocess.call(exec_path) == 0 : 
            # DAT play list roll-back
            datplaylist_dst = mpc_path + "/DATplayList/MonoDATList.datpls"
            datplaylist_src = datplaylist_src + ".bak"

            datplaylist_src = datplaylist_src.replace("/", "\\")
            datplaylist_dst  = datplaylist_dst.replace("/", "\\")

            if os.path.isfile(datplaylist_src) and os.access(datplaylist_src, os.R_OK):
                copyfile(datplaylist_src, datplaylist_dst)
                os.remove(datplaylist_src)
      
    return num_dat

def read_ground_truth(src_path) :  
    f = open(src_path, 'r')
    vehicle_info = []
    lines = f.readlines()
    framecount_prefix = "framecount"
    frameend_prefix = r"</frame>"

    min_interval = 1000
    framecount = 0
    prev_framecount = 0;
    for line in lines :
        object_flag = False;      
        
        if framecount_prefix in line :
            idx = line.find(framecount_prefix)
            phase = line[idx - 1:]           
            str_framecount = re.findall(r'\d+', phase)
            framecount = int(str_framecount[0])             
            

        # get the frame interval at each frame
        if frameend_prefix in line : 
           if framecount != 0 and framecount % 10 == 0:
               frame_interval = framecount - prev_framecount
               if min_interval > frame_interval:
                    min_interval = frame_interval
               prev_framecount = framecount

    return min_interval

def get_gt_skip_interval(src_file, gt_path):
    object_list = ['_Vehicle', '_Pedestrian']
    src_dir = gt_path + '\\' + src_file + '\\' + "*.xml"
    gt_list = glob.glob(src_dir)
    skip_interval = 0
    for gt_file in gt_list:
        for object_prefix in object_list :
            if object_prefix in gt_file :
                skip_interval = read_ground_truth(gt_file)
  
    return skip_interval

def convert_data(src_path, converted_file_list, num_converted, file_name):
    #Convert data when the data is not in the converted file list.
    
    converter_path = pa.converter_path
    cvt_postfix = pa.cvt_postfix

    print "Converter path: " + converter_path
    print "Source path: " + src_path

    # set converter working directory.
    idx = converter_path.rfind("\\")
    cvt_working_dir = converter_path[0:idx]
    os.chdir(cvt_working_dir)

    if src_path.endswith(".dat"):

        # get skpi inteval of gt.
        skip_interval = get_gt_skip_interval(file_name, pa.ground_truth_path)
        
        #if skip_interval == 1 or skip_interval == 0:
        if skip_interval == 1:    
            filepath = pa.list_file
            if False:
                with open(filepath, "a") as f:
                    f.write(filename)
                print("strange file was detected.\n")                
            converted_file_list.append(file_name)    
            num_converted = num_converted + 1
            time.sleep(7)            

        else :
            path_without_ext = src_path[:-4]
            cvt_name_guess = path_without_ext + cvt_postfix + "*.dat"

            src_file = src_path
            cal_file = path_without_ext + "_Cal.xml"
            #command = converter_path + " " + src_file + " " + "-training" + " " + str(skip_interval)      
            command = converter_path + " " + src_file      
    
            if subprocess.call(command) == 0 :                           
                print("raw data conversion was done.\n")                
                converted_file_list.append(file_name)    
                num_converted = num_converted + 1
                time.sleep(7)            
     
    return num_converted  

def convert_process(site_url, url_list, destination, num_file):

    global download_lock
    global converted_file_list
    num_converted = 0
    pre_downloaded_file_list = []
    pre_converted_file_list = []

    src_files = os.listdir(destination + '\\') 

    for src_file in src_files:
        if ".dat" in src_file:
            c_idx = src_file.rfind(pa.cvt_postfix)
            if c_idx == -1:
                pre_downloaded_file_list.append(src_file)

    for downloaded_file in pre_downloaded_file_list:
        idx = downloaded_file.rfind('.dat')
        downloaded_file_name = downloaded_file[:idx]
        dst_path = destination + '\\' + downloaded_file_name + pa.cvt_postfix + "*.dat"
        converted_full_path = glob.glob(dst_path)

        if len(converted_full_path) != 0 :      
            converted_file_list.append(downloaded_file_name)            
            num_converted = num_converted + 1      
        else :
            src_path = destination + '\\' + downloaded_file
            num_converted = convert_data(src_path, converted_file_list, num_converted, downloaded_file_name)

    while num_file != num_converted :
        for i in range(0, num_file - 1, 1):      
            file_url = site_url + "/" + url_list[i]
            idx = file_url.rfind('/')
            file_name = file_url[idx+1:]
            src_path = destination + "/" + file_name + ".dat"            
            
            file_idx = download_lock.lock_file.rfind('/')

            if file_idx != -1:
                download_file_name = download_lock.lock_file[file_idx+1:]
                data_idx = download_file_name.rfind('.dat')
                locked_data_name = download_file_name[:data_idx]      

                #if the data is not locked data.
                if locked_data_name != file_name:      
                    if os.access(src_path, os.F_OK and os.X_OK):      
                        converted_flag = False
                        for converted_file_name in converted_file_list:                               
                            if file_name == converted_file_name:
                                converted_flag = True

                        if converted_flag is False:
                            print("[" + str(i+1) + "/" + str(num_file) + "]" + file_name)                            
                            num_converted = convert_data(src_path, converted_file_list, num_converted, file_name)
            
        # for last data convert.
        if download_lock._lock_counter == 1:
            file_idx = download_lock.lock_file.rfind('/')
            download_file_name = download_lock.lock_file[file_idx+1:]
            data_idx = download_file_name.rfind('.dat')
            locked_data_name = download_file_name[:data_idx]
            src_path = destination + "/" + locked_data_name + ".dat"  

            if file_idx != -1:
                if os.access(src_path, os.F_OK and os.X_OK):      
                    converted_flag = False
                    for converted_file_name in converted_file_list:                               
                        if locked_data_name == converted_file_name:
                            converted_flag = True

                    if converted_flag is False:
                        num_converted = convert_data(src_path, converted_file_list, num_converted, locked_data_name)
            
        if num_converted is num_file:
            print ('converting all raw dat was done.\n')


def download_dat_file(src, dst):
    ret = urllib.urlopen(src)
    global download_lock

    # test if source file exists.
    if ret.code == 200:
        # test if destination file exists
        if os.path.isfile(dst) and os.access(dst, os.R_OK):
            print(src + " already exists.\n")
        else:                
            print dst + "is locked.\n"
            download_lock = FileLock(dst)                   
            print dst + "is released.\n" 
            urllib.urlretrieve(src, dst)
    else:
        print(src + " not exists.\n")

def download_file(src, dst):
    ret = urllib.urlopen(src)

    # test if source file exists.
    if ret.code == 200:
        # test if destination file exists
        if os.path.isfile(dst) and os.access(dst, os.R_OK):
            print(src + " already exists.\n")
        else:
            urllib.urlretrieve(src, dst)
    else:
        print(src + " not exists.\n")


def download_process(site_url, url_list, destination, num_file, drive_list):

    global download_lock
   
    for drive in drive_list:
        free_space_GB = ut.get_free_space_GB(drive)

    for i in range(0, num_file, 1):
        list_dat = glob.glob(destination + "/" + "*.dat")
        """
        for file in list_dat:
            del_path = file
            try:
                os.unlink(del_path)
            except OSError as e:
                print e.message
        """
        file_url = site_url + "/" + url_list[i]
        idx = file_url.rfind('/')
        file_name = file_url[idx+1:]

        # Calibration file.
        src_url = file_url + "/Calibration.xml"
        dst_file_name = destination + "/" + file_name + "_Cal.xml"
        download_file(src_url, dst_file_name)

        # Gt file.
        src_url = file_url + "/GT/" + file_name + ".zip"
        dst_file_name = destination + "/" + file_name + ".zip"
        download_file(src_url, dst_file_name)

        # extract zip file.
        ext.extract_zip(dst_file_name, pa.ground_truth_path) 

        # Dat file.
        src_path = pa.data_server_path + '/' + url_list[i] + '/'+ file_name + ".dat"
        dst_file_name = destination + "/" + file_name + ".dat"            
        
        ut.copy_dat_files(src_path, dst_file_name, file_name, download_lock, i, num_file)      
        print("[" + str(i+1) + "/" + str(num_file) + "]" + file_name)

    print('Downloading raw dat is done.')
    download_lock._lock_counter = 1

def run_debugger(src_path):    
    idx = src_path.rfind('ObjectDebugger.exe')
    dst_path = src_path[:idx] + "..\\..\\ObjectDebugger\\ObjectDebugger.exe"

    FileName = ut.file_name_from_path(dst_path)    
    flag = ut.process_exists(FileName)  # check whether objecdebugger is running
    if flag :
        ut.kill_program(FileName)
        time.sleep(1)

    if os.path.isfile(src_path) and os.access(src_path, os.R_OK):
        if os.path.isfile(dst_path) :
            os.remove(dst_path)
           
        copyfile(src_path, dst_path)
        ut.run_program(dst_path)

    else:
        print 'fail to find object debugger.\n'

def extract_feature_process(num_file, destination):
    global converted_file_list
    extracted_list = []
    num_extracted = 0
    
    while num_extracted != num_file:        
        for converted_file in converted_file_list:
          extracted_flag = False  
          for extracted_file in extracted_list:
              if converted_file == extracted_file:
                 extracted_flag = True

          if extracted_flag is False:
            
            flag = run_mpc55(destination, converted_file) 
            if flag > 0 :
                num_extracted = num_extracted + 1
                extracted_list.append(converted_file)

    print('extracting feature was done.\n')        

def call_threads(site_url, url_list, destination, num_file, drive_list):
      
    # download all data.
    thread0 = threading.Thread(target = download_process, args = (site_url, url_list, destination, num_file, drive_list))

    # conversion.
    thread1 = threading.Thread(target = convert_process, args = (site_url, url_list, destination, num_file))

    # extract feature.
    #thread2 = threading.Thread(target = extract_feature_process, args = (num_file, destination,))

    thread0.start()
    thread1.start()
    #thread2.start()

    thread0.join()
    thread1.join()
    #thread2.join()        

if __name__ == '__main__':
    #ut.copy_dll_files("/lib/hagllib/bin")
    #ut.copy_dll_files("/lib/svnetwlib/bin")
    #ut.copy_dll_files("/lib/svnetpc")
    #ut.copy_dll_files("/lib/FPE_Accel")
    #ut.copy_dll_files("/lib/opencv3.1.0/x64/vc14/bin")
    #ut.copy_dll_files("/lib/ISP_CUDA")

    print("list file: " + list_file)
    print("destination: " + destination)

    site_url = "http://cosette.lge.com:8080"

    try:
        f = open(list_file, "r")
    except IOError:
        print("Failed to open list file.\n")
        exit(-1)

    # read file list.
    url_list = []
    num_file = 0

    lines = f.readlines()
    for line in lines:
        if line[-1]  == '\n':
            line = line[:-1]
            url_list.append(line)
        else :
            url_list.append(line)
    num_file = len(lines)

    f.close()

    if not os.path.exists(destination):
        os.makedirs(destination)

    thread = threading.Thread(target = call_threads, args = (site_url, url_list, destination, num_file, drive_list))
    thread.start()
    thread.join()  




