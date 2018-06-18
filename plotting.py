#Script for plotting the data
import numpy as np
import matplotlib.pyplot as plt
import os, shutil
if not os.path.isdir('figures'):
    os.mkdir('figures')

for filename in os.listdir('.'):
    if filename.startswith("array"): 
        data = np.loadtxt(filename)
        plt.imshow(data,cmap="plasma")
        plt.colorbar()
        plt.savefig('./figures/'+filename+'.png')
        plt.close()
