""" Manipulations with Dalitz distributions """

import numpy as np
import dalitz_tools as dt

def parse_ddist(file_name):
    """ Parse text file """
    with open(dt.ddist_path(file_name)) as binf:
        print binf.readline()  # events
        masses, limits, titles = dt.parse_model_title(binf)
        ddist = np.array([[float(val) for val in line.split()] for line in binf.readlines()])
        return ddist, masses, limits, titles
