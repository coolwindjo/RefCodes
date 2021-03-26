# -*- coding: utf-8 -*-
#@package deconvolution simulation
from __future__ import print_function
import sys
import inspect
import xlwings as xw
import numpy as np
import pandas as pd

class ConvSim(object):
    """"A class for simulate convolutions"""

    def __init__(self, *args, **kwargs):
        return super(ConvSim, self).__init__(*args, **kwargs)

    def set_wb(self, wb):
        self.wb = wb
        self.ws_r = wb.sheets["UserDefined"]

    def set_vars(self):
        self.output = self.ws_r["B1"].value
        self.input_x = int(self.ws_r["B3"].value)
        self.input_y = int(self.ws_r["B4"].value)
        self.input_x_re = int(self.ws_r["D3"].value)
        self.input_y_re = int(self.ws_r["D4"].value)
        self.kernel_x = int(self.ws_r["C3"].value)
        self.kernel_y = int(self.ws_r["C4"].value)
        self.output_x = int(self.ws_r["D3"].value)
        self.output_y = int(self.ws_r["D4"].value)
        self.pad_t = int(self.ws_r["B6"].value)
        self.pad_b = int(self.ws_r["B7"].value)
        self.pad_l = int(self.ws_r["B8"].value)
        self.pad_r = int(self.ws_r["B9"].value)
        self.k_pad_t = int(self.ws_r["C6"].value)
        self.k_pad_b = int(self.ws_r["C7"].value)
        self.k_pad_l = int(self.ws_r["C8"].value)
        self.k_pad_r = int(self.ws_r["C9"].value)

    def make_matrix(self, w, h, v):
        df = pd.DataFrame()
        for row in range(h):
            for col in range(w):
                df.at[row, col] = v
        return df

    def sheet_out(self, title, df):
        w = len(df.columns)
        h = len(df)
        ws = self.wb.sheets.add(title + " " + str(w)+"x"+str(h))
        ws.range("A:AAA").api.ColumnWidth = 2
        ws["A1"].value = title + str(w) + "x" + str(h)
        ws["B2"].value = df
        return ws

    def make_input(self):
        # df = pd.DataFrame([[1,2],[3,4]], columns=['one', 'two'])
        # df = pd.DataFrame({'row':range(self.input_y), 'col':range(self.input_x))
        df = self.make_matrix(self.input_x, self.input_y, 1)
        return df

    def make_kernel(self):
        df = self.make_matrix(self.kernel_x, self.kernel_y, 1)
        return df

    def add_padding(self, prev_df, pad_t, pad_b, pad_l, pad_r):
        try:
            w = len(prev_df.columns)
            h = len(prev_df)
            padded_w = pad_l + w + pad_r
            padded_h = pad_t + h + pad_b
            df = pd.DataFrame()
            for row in range(padded_h):
                for col in range(padded_w):
                    if row < (pad_t + h) and row >= pad_t :
                        if col < (pad_l + h) and col >= pad_l :
                            df.at[row, col] = prev_df.at[row-pad_t, col-pad_l]
                        else:
                            df.at[row, col] = 0
                    else:
                        df.at[row, col] = 0
        except:
            self.ws_r[self.output].value = ("[Error] Unexpected error at " + inspect.currentframe().f_code.co_name + "()", sys.exc_info()[0])
        return df

    def add_repeat(self, prev_df, x_re, y_re):
        try:
            w = len(prev_df.columns)
            h = len(prev_df)
            w_re = 2*w
            h_re = 2*h
            df = pd.DataFrame()
            for row in range(h_re):
                for col in range(w_re):
                    if (row % 2 == 1) or (col % 2 == 1):
                        df.at[row, col] = 0
                    else:
                        df.at[row, col] = prev_df.at[int(row/2), int(col/2)]
        except:
            self.ws_r[self.output].value = ("[Error] Unexpected error at " + inspect.currentframe().f_code.co_name + "()", sys.exc_info()[0])
        return df

    def convolution(self):#, df, df_k):
        try:
            df = self.make_matrix(6, 6, 1)
            df_k = self.make_matrix(self.kernel_x, self.kernel_y, 1)
            df_conv = pd.DataFrame()
            w = len(df.columns)
            h = len(df)
            k_w = len(df_k.columns)
            k_h = len(df_k)
            # for row in range(w):
            #     for col in range(h):

        except:
            self.ws_r[self.output].value = ("[Error] Unexpected error at " + inspect.currentframe().f_code.co_name + "()", sys.exc_info()[0])
        return df_conv

def main():
    try:
        cs = ConvSim()
        cs.set_wb(xw.Book.caller())
        cs.set_vars()
        cs.convolution()
        '''
        df_k = cs.make_kernel()
        cs.sheet_out("Kernel Imge", df_k)
        df_k_padded = cs.add_padding(df_k,
        cs.k_pad_t,
        cs.k_pad_b,
        cs.k_pad_l,
        cs.k_pad_r)
        cs.sheet_out("Padded Kernel Image", df_k_padded)
        df = cs.make_input()
        cs.sheet_out("Input Image", df)
        df_repeated = cs.add_repeat(df, cs.input_x_re, cs.input_y_re)
        cs.sheet_out("Repeated Image", df_repeated)
        df_padded = cs.add_padding(df_repeated,
        cs.pad_t,
        cs.pad_b,
        cs.pad_l,
        cs.pad_r)
        '''
        cs.sheet_out("Padded Image", df_padded)

    except:
        cs.ws_r[cs.output].value = ("[Error] Unexpected error at " + inspect.currentframe().f_code.co_name + "()", sys.exc_info()[0])
    return


@xw.func
def hi(name):
    return f"hi {name}!"

@xw.func
def hello(name):
    return f"Hello {name}!"


if __name__ == "__main__":
    xw.Book("deconv.xlsm").set_mock_caller()
    main()
