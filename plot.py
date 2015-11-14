import numpy as np
import matplotlib.cm as cm
from matplotlib import pyplot as plt
from matplotlib.colors import Normalize
from matplotlib.colors import LogNorm
import sys

#with open("order.txt",'r') as area_file:
#	areas = []
#	for line in area_file:
#		areas.append(line[0:-1])

evec = np.absolute(np.genfromtxt("evec.csv", delimiter=';'))
tau = np.genfromtxt("tau.csv",delimiter=';')
tau2 = np.genfromtxt("tau2.csv",delimiter=';')



#for i in range(len(tau)):
#	plt.scatter(i,tau[i])
#plt.show()
#exit(0)

my_cmap = cm.get_cmap('hot')
my_cmap.set_under('black')
my_cmap.set_bad('grey')

#plt.imshow(evec,cmap=my_cmap,norm=Normalize(vmin=0,vmax=0.7),interpolation='nearest')
plt.imshow(evec,cmap=my_cmap,interpolation='nearest')
#plt.imshow(FLN,cmap=my_cmap,norm=LogNorm(vmin=1e-7,vmax=1),interpolation='nearest')
#plt.xticks(range(29),areas,rotation=90.)
#plt.yticks(range(29),areas)
#plt.tick_params(axis='both',labelsize=9)

plt.colorbar()
#plt.savefig("FLN.png",dpi=300)
plt.show()







