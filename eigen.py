from numpy import linalg as la
import numpy as np
import matplotlib.cm as cm
from matplotlib.colors import LogNorm
import matplotlib.pyplot as plt
import sys

N = 29
NN =2*N

w = np.genfromtxt("w.csv",delimiter=';')

vals, vecs = la.eig(w)


tau = -1/vals.real
tau_ordered = np.sort(tau)
tau = tau.tolist()

order = []
for i in range(NN):
	t = tau_ordered[i]
	a = tau.index(t)
	order.append(a)

for i in range(NN):
	plt.scatter(i,tau[order[i]])
plt.show()
exit(0)
ww = []
for i in range(NN):
	ww.append(np.asarray(w[:NN,order[i]]))
#	if(i==28):
#		ww[i] = np.asarray([-0.45]*NN)
ww = np.asarray(ww)
ww = ww.transpose()
my_cmap = cm.get_cmap('hot')
my_cmap.set_under('black')


xt = []
for i in range(58):
	xt.append("%.2f" % tau_ordered[i])

plt.imshow(ww,cmap=my_cmap,interpolation='nearest')
plt.xticks(range(NN),xt[:NN],rotation=90.)
plt.colorbar()


plt.show()



exit(0)



