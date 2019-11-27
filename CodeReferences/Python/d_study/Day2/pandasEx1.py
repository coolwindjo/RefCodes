import numpy as np
import pandas as pd

data = np.arange(32)
rData = data.reshape(8, 4)
print("rData:\n", rData)
tData = rData.T
print("tData:\n", tData)

p = print
p("# -----------------------------------------")

arr5x4 = np.random.randn(5, 4)
print("arr5x4:\n", arr5x4)
print("\nmean:", arr5x4.mean())
print("\nsum:", arr5x4.sum())

print("\nmean(axis=0:", arr5x4.mean(axis=0))
print("\nmean(axis=1:", arr5x4.mean(axis=1))

p("# -----------------------------------------")

obj = pd.Series([4, 7, 8, 1])
print("obj:\n", obj)

obj2 = pd.Series([4, 7, 8, 1],
                 index=['a', 'b', 'c', 'd'])
print("\nobj2:\n", obj2)

print("\nobj2:[c]=", obj2['c'])
print("\nobj2[[c, a, d]]=\n", obj2[['c', 'a', 'd']])
print("\nnp.exp(obj2)\n", np.exp(obj2))
print("\n", obj2[obj2 > 5])
print("\n", obj2['a':'c'])

p("# -----------------------------------------")

np.random.seed(1234)
obj = pd.DataFrame(np.random.randn(3, 3),
                   index=list('abc'),
                   columns=list('efg'))
print("obj:\n", obj)

print("\nobj[e]\n", obj['e'])
print("\nobj[b]\n", obj.loc['b'])
print("\n", obj.loc[:, 'f':])

print("\nobj.describe():\n", obj.describe())

p("# -----------------------------------------")

obj2 = pd.DataFrame(np.random.randn(1000, 2))
print("\nobj2:\n", obj2)

print("\nobj2.head(20)\n", obj2.head(20))
print("\nobj2.tail(5)\n", obj2.tail(5))
print("\nobj2.info()", obj2.info())

p("# -----------------------------------------")

data = pd.Series([1, np.nan, 3.5, np.nan, 7])
print("\n", data, "\n")
print("\n", data.dropna(), "\n")
print("\n", data[data.notnull()], "\n")

np.random.seed(12345)
df = pd.DataFrame(np.random.randn(7, 3))
df.iloc[:4, 1] = np.nan
print("\n", df, "\n")
df.iloc[:2, 2] = np.nan
print("\n", df, "\n")

print("\n", df.fillna(0), "\n")
print("\n", df.fillna({1:0.5,2:-1}), "\n")
print("\n", df.fillna(df.mean()), "\n")