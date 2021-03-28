import os
import sys

def execute(cmd):
    print(cmd)
    sys.stdout.flush()
    return os.system(cmd)

class ADTF:
 def __init__(self, adtfConfigXml='Z:/git/CV_ADAS/build/adtf/adtf_project/Stereo_VL1000/config/system.xml', inputDat='C:/DB/Rec20140827141921.dat', outputDat='C:/DB/output/output.dat', calibParamDir = 'C:/git/CV_ADAS/build/adtf/adtf_project/LG_StereoADAS/CalibParam_LG_GEN'):
  self.adtfConfigXml = adtfConfigXml
  if not os.path.exists(self.adtfConfigXml):
   print('[ADTF] ADTF config xml file not exist.')
   exit(1)
  
  self.inputDat = inputDat
  if not os.path.exists(self.inputDat):
   print('[ADTF] Input DAT file not exist.')
   exit(1)
  
  self.calibParamDir = calibParamDir
  if not os.path.exists(self.calibParamDir):
   print('[ADTF] Calibration param directory not exist.')
   exit(1)
  
  self.adtfScriptTemplate = 'pytest.template'
  if not os.path.exists(self.adtfScriptTemplate):
   print('[ADTF] ADTF script template file not exist.')
   exit(1)
  
  self.outputDat = outputDat
  if os.path.exists(self.outputDat):
   os.remove(self.outputDat)
 
 def GenerateADTFScript(self):
  self.adtfScript = os.path.join(os.path.dirname(self.inputDat), os.path.splitext(self.adtfScriptTemplate)[0]+'.py').replace('\\', '/')
  self.fpTemplate = open(self.adtfScriptTemplate, 'r')
  strTemplate = self.fpTemplate.read()
  self.fpTemplate.close()
  
  strTemplate = strTemplate.replace('TEMPLATE_CONFIGURATION_XML', '"'+self.adtfConfigXml+'"')
  strTemplate = strTemplate.replace('TEMPLATE_INPUTDAT', '"'+self.inputDat+'"')
  strTemplate = strTemplate.replace('TEMPLATE_OUTPUTDAT','"'+self.outputDat+'"')
  strTemplate = strTemplate.replace('TEMPLATE_CALIBRATION_PARAM', '"'+self.calibParamDir+'"')
            
  print strTemplate
  self.fpScript = open(self.adtfScript, 'w')
  self.fpScript.write(strTemplate)
  self.fpScript.close()
 
 def Run(self):
  self.GenerateADTFScript()
  execute('adtf_runtime -playlist="' +self.adtfScript +'" -quit')
  
  if not os.path.exists(self.outputDat):
   print('[ADTF] ADTF not run.')
   exit(1)
if __name__ == '__main__':
    if len(sys.argv) != 5:
        print('[ADTF] Invalid arguments.')
        exit(1)
    else:
        ADTF(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]).Run()

