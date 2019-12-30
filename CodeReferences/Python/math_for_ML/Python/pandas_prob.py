# -*- coding: utf-8 -*-
import sys
import pandas as pd
import numpy as np

class ProbSolve():
    def __init__(self, *data_frames):
        self.df_list = data_frames
        # for df in self.df_list:
            # print(df)
        return
    
    def concat_dfs(self):
        try:
            ret = pd.concat(self.df_list)
        except :
            print("[Error] Unexpected error", sys.exc_info()[0])
        # print(ret)
        return ret
    def cal_profit(self, df):
        profit_col = df.loc[:,'Sales'] - df.loc[:,'Expenses']
        df['Profit'] = profit_col
        # print(con)
        return df
    def cal_total(self, df):
        tot_row = pd.DataFrame({
            'Sales':[df['Sales'].sum()],
            'Expenses': [df['Expenses'].sum()],
            'Profit': [df['Profit'].sum()]
            }, index=['Total'])

        ret = df.copy()
        # ret.loc['Total'] = tot_row.loc['Total']
        ret.loc['Total'] = df.sum(axis=0)
        try:
            ret = pd.concat([df, tot_row])
        except :
            print("[Error] Unexpected error", sys.exc_info()[0])
        return ret
        


def main():
    df1 = pd.DataFrame({
        'Sales' : [10000000, 12000000, 9000000, 6000000, 8000000, 1100000],
        'Expenses' : [15000000, 1300000, 1200000, 9000000, 9900000, 9500000]},
        index = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'])

    df2 = pd.DataFrame({
        'Sales' : [13000000, 14000000, 17000000, 15400000, 16500000, 16600000],
        'Expenses' : [11000000, 10400000, 11000000, 12100000, 9000000, 9500000]},
        index = ['Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'])
    ps = ProbSolve(df1, df2)
    con = ps.concat_dfs()
    added = ps.cal_profit(con)
    result = ps.cal_total(added)
    print(result)
    return

if __name__ == '__main__':
    main()