# -*- coding: utf-8 -*-
import numpy as np

ab = [3, 76]

data = [[2, 81], [4, 93], [6, 91], [8, 97]]
x = [i[0] for i in data]
y = [i[1] for i in data]

def predict(x):
    return ab[0] * x + ab[1]
    
def RMSE(p, a):
    return np.sqrt(((p-a) ** 2).mean())

def RMSE_val(pred_result, y):
    return RMSE(np.array(pred_result), np.array(y))

predict_result = []
for x_i, y_i in zip(x, y):
    predict_result.append(predict(x_i))
    print("Study time:{} Measured score:{} Predicted score:{}".format(x_i, y_i, predict(x_i)))
print("RMSE final result: " + str(RMSE_val(predict_result,y)))
