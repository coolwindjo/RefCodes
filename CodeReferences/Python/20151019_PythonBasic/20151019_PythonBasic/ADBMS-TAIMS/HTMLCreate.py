import os
import sys
import glob
def execute(cmd):
 print cmd
 sys.stdout.flush()
 return os.system(cmd)
def userGlob(dir, pattern):
 list = glob.glob1(dir, pattern)
 
 for i in range(0, len(list)):
  list[i] = os.path.join(dir, list[i])
  
 return list
class HTMLCreate:
 def __init__(self, datFile):
  self.dir = os.path.dirname(datFile).replace('\\', '/')
  
  self.gpsFile = os.path.splitext(datFile)[0] + '.txt'
  if not os.path.exists(self.gpsFile):
   print('[HTMLCreate] GPS file not exist.')
   exit(1)
  
  self.videoFile = os.path.splitext(datFile)[0] + '.avi'
  if not os.path.exists(self.videoFile):
   print('[HTMLCreate] Video file not exist.')
   exit(1)
  
  self.imageListFile = os.path.join(self.dir, 'IMAGE/IMAGE_LIST.txt').replace('\\', '/')
  if not os.path.exists(self.imageListFile):
   print('[HTMLCreate] Image list file not exist.')
   exit(1)
 
 def Run(self):
  xmlList = userGlob(self.dir, '*.xml')
  for xmlFile in xmlList: 
   xmlFile = xmlFile.replace('\\', '/')
   execute('HTMLCreater "' + xmlFile + '" "' + os.path.splitext(xmlFile)[0] + '.html" "' + self.gpsFile + '" "' + self.videoFile + '" "' + self.imageListFile + '"')
 
if __name__ == '__main__':
 if len(sys.argv) != 2:
  print('[HTMLCreate] Invalid arguments.')
  exit(1)
 else:
  HTMLCreate(sys.argv[1]).Run()

