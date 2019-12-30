import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets,svm
# from sklearn.metrics import confusion_matrix

iris = datasets.load_iris()

X = iris.data[:, :2]
y = iris.target
'''
clf = svm.SVC(kernel='linear', C = 1)
clf.fit(X,y)

y_pred = clf.predict(X)
print('con_mat : \n', confusion_matrix(y,y_pred))
'''
def make_meshgrid(x,y, h=0.02):
    x_min, x_max = x.min()-1, x.max()+1
    y_min, y_max = y.min()-1, y.max()+1
    xx,yy = np.meshgrid(np.arange(x_min,x_max,h), np.arange(y_min,y_max,h))
    return xx,yy

def plot_contours(ax, clf, xx, yy, **params):
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()]).reshape(xx.shape)
    out = ax.contourf(xx,yy,Z, **params)
    return out

models = (svm.SVC(kernel='linear', C=1),
          svm.LinearSVC(C=1, max_iter=10000),
          svm.SVC(kernel='rbf',gamma=0.7, C=1, max_iter=10000),
          svm.SVC(kernel='poly', degree=3, C=1, gamma='auto'))

models = (clf.fit(X,y) for clf in models)
titles = ['SVC with Linear kernel',
          'LinearSVC (Linear Kernel)',
          'SVC with RBF Kernel',
          'SVC with polynomial (3degree) kernel']

fig, sub = plt.subplots(2,2)
plt.subplots_adjust(wspace=0.5, hspace=0.5)
x0, x1 = X[:,0], X[:,1]
xx, yy = make_meshgrid(x0,x1)

for clf, titles, ax in zip(models, titles, sub.flatten()):
    plot_contours(ax, clf, xx, yy, cmap=plt.cm.coolwarm,alpha=0.8)
    ax.scatter(x0,x1, c=y, cmap = plt.cm.coolwarm, s=20,edgecolors='k')
    ax.set_xlim(xx.min(), xx.max())
    ax.set_ylim(yy.min(), yy.max())
    ax.set_xlabel('sepal length')
    ax.set_ylabel('sepal width')
    ax.set_xticks(())
    ax.set_yticks(())
    ax.set_title(titles)

plt.show()