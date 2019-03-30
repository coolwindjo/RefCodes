import os
import sys
import shutil
import ConfigParser
import HilS
def execute(cmd):
 print cmd
 sys.stdout.flush()
 return os.system(cmd)
class BuildFail:
 def __init__(self, binaryImageDir, inputDir):
  # jenkins info
  self.projectName = os.getenv('JOB_NAME')
  self.buildNum = os.getenv('BUILD_NUMBER')
  self.workstation = os.getenv('NODE_NAME')
  
  self.buildName = binaryImageDir
   
  self.inputDir = os.path.join(os.getenv('WORK_INPUT_ROOT'), inputDir).replace('\\', '/')
  self.buildDir = os.path.join(os.getenv('WORK_OUTPUT_ROOT'), self.projectName + '/(' + self.buildNum + ')' + self.buildName).replace('\\', '/')
  self.serverBuildDir = os.path.join(os.getenv('SERVER_OUTPUT_ROOT'), self.projectName + '/(' + self.buildNum + ')' + self.buildName).replace('\\', '/')
  
  # IP
  config = ConfigParser.ConfigParser()
  config.read('workstation.cfg')
  self.workstationIP = config.get(self.workstation, 'IP')
  self.relaySwitchIP = config.get(self.workstation, 'RELAY_SWITCH_IP')
 
 def Run(self):
  HilS.TurnOff(self.relaySwitchIP)
  execute('BuildFailDelete "' + self.projectName + '" "' + self.buildNum + '" "' + self.buildName + '"')
  
  if os.path.exists(self.serverBuildDir):
   shutil.rmtree(self.serverBuildDir)
  
  if os.path.exists(self.inputDir):
   shutil.rmtree(self.inputDir)
  
  #if os.path.exists(self.buildDir):
  # shutil.rmtree(self.buildDir)
 
if __name__ == '__main__':
 if len(sys.argv) != 3:
  print('[BuildFail] Invalid arguments.')
  exit(1)
 else:
  BuildFail(sys.argv[1], sys.argv[2]).Run()
