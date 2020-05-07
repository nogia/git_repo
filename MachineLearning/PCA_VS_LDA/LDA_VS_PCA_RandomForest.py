import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as  sns
import statsmodels.api as sm
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import classification_report
from sklearn import tree
from sklearn import linear_model
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import confusion_matrix

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

#x_train_set = df_train.iloc[:,0:len(df_train.columns)-1]
x_train_set = df_train
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

#####################################################################
X = x_train.iloc[:,0:len(df_train.columns)-1]
le = LabelEncoder()
y = le.fit_transform(x_train['y'])
#####################################################################
print("Start LDA using scikit-learn")
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
lda = LinearDiscriminantAnalysis(n_components=3)
X_lda2 = lda.fit_transform(X, y)
print("lda.explained_variance_ratio_ = ",lda.explained_variance_ratio_)

############  LDA fpund only one vector  ###########################
print("End LDA using scikit-learn : LDA fpund only one vector")
############ Trying PCA ############################################
print("Start PCA using scikit-learn")
from sklearn.decomposition import PCA
pca = PCA(n_components=93)
X_pca = pca.fit_transform(X, y)
print("pca.explained_variance_ratio_ = ",pca.explained_variance_ratio_)

xx =  X_pca[:,0]
yy =   X_pca[:,1]
zz =   X_pca[:,2]
plt.xlabel('PC1')
plt.ylabel('PC2')
plt.ylabel('PC3')
plt.scatter(
    xx,
    yy,
   # zz,
    c=y,
    cmap='rainbow',
    alpha=0.7,
    edgecolors='b'
)
plt.show()
print("End PCA using scikit-learn")

###########  Train Using LDA  ##############################################
print("Start Classification using scikit-learn LDA/Random Forest")
X_train, X_test, y_train, y_test = train_test_split(X_lda2, y, random_state=1)
rf = RandomForestClassifier()
rf.fit(X_train, y_train)
y_pred = rf.predict(X_test)
c_matrix = confusion_matrix(y_test, y_pred)
print(c_matrix)
print("Accuracy = " ,(c_matrix[0][0]+c_matrix[1][1])/len(y_test))
print("End Classification using scikit-learn Decision Tree")
############ Train Using PCA  ##############################################
print("Start Classification using scikit-learn PCA/Random Forest")
X_train, X_test, y_train, y_test = train_test_split(X_pca, y, random_state=1)
rf = RandomForestClassifier()
rf.fit(X_train, y_train)
y_pred = rf.predict(X_test)
c_matrix = confusion_matrix(y_test, y_pred)
print(c_matrix)
print("Accuracy = " ,(c_matrix[0][0]+c_matrix[1][1])/len(y_test))
print("End Classification using scikit-learn PCA/Decision Tree")
###########################################################################



