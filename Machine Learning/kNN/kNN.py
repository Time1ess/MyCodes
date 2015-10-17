from numpy import *
import operator
from collections import Counter
from random import random

def createDataSet():
    group=array([[1.2,2.3],[0.7,2.1],[1.0,1.0],[0.9,0.8],[2.1,0.6],
        [2.1,0.6],[3.0,1.0],[3.2,0.8],[2.9,2.4],[3.4,1.3],
        [0.8,2.2],[1.0,3.0],[2.3,0.6],[0.9,3.4],[1.8,3.3],
        [2.4,2.3],[3.0,3.0],[3.2,2.4],[2.6,3.4],[3.2,3.4]])
    labels=['A','A','A','A','A',
            'B','B','B','B','B',
            'C','C','C','C','C',
            'D','D','D','D','D'
            ]
    return group,labels

def classify0(inX,dataSet,labels,k):
    dataSetSize=dataSet.shape[0] #get size of rows in dataSet
    diffMat=tile(inX,(dataSetSize,1))-dataSet # get difference with each class
    sqDiffMat=diffMat**2 #square the difference
    sqDistances=sqDiffMat.sum(axis=1) # sum by rows
    distances=sqDistances**0.5 #get the distance
    sortedDistIndicies=distances.argsort() #return labels by values ascent
    classCount={}
    for i in range(k):
        voteIlabel=labels[sortedDistIndicies[i]]
        classCount[voteIlabel]=classCount.get(voteIlabel,0)+1
    count=Counter(classCount)
    return count.most_common(1)[0][0]

def main():
    group,labels=createDataSet()
    f=open('data.txt','w')
    for i in xrange(20000):
        data=[random()*4 for k in xrange(2)]
        prediction=classify0(data,group,labels,5)
        print 'For point: %.2f,%.2f'%(data[0],data[1]),' kNN predicts: Class',prediction
        print >>f,'%.2f %.2f %d'%(data[0],data[1],ord(prediction)-ord('A'))
    f.close()


if __name__=='__main__':
    main()
