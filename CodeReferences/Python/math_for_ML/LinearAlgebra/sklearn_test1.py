from sklearn import datasets
import pandas as pd

iris = datasets.load_iris()
print(iris.data.shape)
print(iris.feature_names)
df = pd.DataFrame(iris.data)
print(df.head())

X = iris.data[:,:2]
y = iris.target

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.3)

from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
sc.fit(X_train)
X_train_std = sc.transform(X_train)
X_test_std = sc.transform(X_test)

from sklearn.svm import SVC
svm = SVC(kernel='linear', C=1.0)
svm.fit(X_train_std, y_train)

y_pred = svm.predict(X_test_std)

print("MisClassified Examples : %d" % (y_test != y_pred).sum())

from sklearn.metrics import accuracy_score
print("Accuracy : %.4f" %accuracy_score(y_test, y_pred))
