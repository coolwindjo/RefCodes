# -*- coding: utf-8 -*- 
import os
import sys
import glob
import shutil
import time, datetime
#import ConfigParser
import xml.etree.ElementTree as ET
#import HilS

def execute(cmd):
   print(cmd)
   sys.stdout.flush()
   return os.system(cmd)

def userGlob(dir, pattern):
    list = glob.glob1(dir, pattern)
    
    for i in range(0, len(list)):
        list[i] = os.path.join(dir, list[i])
    return list

def DateStamp(time):
    return datetime.datetime.fromtimestamp(time).strftime('%Y-%m-%d')

def TimeStamp(time):
    return datetime.datetime.fromtimestamp(time).strftime('%Y-%m-%d %H:%M:%S')

def PrintTime(time):
    hr = time / 3600
    min = time % 3600 / 60
    sec = time % 60
    return '%02d'%(hr) + ':' + '%02d'%(min) + ':' + '%02d'%(sec)

class TestAutomation:
    def __init__(self, binaryImageDir, inputDir, filter):
        self.buildStartTime = time.time()
        
    # jenkins info
    self.projectName = os.getenv('JOB_NAME')
    self.buildNum = os.getenv('BUILD_NUMBER')
    self.workstation = os.getenv('NODE_NAME')
    self.operator = os.getenv('BUILD_USER')
    
    # input dir
    self.serverInputDir = os.path.join(os.getenv('SERVER_INPUT_ROOT'), inputDir).replace('\\', '/')
    if not os.path.exists(self.serverInputDir):
        print('[TestAutomation] Input directory not exist.')
        exit(1)
  
    # binary image dir
    self.binaryImageDir = os.path.join(os.getenv('SERVER_BINARY_IMAGE_ROOT'), binaryImageDir).replace('\\', '/')
    if not os.path.exists(self.binaryImageDir):
        print('[TestAutomation] Binary image directory not exist.')
        exit(1)
        
    # dbc file
    self.dbcFile = userGlob(os.path.join(self.binaryImageDir, 'config'), '*.dbc')[0].replace('\\', '/')
    if not os.path.exists(self.dbcFile):
        print('[TestAutomation] DBC file not exist.')
        exit(1)
  
    # ADTF config xml
    self.adtfConfigXml = os.getenv('ADTF_CONFIG_XML').replace('\\', '/')
    if not os.path.exists(self.adtfConfigXml):
        print('[TestAutomation] ADTF config xml file not exist.')
        exit(1)
  
    # filter
    self.filterDir = os.getenv('FILTER_DIR')
    self.filter = filter
  
    # IP
    config = ConfigParser.ConfigParser()
    config.read('workstation.cfg')
    self.workstationIP = config.get(self.workstation, 'IP')
    self.relaySwitchIP = config.get(self.workstation, 'RELAY_SWITCH_IP')
    
    self.LGBoxIP = os.getenv('LG_BOX_IP')
    
def GetInputDir(self):
    self.inputRoot = os.getenv('WORK_INPUT_ROOT').replace('\\', '/')
    if not os.path.exists(self.inputRoot):
        os.mkdir(self.inputRoot)
  
    self.inputDir = os.path.join(self.inputRoot, os.path.basename(self.serverInputDir)).replace('\\', '/')
    if os.path.exists(self.inputDir):
        shutil.rmtree(self.inputDir)
  
    execute('xcopy "' + self.serverInputDir + '" "' + self.inputDir + '/" /f/e/y')

    self.inputSubDirList = os.listdir(self.inputDir)
    if len(self.inputSubDirList) <= 0:
        print('[TestAutomation] Input sub directory not exist.')
        exit(1)

def GetInputSeqList(self, inputSubDir):
    execute('SequenceExporter "' + inputSubDir + '"')

    file = open(os.path.join(inputSubDir, 'SEQ_LIST.txt'), 'r')
    inputSeqList = file.read().splitlines()
    file.close()
    
    return inputSeqList
 
def SetOutputDir(self):
    # local output
    self.outputRoot = os.getenv('WORK_OUTPUT_ROOT').replace('\\', '/')
    if not os.path.exists(self.outputRoot):
        os.mkdir(self.outputRoot)

    self.projectDir = os.path.join(self.outputRoot, self.projectName).replace('\\', '/')
    if not os.path.exists(self.projectDir):
        os.mkdir(self.projectDir)

    self.buildDir = os.path.join(self.projectDir, '[' + self.buildNum + ']' + os.path.basename(self.binaryImageDir)).replace('\\', '/')
    if os.path.exists(self.buildDir):
        shutil.rmtree(self.buildDir)
    os.mkdir(self.buildDir)

    # server output
    self.serverRoot = os.getenv('SERVER_OUTPUT_ROOT').replace('\\', '/')
    
    self.serverProjectDir = os.path.join(self.serverRoot, self.projectName).replace('\\', '/')
    if not os.path.exists(self.serverProjectDir):
        os.mkdir(self.serverProjectDir)
        
    self.serverBuildDir = os.path.join(self.serverProjectDir, os.path.basename(self.buildDir)).replace('\\', '/')
    if os.path.exists(self.serverBuildDir):
        shutil.rmtree(self.serverBuildDir)
    os.mkdir(self.serverBuildDir)
 
def BuildInfoInsert(self):
    buildXml = ET.Element('Build', project_name=self.projectName, build_num=self.buildNum, build_name=os.path.basename(self.binaryImageDir), build_date=DateStamp(self.buildStartTime))
    
    infoListXml = ET.SubElement(buildXml, 'InfoList')
    ET.SubElement(infoListXml, 'Info', index='0', key='Test start at', value=TimeStamp(self.buildStartTime))
    ET.SubElement(infoListXml, 'Info', index='1', key='Test end at', value=TimeStamp(self.buildEndTime))
    ET.SubElement(infoListXml, 'Info', index='2', key='Test running time', value=PrintTime(int(self.buildEndTime)-int(self.buildStartTime)))
    ET.SubElement(infoListXml, 'Info', index='3', key='Input stream time', value=PrintTime(self.streamTimeTotal)) 
    ET.SubElement(infoListXml, 'Info', index='4', key='Workstation', value=self.workstation)
    ET.SubElement(infoListXml, 'Info', index='5', key='SW version', value=os.path.basename(self.binaryImageDir))
    
    filterList = self.filter.split(',')
    filterListXml = ET.SubElement(buildXml, 'FilterList')
    for i in range(0, len(filterList)):
        ET.SubElement(filterListXml, 'Filter', index=str(i), name=filterList[i])
    ET.SubElement(buildXml, 'Seq', total=str(self.seqTotal))
    
    buildXmlTree = ET.ElementTree(buildXml)
    
    buildXmlFile = os.path.join(self.serverBuildDir, os.path.basename(self.serverBuildDir) + '.xml').replace('\\', '/')
    buildXmlTree.write(buildXmlFile)
    
    execute('BuildInserter "' + buildXmlFile + '"')

def SeqInfoInsert(self, seqName, seqNum, seqStartTime, seqEndTime, streamTime, inputDat, calibParamDir, serverSeqDir, outputDat):
  seqXml = ET.Element('Seq', project_name=self.projectName, build_num=self.buildNum, build_name=os.path.basename(self.binaryImageDir), seq_name=seqName, seq_num=seqNum)
  
  infoListXml = ET.SubElement(seqXml, 'InfoList')
  ET.SubElement(infoListXml, 'Info', index='0', key='Seq. start at', value=TimeStamp(seqStartTime))
  ET.SubElement(infoListXml, 'Info', index='1', key='Seq. end at', value=TimeStamp(seqEndTime))
  ET.SubElement(infoListXml, 'Info', index='2', key='Seq. running time', value=PrintTime(int(seqEndTime)-int(seqStartTime))) 
  ET.SubElement(infoListXml, 'Info', index='3', key='Input stream time', value=PrintTime(streamTime))  
  ET.SubElement(infoListXml, 'Info', index='4', key='Workstation', value=self.workstation)
  ET.SubElement(infoListXml, 'Info', index='5', key='SW version', value=os.path.basename(self.binaryImageDir))
  ET.SubElement(infoListXml, 'Info', index='6', key='Calibration info', value=os.path.basename(calibParamDir))
  
  ET.SubElement(seqXml, 'Video', path=os.path.join(serverSeqDir, os.path.basename(os.path.splitext(outputDat)[0] + '.avi')).replace('\\', '/'))
  
  file = open(os.path.splitext(inputDat)[0] + '.txt', 'r')
  inputDatList = file.read().splitlines()
  file.close()
  
  inputDatListXml = ET.SubElement(seqXml, 'InputDATList')
  for i in range(0, len(inputDatList)):
   ET.SubElement(inputDatListXml, 'InputDAT', index=str(i), path=os.path.join(serverSeqDir, inputDatList[i]).replace('\\', '/'))
  
  seqXmlTree = ET.ElementTree(seqXml)
  
  seqXmlFile = os.path.join(serverSeqDir, os.path.basename(serverSeqDir) + '.xml').replace('\\', '/')
  seqXmlTree.write(seqXmlFile)
  
  execute('SequenceInserter "' + seqXmlFile + '"')
  
def RunSeq(self, seqName, seqNum, inputDat, calibParamDir):
    seqStartTime = time.time()
    
    seqDir = os.path.join(self.buildDir, seqName + '_' + seqNum).replace('\\', '/')
    serverSeqDir = os.path.join(self.serverBuildDir, os.path.basename(seqDir)).replace('\\', '/')
  
    outputDat = os.path.join(seqDir, os.path.splitext(os.path.basename(inputDat))[0] + '_output.dat').replace('\\', '/')
    
    for i in range(0, 5):
        for j in range(0, 5):
            HilS.Boot(self.relaySwitchIP)
            ret = HilS.BootWait(self.LGBoxIP)
            if ret == 0:
                break
        if ret != 0:
            print('[TestAutomation] HilS not boot.')
            exit(1)
                
        ret = execute('ADTF.py "' + self.adtfConfigXml + '" "' + inputDat + '" "' + outputDat + '" "' + calibParamDir + '"')
        if ret == 0:
            break
    if ret != 0:
        print('[TestAutomation] ADTF Error.')
        exit(1)
        
    HilS.TurnOff(self.relaySwitchIP)
    execute('DatExport.py "' + outputDat + '" "' + seqDir + '" "' + self.dbcFile + '"')
    execute('Filters.py "' + self.filterDir + '" "' + self.filter + '" "' + os.path.splitext(outputDat)[0] + '.mat" "' + self.operator + '" "' + os.path.basename(self.binaryImageDir) + '"')
    execute('HTMLCreate.py "' + outputDat + '"')   
    execute('xcopy "' + seqDir + '" "' + serverSeqDir + '/" /f/e/y')
    execute('EventInsert.py "' + self.projectName + '" "' + self.buildNum + '" "' + os.path.basename(self.binaryImageDir) + '" "' + seqName + '" "' + seqNum + '" "' + seqDir + '" "' + serverSeqDir + '"')
    
    config = ConfigParser.ConfigParser()
    config.read(os.path.splitext(outputDat)[0] + '.cfg')
    streamTime = int(config.get('StreamInfo', 'TIME'))/1000000  
    self.streamTimeTotal = self.streamTimeTotal + streamTime
    
    seqEndTime = time.time()  
    self.SeqInfoInsert(seqName, seqNum, seqStartTime, seqEndTime, streamTime, inputDat, calibParamDir, serverSeqDir, outputDat)

def Run(self):
    self.GetInputDir()
    self.SetOutputDir()
    
    self.seqTotal = 0
    self.streamTimeTotal = 0
    for i in range(0, len(self.inputSubDirList)):
        seqName = self.inputSubDirList[i]
    
        self.inputSubDirList[i] = os.path.join(self.inputDir, self.inputSubDirList[i]).replace('\\', '/')
        inputSeqList = self.GetInputSeqList(self.inputSubDirList[i])
    
        if len(inputSeqList) <= 0:
            continue
    
        calibParamDir = userGlob(self.inputSubDirList[i], 'CalibParam*')[0].replace('\\', '/')
        if not os.path.exists(calibParamDir):
            continue
    
        for j in range(0, 5):
            HilS.Boot(self.relaySwitchIP)
            ret = HilS.BootWait(self.LGBoxIP)
            if ret == 0:
                break
            
        if ret != 0:
            print('[TestAutomation] HilS not boot.')
            exit(1)
        
        if i == 0:
            HilS.ImageWrite(self.LGBoxIP, self.binaryImageDir)
        HilS.CalibParamWrite(self.LGBoxIP, calibParamDir)
    
        for j in range(0, len(inputSeqList)):
            self.RunSeq(seqName, str(j+1), os.path.join(self.inputSubDirList[i], inputSeqList[j]).replace('\\', '/'), calibParamDir)
            self.seqTotal = self.seqTotal + 1
        
    HilS.TurnOff(self.relaySwitchIP)
    
    shutil.rmtree(self.inputDir)
    shutil.rmtree(self.buildDir)
    
    self.buildEndTime = time.time()  
    self.BuildInfoInsert()

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print('[TestAutomation] Invalid arguments.')
        exit(1)
    else:
        TestAutomation(sys.argv[1], sys.argv[2], sys.argv[3]).Run() 

