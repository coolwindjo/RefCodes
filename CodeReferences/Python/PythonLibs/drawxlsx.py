# -*- coding: utf-8 -*-
##  @package DrawXlsx
#   Documentation for this module
#
#   More details
import xlsxwriter
import sys
    
class DrawXlsx(object):
    """A class for drawing on excel file"""

    def __init__(self, *args, **kwargs):
        return super(DrawXlsx, self).__init__(*args, **kwargs)

    def get_work_sheet_count(self):
        return self._nWorkSheetCount

    def get_chart_count(self):
        return self._nChartCount

    def make_xlsx_filename_with_date(self, strFileName, date=""):

        import time
        
        if date == "":
            strXlsxFile = time.strftime("%Y%m%d_")
        else:
            strXlsxFile = time.strftime("%Y%m") + date + "_"
        strXlsxFile += strFileName
        strXlsxFile += ".xlsx"
        
        return strXlsxFile

    def make_absolute_cell_coordinate(self, strCell):

        import re
        nRowNum = int(re.findall('\d+', strCell)[0])
        strColLetter = re.findall('[a-zA-Z]+', strCell)[0]
        strAbsoluteCell = "$" + strColLetter + "$" + str(nRowNum)

        return strAbsoluteCell

    def open_workbook(self, strXlsxFileName):
        
        try:
            self._workbook = xlsxwriter.Workbook(strXlsxFileName)
            self._arWorksheet = []
            self._nWorkSheetCount = 0
            self._arChart = []
            self._nChartCount = 0
        except :
            print("[Error] Unexpected error at open_workbook().", sys.exc_info()[0])

        return 

    def close_workbook(self):
        
        try:
            self._workbook.close()
        except :
            print("[Error] Unexpected error at close_workbook().", sys.exc_info()[0])

        return 

    def add_worksheet(self):
        
        self._nWorkSheetCount += 1
        self._arWorksheet.append(self._workbook.add_worksheet())

        return

    def write(self, nSheetId, strCell, strValue):
        
        try:
            bold = self._workbook.add_format({'bold': 1})
            self._arWorksheet[nSheetId].write(strCell, strValue, bold)
        except :
            print("[Error] Unexpected error at write().", sys.exc_info()[0])

        return        

    def write_row(self, nSheetId, strStartingCell, listHeading):
        
        try:
            bold = self._workbook.add_format({'bold': 1})
            self._arWorksheet[nSheetId].write_row(strStartingCell, listHeading, bold)
        except :
            print("[Error] Unexpected error at write_row().", sys.exc_info()[0])

        return        
    
    def write_col(self, nSheetId, strStartingCell, listData):
        
        try:
            self._arWorksheet[nSheetId].write_column(strStartingCell, listData)
        except :
            print("[Error] Unexpected error at write_col().", sys.exc_info()[0])

        return

    def open_chart(self, strType, strTitle):
        
        try:
            self._nChartCount += 1
            self._arChart.append(self._workbook.add_chart({'type' : strType}))
            self._arChart[self._nChartCount-1].set_title({'name' : strTitle})
            self._arChart[self._nChartCount-1].set_style(10)
        except:
            print("[Error] Unexpected error at open_chart().", sys.exc_info()[0])

        return

    def close_and_insert_chart(self, strUpperLeftCell):
        
        try:
            worksheet = self._arWorksheet[self._nWorkSheetCount-1]
            chart = self._arChart[self._nChartCount-1]
            worksheet.insert_chart(strUpperLeftCell, chart, {'x_offset' : 25, 'y_offset' : 10})
        except:
            print("[Error] Unexpected error at close_and_insert_chart().", sys.exc_info()[0])

        return

    def add_base_data_to_chart(self, strStartingCell, strBaseXName, strBaseYName, listData, nChartId=-1, nSheetId=-1):
        
        if nChartId == -1:
            nChartId = self._nChartCount-1
        if nSheetId == -1:
            nSheetId= self._nWorkSheetCount-1
        strSheet = "Sheet" + str(nSheetId+1) + "!"
        self._arChart[nChartId].set_y_axis({
           'name'  : '=' + strSheet + self.make_absolute_cell_coordinate(strStartingCell),
            #'min' : min(listData), 
            #'max' : max(listData),
        })
        self.add_data_to_chart(strStartingCell, strBaseXName, listData, nChartId, nSheetId, 1)

        return

    def add_data_to_chart(self, strStartingCell, strDataName, listData, nChartId=-1, nSheetId=-1, isBase=0):

        MaxValueNumForTrendLine = 30
        import re
        if nChartId == -1:
            nChartId = self._nChartCount-1
        if nSheetId == -1:
            nSheetId= self._nWorkSheetCount-1
        try:
            self.write(nSheetId, strStartingCell, strDataName)
            nStartingRowNum = int(re.findall('\d+', strStartingCell)[0]) + 1
            strStartingCellColLetter = re.findall('[a-zA-Z]+', strStartingCell)[0]
            strBeginingCell = strStartingCellColLetter + str(nStartingRowNum)
            self.write_col(nSheetId, strBeginingCell, listData)
            nFinishingCellRowNum = nStartingRowNum - 1 + len(listData)
            
            strSheet = "Sheet" + str(nSheetId+1) + "!"
            if isBase == 0:
                # Given data is a y value.
                strAxisRangeBegin = "$" + strStartingCellColLetter + "$" + str(nStartingRowNum)
                strAxisRangeEnd = "$" + strStartingCellColLetter + "$" + str(nFinishingCellRowNum)
                strXRange = self._strBaseAxisRangeBegin + ":" + self._strBaseAxisRangeEnd
                strYRange = strAxisRangeBegin + ":" + strAxisRangeEnd 
                dicSeriseSettings = {
                    'name'          : '=' + strSheet + self.make_absolute_cell_coordinate(strStartingCell),
                    'categories'    : '=' + strSheet + strXRange,
                    'values'        : '=' + strSheet + strYRange,
                }
                if len(listData) < MaxValueNumForTrendLine:
                    strFormula = [0,0,0,0]
                    strFormula[0] = str('=INDEX(LINEST(' + strYRange + ',' + strXRange + '^{1,2}),1)')
                    strFormula[1] = str('=INDEX(LINEST(' + strYRange + ',' + strXRange + '^{1,2}),1,2)')
                    strFormula[2] = str('=INDEX(LINEST(' + strYRange + ',' + strXRange + '^{1,2}),1,3)')
                    strFormula[3] = '=-'+ strStartingCellColLetter + str(nFinishingCellRowNum + 3) + '/(2*' + strStartingCellColLetter + str(nFinishingCellRowNum + 2) + ')'
                    self.write_col(nSheetId, strStartingCellColLetter + str(nFinishingCellRowNum + 2), strFormula)
                    dicSeriseSettings['trendline'] = {  
                        'type'  :'polynomial',
                        'order' : 2,
                        'display_equation'  : True,
                    }
                else:
                    pass
                self._arChart[nChartId].add_series(dicSeriseSettings)
            else:
                # Given data is the base data.
                self._strBaseAxisRangeBegin = "$" + strStartingCellColLetter + "$" + str(nStartingRowNum)
                self._strBaseAxisRangeEnd = "$" + strStartingCellColLetter + "$" + str(nFinishingCellRowNum)
                dicXSettings = {
                    'name'      : '=' + strSheet + self.make_absolute_cell_coordinate(strStartingCell),
                    'min'       : min(listData), 
                    'max'       : max(listData),
                }
                if len(listData) < MaxValueNumForTrendLine:
                    strTrendLineCoeffs = ['a','b','c', '-b/(2a)']
                    self.write_col(nSheetId, strStartingCellColLetter + str(nFinishingCellRowNum + 2), strTrendLineCoeffs)
                    dicXSettings['major_unit'] = 1
                else:
                    pass
                self._arChart[nChartId].set_x_axis(dicXSettings)
        except:
            print("[Error] Unexpected error at add_data_to_chart().", sys.exc_info()[0])
            print("len(listData) = " + str(len(listData)))
        
        return

def main():
    
    dx = DrawXlsx()
    strXlsxFile = dx.make_xlsx_filename_with_date("VehicleSignalComparison_slalom1")

    dx.open_workbook(strXlsxFile)
    dx.add_worksheet()

    headings = ['Number', 'Batch 1', 'Batch 2']
    data = [
        [2, 3, 4, 5, 6, 7],
        [10, 40, 50, 20, 10, 50],
        [30, 60, 70, 50, 40, 30],
    ]

    dx.open_chart('line', 'Result of sample analysis') 
               
    dx.add_base_data_to_chart('A1', 'Test Number', 'Sample length (mm)', data[0])
    dx.add_data_to_chart('B1', 'Batch 1', data[1])
    dx.add_data_to_chart('C1', 'Batch 2', data[2])

    dx.close_and_insert_chart("D2")

    dx.add_worksheet()

    dx.open_chart('line', 'Result of sample analysis') 
               
    dx.add_base_data_to_chart('A1', 'Test Number', 'Sample length (mm)', data[0])
    dx.add_data_to_chart('B1', 'Batch 1', data[1])
    dx.add_data_to_chart('C1', 'Batch 2', data[2])

    dx.close_and_insert_chart("D2")

    dx.close_workbook()

    return

if __name__ == "__main__":
    main()
        