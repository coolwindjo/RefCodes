# -*- coding: utf-8 -*-
##  @package ConvertingBetweenCelsiusAndFahrenheit

##  Documentation for GetTemperature()
#
#   More details.
def try_input(strOutput):
    
    import sys
    for i in range(1,10):
        try:
            inputString = input(strOutput)
            break
        except  :
            print("[Error] Unexpected error", sys.exc_info()[0])
            continue

    return inputString

def GetTemperature():
    
    temperature = try_input("Input temperature value followed by its unit: ")

    return temperature


##  Documentation for ParseTempAndUnit()
#
#   More details.
"""
def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    reverse = dict((value, key) for key, value in enums.iteritems())
    enums['reverse_mapping'] = reverse
    return type('Enum', (), enums)
"""
import enum
class TempUnit(enum.Enum):
    notAnUnit = 0
    celsius = 1
    fahrenheit = 2

def ParseTempAndUnit(strTemperature):
    
    import sys
    unitPos = strTemperature.rfind("C")
    if unitPos == -1:
        unitPos = strTemperature.rfind("F")
    if unitPos == -1:
        eUnit = TempUnit.notAnUnit
        nTemp = 0
    else:
        try:
            nTemp = float(strTemperature[:unitPos])
        except  ValueError:
            print("[Error] Could not convert data to floating point.")
        except  NameError:
            print("[Error] The input is not proper value.")
        except  :
            print("[Error] Unexpecetd error.", sys.exc_info()[0])
        if strTemperature[unitPos] == "C":
            eUnit = TempUnit.celsius
        elif strTemperature[unitPos] == "F":
            eUnit = TempUnit.fahrenheit

    return nTemp, eUnit


##  Documentation for PrintConvertedTemp()
#
#   More details.
def PrintConvertedTemp(nTemp, eUnit):
    
    if eUnit == TempUnit.celsius:
        givenUnit = "C"
        convertedTemp = float(nTemp) * 1.8 + 32
        convertedUnit = "F"
    elif eUnit == TempUnit.fahrenheit:
        givenUnit = "F"
        convertedTemp = (float(nTemp) - 32) / 1.8
        convertedUnit = "C"
    print("Converted result: " + str(nTemp) + givenUnit + " -> " 
            + "{:.2f}%s".format(convertedTemp) % convertedUnit)

    return


##  Documentation for the main function.
#
#   More details.
def main():
    
    for i in range(1,10):
        strTemperature = GetTemperature()
        nTemp, eUnit = ParseTempAndUnit(strTemperature)
        if eUnit == TempUnit.notAnUnit:
            break
        else:
            PrintConvertedTemp(nTemp, eUnit)
            continue
    print("Finish the operation.")

    return

if __name__ == "__main__":
    main()
