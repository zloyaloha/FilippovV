import random
import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt

INPUT_NEU = 4
OUT_NEU = 3
HID_NEU = 10
ALPHA = 0.002
EPOCH = 100

iris = datasets.load_iris()
dataset = [(iris.data[i][None, ...], iris.target[i]) for i in range(len(iris.target))]
lossArr = []
probArr = []


w1 = np.random.randn(INPUT_NEU, HID_NEU) #матрица 
b1 = np.random.randn(1, HID_NEU)
w2 = np.random.randn(HID_NEU, OUT_NEU)
b2 = np.random.randn(1, OUT_NEU)

def ReluDeriv(t):
    return (t >= 0).astype(float)

def Full(y, num_classes):
    yFull = np.zeros((1, num_classes))
    yFull[0,y] = 1
    return yFull

def Sce(z,y):
    return -np.log(z[0,y])

def Relu(t):
    return np.maximum(t, 0)

def Softmax(t):
    out = np.exp(t)
    return out / np.sum(out)

counter = 0
k = 1

for ep in range(EPOCH):
    random.shuffle(dataset)
    for i in range(len(dataset)):

        x, y = dataset[i]

        t1 = x @ w1 + b1
        h1 = Relu(t1)
        t2 = h1 @ w2 + b2
        z = Softmax(t2)
        maxi = np.argmax(z)
        if (maxi == y):
            counter += 1
        k += 1
        if (k > 250):
            probArr.append((counter / k) * 100)


        e = Sce(z, y)

        yFull = Full(y, OUT_NEU)
        de_dt2 = z - yFull
        de_dw2 = h1.T @ de_dt2
        de_db2 = de_dt2
        de_dh1 = de_dt2 @ w2.T
        de_dt1 = de_dh1 * ReluDeriv(t1)
        de_dw1 = x.T @ de_dt1
        de_db1 = de_dt1

        w1 = w1 - ALPHA * de_dw1
        b1 = b1 - ALPHA * de_db1
        w2 = w2 - ALPHA * de_dw2
        b2 = b2 - ALPHA * de_db2

        lossArr.append(e)
def Predict(x):
    t1 = x @ w1 + b1
    h1 = Relu(t1)
    t2 = h1 @ w2 + b2
    z = Softmax(t2)
    return z

def CalcAccuracy():
    correct = 0
    for x, y in dataset:
        z = Predict(x)
        pred = np.argmax(z)
        if y == pred:
            correct += 1
    acc = correct / len(dataset)
    return acc

accuracy = CalcAccuracy()
print("Accuracy: ", accuracy)

fig = plt.figure()


ax1 = fig.add_subplot(1,2,1)
ax2 = fig.add_subplot(1,2,2)
ax1.grid(True)
ax2.grid(True)
ax1.set(title = 'Mistake cross entropy')
ax2.set(title = 'Probability of guessing')
ax1.plot(lossArr)
ax2.plot(probArr)


plt.show()


