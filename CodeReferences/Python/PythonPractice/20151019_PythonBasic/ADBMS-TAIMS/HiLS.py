# -*- coding: utf-8 -*- 
import os
import sys
import subprocess
import time
targetID = 'root'
targetPW = 'root'

def execute(cmd):
   print(cmd)
   sys.stdout.flush()
   return os.system(cmd)

def executePIPE(cmd):
    fd = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return fd.stdout, fd.stderr

def plink(targetIP, cmd):
    execute('echo y | plink -pw ' + targetPW + ' ' + targetID + '@' + targetIP + ' ' + cmd)

def pscp(targetIP, src, dest):
    execute('echo y | pscp -pw ' + targetPW + ' -r "' + src + '" ' + targetID + '@' + targetIP + ':' + dest) 

def RelaySwitchControl(switchIP, cmd):
    execute('RelaySwitchControl ' + switchIP + ' ' + cmd)

def Boot(switchIP):
    RelaySwitchControl(switchIP, 'OFF OFF OFF OFF OFF OFF')
    time.sleep(10)
    RelaySwitchControl(switchIP, 'OFF OFF ON ON OFF OFF')

def BootWait(targetIP):
    sec = 0
    
    while True:
   print('Boot wating...')
   
   std_out, std_err = executePIPE('ping -n 1 ' + targetIP)
   result = std_out.read()
   print result
   
   if result.find(targetIP + u'�� ����'.encode('euc-kr')) != -1:
    break
   
   sec = sec + 1
   if sec >= 60:
    print('Boot time out.')
    return 1
  
  print('Boot completed.')
  return 0
def TurnOff(switchIP):
 RelaySwitchControl(switchIP, 'OFF OFF OFF OFF OFF OFF')
def ImageWrite(targetIP, imageDir):
 plink(targetIP, 'killall rpmain')
 pscp(targetIP, imageDir + '/*', '/mnt')
 plink(targetIP, 'sync')
def CalibParamWrite(targetIP, calibParamDir):
 pscp(targetIP, calibParamDir + '/FCAL.LUT', '/mnt/opt/bin')
 pscp(targetIP, calibParamDir + '/Calibration.xml', '/mnt/config')
 pscp(targetIP, calibParamDir + '/Calibration_rewritable.xml', '/mnt/config')
 plink(targetIP, 'sync')

