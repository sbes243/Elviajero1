
import matplotlib.pyplot as plt
from numpy.lib.shape_base import split
import pandas as pd
import numpy as np
import time
import random

x=np.array([1,2,3,4,5])
y1=x**2
y2=x**3


#plt.show()

lista1=[]
lista2=[]
with open("ploting.txt") as archivo:
    for linea in archivo:
        z=(linea.split('\n',1)[0])
        lista1.append(np.float64(z.split(',',1)[0]))
        lista2.append(np.float64(z.split(',',1)[1]))

x=[]
i=0
while(i<len(lista1)):
    x.append(np.int64(i))
    i=i+1
v=0

plt.plot(x,lista2,'b')
plt.show()
#with open("tiempo.txt") as archivo1:
#    for linea in archivo1:
#        y.append(np.float16(linea));

#plt.plot(x,y)
#plt.show()
