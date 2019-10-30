# -*- coding: utf-8 -*-
"""
Created on Mon Jun 17 09:12:19 2019

@author: rditlkc9
"""
import matplotlib.pyplot as plt
import numpy
current = []
volt = []


f=open("data/capture.txt", "r")

if f.mode=='r':
    f1=f.readlines()
    f1.pop(0)
    for x in f1:
        y=x.split(",")
        z = y[0].split(":")
        zz=y[1].split(":")
        volt.append(float(z[1]))
        current.append(float(zz[1]))
f.close()

xAxis=volt
yAxis=current

fig, ax = plt.subplots()
ax.plot(xAxis, yAxis)
ax.set(xlabel='Range (mv)', ylabel='Current (uA)')
ax.set_title('Fig 2')
ax.grid()
#fig.savefig("VRangevsSeCurrentTest1.png")
plt.show()