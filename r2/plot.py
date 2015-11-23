import matplotlib.pyplot as plt
import numpy as np

re = np.genfromtxt("eval_re.csv",delimiter=';')
im = np.genfromtxt("eval_im.csv",delimiter=';')

for i in range(len(re)):
	plt.scatter(re[i],im[i])
plt.show()



