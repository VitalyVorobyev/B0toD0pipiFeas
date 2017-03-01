""" Manipulations with data """

import re
import numpy as np

FLOATS = re.compile(r"[-+]?\d+\.\d+")
INTS = re.compile(r"\d+")

MAIN_PATH = "/home/vitaly/B0toD0pipi/B0toD0pipiFeas/"

def ddist_path(file_name):
    """ Path to generated Dalitz distributions """
    return MAIN_PATH + "data/txt/" + file_name

def pict_path(file_name):
    """ Path to generated Dalitz distributions """
    return MAIN_PATH + "pics/" + file_name.split('.')[0] + '.eps'

def mbc(mab, mac, masses):
    """ The third Dalitz variable """
    return -mab - mac + (masses**2).sum()

def parse_model_title(binf):
    """ Read and parse five standard lines """
    binf.readline()  # title
    massstr = binf.readline().split()
    masses = np.array([float(val) for val in [massstr[0]] + massstr[2:]])
    limits, titles = {}, {}
    for _ in range(3):
        abline = binf.readline()
        limits[abline[:3]] = np.array([float(val) for val in FLOATS.findall(abline)])
        titles[abline[:3]] = r" ".join(abline.split()[1:-2])
    return masses, limits, titles

def npz_fname(fname):
    """ Corresponding .npz file """
    return MAIN_PATH + 'data/npz/' + fname.split('/')[-1].split('.')[0] + '.npz'
