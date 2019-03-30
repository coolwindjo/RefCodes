'''
Created on 2014. 8. 28.
@author: adas
'''
import os
import sys
def execute(cmd):
 print cmd
 sys.stdout.flush()
 return os.system(cmd)
class DatExport:
 def __init__(self, sourceDat = 'C:/DB/output/output.dat', outputDir = 'C:/DB/output', dbcFile = 'C:/git/CV_ADAS/build/images/config/LGADAS_CAN.dbc'):
  self.sourceDat = sourceDat
  if not os.path.exists(self.sourceDat):
   print('[DatExport] Source DAT file not exist.')
   exit(1)
  
  self.outputDir =  outputDir
  if not os.path.exists(self.outputDir):
   print('[DatExport] Output directory not exist.')
   exit(1)
  
  self.dbcFile = dbcFile
  if not os.path.exists(self.dbcFile):
   print('[DatExport] DBC file not exist.')
   exit(1)
 
 def Export(self):
  execute('adtf_datexporter -export CAN -output "' + self.ascFile + '" "' + self.sourceDat + '"')
  execute('cantomat -f mn -d "' + self.dbcFile+ '" -a "' + self.ascFile+ '" -m "' + self.matFile + '"')
  
  execute('ImageExporter "' + self.sourceDat + '" "' + self.imageDir + '"')
  execute('GPSExporter -interval 1000 "' + self.sourceDat + '" "' + self.gpsFile + '"')
  execute('VideoExporter "' + self.sourceDat + '" "' + self.videoFile + '"')
  execute('StreamInfoExporter "' + self.sourceDat + '" "' + self.cfgFile + '"')
  
 def Run(self):
  self.ascFile = os.path.join(self.outputDir, os.path.splitext(os.path.basename(self.sourceDat))[0]+'.asc').replace('\\', '/')
  self.matFile = os.path.join(self.outputDir, os.path.splitext(os.path.basename(self.sourceDat))[0]+'.mat').replace('\\', '/')
  
  self.imageDir = os.path.join(self.outputDir, 'IMAGE').replace('\\', '/')
  if not os.path.exists(self.imageDir):
   os.mkdir(self.imageDir)
  
  self.gpsFile = os.path.join(self.outputDir, os.path.splitext(os.path.basename(self.sourceDat))[0]+'.txt')
  self.videoFile = os.path.join(self.outputDir, os.path.splitext(os.path.basename(self.sourceDat))[0]+'.avi')
  self.cfgFile = os.path.join(self.outputDir, os.path.splitext(os.path.basename(self.sourceDat))[0]+'.cfg')
  
  self.Export()
if __name__ == '__main__':
 if len(sys.argv) != 4:
  print('[DatExport] Invalid arguments.')
  exit(1)
 else:
  DatExport(sys.argv[1], sys.argv[2], sys.argv[3]).Run() 

