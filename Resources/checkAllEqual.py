import numpy as np
import sys

def checkAllEqual(arr, original):
    if np.array_equal(arr, original):
        print("Both versions are equal for all output EMD values!")
    else:
        print("Some values are different!")


if "__main__" == __name__:
    if (len(sys.argv) != 3):
        print("usage:\n\tmyversion.txt orginalVersion.txt")
        sys.exit(3)
    print("loading values...")
    myVersion = np.loadtxt(sys.argv[1])
    originalVersion = np.loadtxt(sys.argv[2])
    print("checking all values...")
    checkAllEqual(myVersion, originalVersion)
    
