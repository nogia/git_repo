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

######################################################################################
# LDA From Scratch
######################################################################################
#compute d dimensions vectors for each class : 0, 1 in this case
X = x_train.iloc[:,0:len(df_train.columns)-1]
col_names =  [0,1]
class_feature_means = pd.DataFrame(columns=col_names)
for c, rows in x_train.groupby('y'):
    class_feature_means[c] = rows.mean()
num_rows = len(class_feature_means[0]) -1
class_feature_means = class_feature_means[0:num_rows]

#2
#plug the mean vectors (mi) into the equation from before
# in order to obtain the within class scatter matrix.
matrix_size = len(class_feature_means)
within_class_scatter_matrix = np.zeros((matrix_size,matrix_size))
for c, rows in x_train.groupby('y'):
    rows = rows.drop(['y'], axis=1)

s = np.zeros((matrix_size, matrix_size))
for index, row in rows.iterrows():
    x, mc = row.values.reshape(matrix_size, 1), class_feature_means[c].values.reshape(matrix_size, 1)
    s += (x - mc).dot((x - mc).T)
within_class_scatter_matrix += s


#3
#we calculate the between class scatter matrix using the following formula.
feature_means = x_train.mean()
feature_means = feature_means[0:len(feature_means)-1]
between_class_scatter_matrix = np.zeros((matrix_size, matrix_size))
for c in class_feature_means:
    n = len(x_train.loc[x_train['y'] == c].index)

    mc, m = class_feature_means[c].values.reshape(matrix_size, 1), feature_means.values.reshape(matrix_size, 1)

    between_class_scatter_matrix += n * (mc - m).dot((mc - m).T)

#  solve the generalized eigenvalue problem for
eigen_values, eigen_vectors = np.linalg.eig(np.linalg.inv(within_class_scatter_matrix).dot(between_class_scatter_matrix))
print("Eigen Values = ")
print(eigen_values)
#The eigenvectors with the highest eigenvalues carry the most
# information about the distribution of the data. Thus, we sort
# the eigenvalues from highest to lowest and select the first k
# eigenvectors. In order to ensure that the eigenvalue maps to
# the same eigenvector after sorting, we place them in a
# temporary array.
pairs = [(np.abs(eigen_values[i]), eigen_vectors[:,i]) for i in range(len(eigen_values))]
pairs = sorted(pairs, key=lambda x: x[0], reverse=True)
for pair in pairs:
    print(pair[0])
# from output above we can see that most of varience described by
# first 1 eigenvalues
# 4.134169691291513
# 2.2118180158789248e-14
# 2.2118180158789248e-14

eigen_value_sums = abs(np.sum(abs(eigen_values)))
print("eigen_value_sums = ",eigen_value_sums)
print('Explained Variance')
for i, pair in enumerate(pairs):
    #print("i=",i," pair[0]=",pair[0]," eigen_value_sums = ",eigen_value_sums);
    print('Eigenvector {}: {}'.format(i, (abs(pair[0])/eigen_value_sums).real))

#Explained Variance by 1 eigenvalue
#Eigenvector 0: 1.000000000000007
#Eigenvector 1: 5.350090056869362e-15
#Eigenvector 2: 5.350090056869362e-15
#First, we create a matrix W with the first 1 eigenvectors.
w_matrix = np.hstack((pairs[0][1].reshape(matrix_size,1), pairs[1][1].reshape(matrix_size,1) )).real

# we save the dot product of X and W into a new matrix Y.
X_lda = np.array(X.dot(w_matrix))
#matplotlib can’t handle categorical variables directly.
# Thus, we encode every class as a number so that we can
# incorporate the class labels into our plot.
le = LabelEncoder()
y = le.fit_transform(x_train['y'])

plt.xlabel('LD1')
plt.ylabel('LD2')
xx =  X_lda[:,0]
yy =   X_lda[:,1]
plt.scatter(
    xx,
    yy,
    c=y,
    cmap='rainbow',
    alpha=0.7,
    edgecolors='b'

)
plt.show()
print("End ")

#####################################################################
print("Start LDA using scikit-learn")
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
lda = LinearDiscriminantAnalysis(n_components=3)
X_lda2 = lda.fit_transform(X, y)
print("lda.explained_variance_ratio_ = ",lda.explained_variance_ratio_)

############  LDA fpund only one vector  ###########################
print("End LDA using scikit-learn : LDA found only one vector")
############ Trying PCA ############################################
