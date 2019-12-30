# -*- coding: utf-8 -*-
import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

class ProbSolve():

    def __init__(self, *data_frames):
        self.df_list = data_frames
        for df in self.df_list:
            print(df)
        return
    
    def cal_cov_x_var(self, df):
        X = df.loc[:,'x']
        Y = df.loc[:,'y']
        XY = X * Y
        XX = X * X
        Xvar = XX.mean()-X.mean()*X.mean()
        print(XY)
        print("E(XY) = ", XY.mean())
        print("E(X) = ", X.mean())
        print("E(Y) = ", Y.mean())
        print("E(X)*E(Y) = ", X.mean()*Y.mean())
        print("E(X**2)-E(X)**2 = ", Xvar)
        print("V(X) = ", X.var())
        cov = XY.mean() - X.mean()*Y.mean()
        print("Cov(X,Y) = ", cov)
        # Xvar = X.var()
        return cov, Xvar

    def cal_slope(self, cov, Xvar):
        slope = cov/Xvar
        return slope

    def cal_regression(self):
        for df in self.df_list:
            cov, Xvar = self.cal_cov_x_var(df)
            slope = self.cal_slope(cov, Xvar)
            print("Slope = ", slope)
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

    data = {'x' : [13,19, 16, 14, 15, 14],
                'y' : [40, 83, 62, 48, 58, 43] }

    data = pd.DataFrame(data)
    ps = ProbSolve(data)
    ps.cal_regression()
    return

if __name__ == '__main__':
    main()