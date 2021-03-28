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
class EventInsert:
 def __init__(self, projectName, buildNum, buildName, seqName, seqNum, seqDir, serverSeqDir):
  self.projectName = projectName
  self.buildNum = buildNum
  self.buildName = buildName
  self.seqName = seqName
  self.seqNum = seqNum  
  self.seqDir = seqDir
  self.serverSeqDir = serverSeqDir
 
 def Run(self):
  xmlList = userGlob(self.seqDir, '*.xml')
  for xmlFile in xmlList: 
   xmlFile = xmlFile.replace('\\', '/')
   htmlFile = os.path.join(self.serverSeqDir, os.path.splitext(os.path.basename(xmlFile))[0] + '.html').replace('\\', '/')
   execute('EventInserter "' + self.seqNum + '" "' + self.seqName + '" "' + self.projectName + '" "' + self.buildNum + '" "' + self.buildName + '" "' + xmlFile + '" "' + htmlFile + '"')
if __name__ == '__main__':
 if len(sys.argv) != 8:
  print('[EventInsert] Invalid arguments.')
  exit(1)
 else:
  EventInsert(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7]).Run()
  
