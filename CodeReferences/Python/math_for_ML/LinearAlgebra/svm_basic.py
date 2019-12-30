import numpy as np
from sklearn import datasets,svm
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

iris = datasets.load_iris()

X = iris.data[:, :2]
# X =Li iris.data[:, 2:]
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state = 0)

sc = StandardScaler()
sc.fit(X_train)
X_train_std = sc.transform(X_train)
X_test_std = sc.transform(X_test)

#svm = svm.SVC(kernel='linear', C=1.0)#, random_state=0)
svm = svm.LinearSVC(C=1, max_iter=10000, loss='hinge')
svm.fit(X_train_std, y_train)
y_pred = svm.predict(X_test_std)



print("MisClassified Examples : %d" % (y_test != y_pred).sum())

from sklearn.metrics import accuracy_score
print("Accuracy : %.4f" %accuracy_score(y_test, y_pred))
