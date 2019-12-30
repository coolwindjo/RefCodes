import os
import sys
def execute(cmd):
 print cmd
 sys.stdout.flush()
 return os.system(cmd)
 
class Filters:
 def __init__(self, filterDir, filter, matFile, operator, swVersion):
  self.filterDir = filterDir.replace('\\', '/')
  if not os.path.exists(self.filterDir):
   print('[Filters] Filter directory not exist.')
   exit(1)
  
  self.filterList = filter.split(',')
  
  if not os.path.exists(matFile):
   print('[Filters] MAT file not exist.')
   exit(1)
  
  self.dir = os.path.dirname(matFile).replace('\\', '/')
  self.matFile =  os.path.basename(matFile)
  self.operator = operator
  self.swVersion = swVersion
 
 def Run(self):
  for filter in self.filterList:
   filterCmd = self.filterDir + '/' + filter + '.exe'
   if not os.path.exists(filterCmd):
    print('[Filter] ' + filterCmd + ' not exist.')
    continue
   
   execute(filterCmd + ' "' + self.dir + '" "' + self.matFile + '" "' + self.operator + '" "' + self.swVersion + '"')
if __name__ == '__main__':
 if len(sys.argv) != 6:
  print('[Filters] Invalid arguments.')
  exit(1)
 else:
  Filters(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5]).Run()

