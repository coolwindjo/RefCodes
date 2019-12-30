from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
import pandas as pd
import numpy as np

from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report
from sklearn.metrics import f1_score
from sklearn.metrics import accuracy_score

tennis_data = pd.read_csv('playtennis.csv')
'''
print('tennis_data:')
print(tennis_data)
'''

tennis_data.Outlook = tennis_data.Outlook.replace('Sunny', 0)
tennis_data.Outlook = tennis_data.Outlook.replace('Overcast', 1)
tennis_data.Outlook = tennis_data.Outlook.replace('Rain', 2)

tennis_data.Temperature = tennis_data.Temperature.replace('Hot', 3)
tennis_data.Temperature = tennis_data.Temperature.replace('Mild', 4)
tennis_data.Temperature = tennis_data.Temperature.replace('Cool', 5)

tennis_data.Humidity = tennis_data.Humidity.replace('High', 6)
tennis_data.Humidity = tennis_data.Humidity.replace('Normal', 7)

tennis_data.Wind = tennis_data.Wind.replace('Weak', 8)
tennis_data.Wind = tennis_data.Wind.replace('Strong', 9)

tennis_data.PlayTennis = tennis_data.PlayTennis.replace('No', 10)
tennis_data.PlayTennis = tennis_data.PlayTennis.replace('Yes', 11)
''''''
print('replace tennis_data')
print(tennis_data)
''''''

X = pd.DataFrame(tennis_data, columns = ['Outlook', 'Temperature', 'Humidity', 'Wind'])
y = pd.DataFrame(tennis_data, columns = ['PlayTennis'])

X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=12345)

'''print('X_train :', X_train)
print('X_test :', X_test)
print('y_train :', y_train)
print('y_test :', y_test)'''

gnb_clf = GaussianNB()
gnb_clf = gnb_clf.fit(X_train, y_train.PlayTennis)
gnb_prediction = gnb_clf.predict(X_test)

print(gnb_prediction)

print('Confusion Matrix')
print(confusion_matrix(y_test, gnb_prediction))
print('Classification Report')

'''
Classification Report는 분류에 대한 측정 항목을 보여주는 보고서를 나타냅니다.

Classification Report의 측정 항목으로는 클래스 별의 precision, recall, f1-score와
전체 데이터의 precision, recall, f1-score가 있습니다.
'''
print(classification_report(y_test, gnb_prediction))
# 실제값과 예측값에 f1-score함수를 사용해 구한 f-measure와 accuracy_score 함수를 사용해
# 구한 accuracy를 나타내보겠습니다.


'''
f1_score 함수에 파라미터로 실제값 y_test와 예측값 gnb_prediction을 넣고 average를 weighted로 설정합니다. 
weighted는 클래스별로 가중치를 적용하는 역할을 합니다. 이렇게 3개의 파라미터를 넣고 f1_score를 구한 후 
round 함수를 이용해 소수점 2번째 자리까지 표현한 값을 변수 fmeasure에 저장합니다.
'''
fmeasure = round(f1_score(y_test, gnb_prediction, average = 'weighted'), 2)

'''
accuracy_score 함수에 파라미터로 실제값 y_test와 예측값 gnb_prediction을 넣고 normalize를 True로 설정합니다.
True는 정확도를 계산해서 출력해주는 역할을 합니다. False로 설정하게 되면 올바르게 분류된 데이터의 수를 출력합니다.
이렇게 3개의 파라미터를 넣고 accuracy를 구한 후 round 함수를 이용해 소수점 2번째 자리까지 표현한 값을 변수 accuracy에 저장합니다.
'''

accuracy = round(accuracy_score(y_test, gnb_prediction, normalize = True), 2)
# 컬럼이 Classifier, F-Measure, Accuracy인 데이터프레임을 변수 df_nbclf에 저장합니다.
df_nbclf = pd.DataFrame(columns=['Classifier', 'F-Measure', 'Accuracy'])


df_nbclf.loc[len(df_nbclf)] = ['Naive Bayes', fmeasure, accuracy]

'''
컬럼 Classifier에는 Naive Bayes로 저장하고, 데이터프레임 df_nbclf에 loc 함수를 사용해 
컬럼에 맞게 fmeasure 데이터와 accuracy 데이터를 데이터프레임에 저장합니다.
'''

# 저장한 데이터프레임을 출력합니다.
print(df_nbclf)
