from sklearn.cluster import KMeans
from sklearn.datasets import make_blobs # make_blobs : 클러스터링 모델 시험시 원하는 특성을 가진 데이터 만들기 위해 사용함

import numpy as np
import matplotlib.pyplot as plt

np.random.seed(0)

centers = [[1,1],[0,0],[2,-1]]
n_clusters = len(centers)

data, labels_true = make_blobs(n_samples = 2000, centers=centers, cluster_std = 0.7)

print(data)

print(labels_true)

print(np.unique(labels_true)) # 생성된 데이터들이 0,1,2 클러스터에 속하는 것을 확인할 수 있음

plt.figure(figsize=(10,5))

plt.scatter(data[:,0], data[:,1])

estimator = KMeans(init='k-means++', n_clusters=3, n_init=10)
estimator.fit(data)

labels_pred = estimator.labels_
labels_pred


cm = plt.cm.get_cmap('jet')
scaled_labels = labels_pred - np.min(labels_pred)
scaled_labels = scaled_labels/(np.max(labels_pred) - np.min(labels_pred))
np.unique(scaled_labels)

plt.figure(figsize=(10,5))

plt.scatter(data[:,0], data[:,1], c=cm(scaled_labels))

plt.show()