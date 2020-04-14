import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as  sns
import statsmodels.api as sm
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report
from sklearn import tree
from sklearn import linear_model

def get_float_rows(dataset) :
    col_float = []
    col_object = []
    for i in dataset.columns:
        if dataset[i].dtypes == np.float:
            col_float.append(i)
        elif dataset[i].dtypes == np.object:
            col_object.append(i)
    return col_float,col_object
# Load in data
df_train = pd.read_csv('exercise_02_train.csv')
x_test_set  = pd.read_csv('exercise_02_test.csv')

# check data types before training

df_train_types = df_train.dtypes
x_test_types = df_train.dtypes

x_train_set = df_train.iloc[:,0:len(df_train.columns)-1]

col_float,col_object = get_float_rows(x_train_set)

x_train_set[col_object[2]] =x_train_set[col_object[2]].replace('[\$,]', '', regex=True).astype(float)
x_train_set[col_object[3]] =x_train_set[col_object[3]].replace('[\%,]', '', regex=True).astype(float)
categorized = [col_object[0],col_object[1],col_object[4],col_object[5]]
for i in range(0,len(categorized)):
    codes, uniques = pd.factorize(x_train_set[categorized[i]])
    print(type(list(codes)))
    x_train_set[categorized[i]] = list(codes)

x_test_set[col_object[2]] =x_test_set[col_object[2]].replace('[\$,]', '', regex=True).astype(float)
x_test_set[col_object[3]] =x_test_set[col_object[3]].replace('[\%,]', '', regex=True).astype(float)
categorized = [col_object[0],col_object[1],col_object[4],col_object[5]]
for i in range(0,len(categorized)):
    codes, uniques = pd.factorize(x_test_set[categorized[i]])
    print(type(list(codes)))
    x_test_set[categorized[i]] = list(codes)

x_train = x_train_set
x_test = x_test_set

# using Nearest neighbors imputation
import numpy as np
from sklearn.impute import KNNImputer

x_train = x_train.replace(x_train.isnull(), np.nan)
x_test = x_test.replace(x_train.isnull(), np.nan)

miss_number_train = (x_train.isnull().sum() > 0).astype(np.int64).sum()
print("Before removing impurities = ",miss_number_train)
miss_number_test = (x_test.isnull().sum() > 0).astype(np.int64).sum()
print("Before removing impurities = ",miss_number_test)

imputer = KNNImputer(n_neighbors=1)
xtrain_filled = imputer.fit_transform(x_train)
xtest_filled = imputer.fit_transform(x_test)

x_train = pd.DataFrame(data=xtrain_filled, columns=x_train.columns)
x_test = pd.DataFrame(data=xtest_filled, columns=x_test.columns)

miss_number_train = (x_train.isnull().sum() > 0).astype(np.int64).sum()
print("After removing impurities = ",miss_number_train)
miss_number_test = (x_test.isnull().sum() > 0).astype(np.int64).sum()
print("Before removing impurities = ",miss_number_test)

######################################################################################
# Training logistic regression classifier using the first Optimal principal components.
######################################################################################
from sklearn.linear_model import LogisticRegression
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn import linear_model
from sklearn import model_selection
from sklearn.model_selection import cross_val_predict
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import GridSearchCV
print("Start PCA/PCR ML Logistic Regression Algorithm")
scaler = StandardScaler()
X = scaler.fit_transform(x_train)
X_test = scaler.fit_transform(x_test)
pca = PCA(0.99)
pca.fit(X)
num_components = pca.n_components_
print("Optimal number of Principal Components = ",num_components)

pca = PCA(n_components=num_components)
x_train_pca = pca.fit_transform(X)
x_test_pca = pca.fit_transform(X_test)

columns = []
for i in range(0,num_components):
    pca_numner = i+1
    columns.append('PC'+ str(pca_numner))

#  X = dataset reduced to 92 Principal Components
# x_test = test dataset reduced to 92 Principal Components
X = pd.DataFrame(data = x_train_pca, columns = columns)
x_test = pd.DataFrame(data = x_test_pca, columns =  columns)
y = df_train['y']
#############################################################################
#############################################################################
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

regr = linear_model.LogisticRegression()
regr.fit(X_train, y_train)
regr_predict = regr.predict(X_test)
####################  Statistics Results    ##############################
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
kf = KFold(shuffle=True, n_splits=5)
regr_cv_score = cross_val_score(regr, X, y, cv=kf, scoring='accuracy')

from sklearn import metrics
print('=============== Accuracy Score ===============')
print(metrics.accuracy_score(y_test, regr_predict))
print('=============== Total Counts ================')
print(y_test.value_counts())
print('=============== y_test.mean ===============')
print(y_test.mean())
print('=============== 1 - y_test.mean ===============')
print(1 - y_test.mean())
print('=============== the first 25 true and predicted responses ===============')
print('True:', y_test.values[0:25])
print('False:',regr_predict[0:25])
########################################################################
confusion = metrics.confusion_matrix(y_test, regr_predict)
print('=============== Confusion Matrix ===============')
print(confusion)
TP = confusion[1, 1]
TN = confusion[0, 0]
FP = confusion[0, 1]
FN = confusion[1, 0]
# use float to perform true division, not integer division
print((TP + TN) / float(TP + TN + FP + FN))
print(metrics.accuracy_score(y_test, regr_predict))
classification_error = (FP + FN) / float(TP + TN + FP + FN)
print('=============== classification error ===============')
print(classification_error)
print(1 - metrics.accuracy_score(y_test, regr_predict))
sensitivity = TP / float(FN + TP)
print('=============== sensitivity =============== ')
print(sensitivity)
print(metrics.recall_score(y_test, regr_predict))
specificity = TN / (TN + FP)
print("=============== specifisity =============== ")
print(specificity)
false_positive_rate = FP / float(TN + FP)
print("=============== false positive ===============")
print(false_positive_rate)
print(1 - specificity)
false_negative_rate = FN / float(FN + TP)
print("=============== false Negative ===============")
print(false_negative_rate)
print(1 - sensitivity)
precision = TP / float(TP + FP)
print("=============== presision ===============")
print(precision)
print(metrics.precision_score(y_test, regr_predict))
print("================== Classification Report ===============")
print(classification_report(y_test, regr_predict))
print('Cross Validation Score = ')
print(regr_cv_score)
print("=== Mean Of Cross Validation Score ===")
print( regr_cv_score.mean())
##################################3#########################################
from sklearn.metrics import plot_confusion_matrix
# Plot non-normalized confusion matrix
titles_options = [("Confusion matrix, without normalization", None),
                  ("Normalized confusion matrix", 'true')]
for title, normalize in titles_options:
    disp = plot_confusion_matrix(regr, X_test, y_test,
                                 display_labels= ['0','1'],
                                 cmap=plt.cm.Blues,
                                 normalize=normalize)
    disp.ax_.set_title(title)
plt.show()
#########################################################################
y_pred_proba = regr.predict_proba(X_test)[:, 1]
fpr, tpr, _ = metrics.roc_curve(y_test,  y_pred_proba)
auc = metrics.roc_auc_score(y_test, y_pred_proba)
plt.plot(fpr,tpr,label="data 1, auc="+str(auc))
plt.legend(loc=4)
plt.show()
import matplotlib.pyplot as plt
plt.hist(y_pred_proba, bins=8)
plt.xlim(0,1)
plt.title('Histogram of predicted probabilities')
plt.xlabel('Predicted probability of 1 ')
plt.ylabel('Frequency')
plt.show()
#########################################################################
# Calculate and Output Predicted values on exercise_02_test.csv
y_pred_class = np.trunc(regr.predict(x_test))
y_pred_class = y_pred_class.astype(int)
import numpy
numpy.savetxt('results1.csv', y_pred_class, delimiter=',', header="y predicted PCA/ Logistic Regression", comments="",fmt="%d")
print('END PCA/PCR ML Logistic Regression Algorithm')
########################################################################



