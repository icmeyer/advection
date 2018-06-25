#Script for plotting the data
import numpy as np
import matplotlib.pyplot as plt
import os, shutil
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("folder", help="folder to store files in")
args = parser.parse_args()
folder = args.folder
print('Storing in folder: ',folder)
directory = '../'+folder

if not os.path.isdir(directory):
    os.mkdir(directory)

for filename in os.listdir('.'):
    if filename.startswith("array"): 
        data = np.loadtxt(filename)
        plt.imshow(data,cmap="plasma",vmin=0.0,vmax=1.2,origin='lower')
        plt.colorbar()
        plt.savefig(directory+'/'+filename+'.png')
        plt.close()
print('Done')
