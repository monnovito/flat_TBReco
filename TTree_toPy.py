import uproot
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Open the ROOT file
with uproot.open("run2117_tbreco.root") as file:
    # Access the tree
    print(file.keys())
    tree = file["datatree"]  # Replace "mdt" with your tree name

    # Convert the tree to a NumPy structured array
    array = tree.arrays(library="np")

    # If you want to access all data as a single structured array:
    data = np.core.records.fromarrays(array.values(), names=list(array.keys()))

print(data.dtype)  # This shows the structure of your structured array
#print(data[:10])  # This prints the first 10 entries in your structured array