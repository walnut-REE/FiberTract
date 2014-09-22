import cPickle as p
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt


# 1. Load data part
#fiberFile = open('FiberData/01CGCskeletonPos.txt', "r")
#fiberFile = open('FiberData/02CGHskeletonPos.txt', "r")
#fiberFile = open('FiberData/03CSTskeletonPos.txt', "r")
#fiberFile = open('FiberData/04ATRskeletonPos.txt', "r")
#fiberFile = open('FiberData/05SLFskeletonPos.txt', "r")
#fiberFile = open('FiberData/06SLFtskeletonPos.txt', "r")
#fiberFile = open('FiberData/07ILFskeletonPos.txt', "r")
#fiberFile = open('FiberData/08IFOskeletonPos.txt', "r")
#fiberFile = open('FiberData/09UNCskeletonPos.txt', "r")
#fiberFile = open('FiberData/10FmajorskeletonPos.txt', "r")
#fiberFile = open('FiberData/11FminorskeletonPos.txt', "r")

# tractograph data
#fiberFile = open('FiberData/tractCGCskeletonPos.txt', "r")
fiberFile = open('FiberData/tractIFOskeletonPos.txt', "r")

# FiberData used to keep all the fiber data
FiberData = []

for line in fiberFile:
    data = []
    
    # save the 0, 1, 2 dim to data
    pos =  line.split('\t')
    data.append(int(pos[0]))
    data.append(int(pos[1]))
    data.append(int(pos[2]))
    
    # add a 3d position to Fiber Data
    FiberData.append(data)



# 2. display part

# Plot the fiber tracts
fig = plt.figure()
ax = fig.gca(projection='3d')

X = []
Y = []
Z = []

for pointNumber in range(0, len(FiberData)):
    X.append(FiberData[pointNumber][0])
    Y.append(FiberData[pointNumber][1])
    Z.append(FiberData[pointNumber][2])
    
ax.plot(X, Y, Z, "b.", markersize=1.0) 

plt.xlim(1, 181)
plt.ylim(1, 217)
ax.set_zlim(1, 181)


plt.show()
