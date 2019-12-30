from sklearn.neighbors import KNeighborsClassifier
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score
import numpy as np

iris = datasets.load_iris()

# iris feature 에서 2개만 사용합니다.
X = iris.data[:, 2:]
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)
sc = StandardScaler()

sc.fit(X_train)
sc.fit(X_test)
X_train_std = sc.transform(X_train)
X_test_std = sc.transform(X_test)

knn = KNeighborsClassifier(n_neighbors=5, p=2, metric='minkowski') # p = 2 & 'minkowski' 두 옵션이 같이 쓰여야 유클리디안 거리 옵션이 적용됨
# knn = KNeighborsClassifier(n_neighbors=51, p=2, metric='minkowski') # p = 2 & 'minkowski' 두 옵션이 같이 쓰여야 유클리디안 거리 옵션이 적용됨
knn.fit(X_train_std, y_train)

y_pred = knn.predict(X_test_std)

from sklearn.metrics import accuracy_score
print('MisClassification Exampes ; %d' % (y_test != y_pred).sum())
print('Accuracy : %.2f' % accuracy_score(y_test , y_pred))