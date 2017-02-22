""" Manipulations with data """

import os
import re
import numpy as np
from cmath import phase, polar

FLOATS = re.compile(r"[-+]?\d+\.\d+")
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
    """ Five standard lines """
    binf.readline()  # title
    massstr = binf.readline().split()
    masses = np.array([float(val) for val in [massstr[0]] + massstr[2:]])
    limits, titles = {}, {}
    for _ in range(3):
        abline = binf.readline()
        limits[abline[:3]] = np.array([float(val) for val in FLOATS.findall(abline)])
        titles[abline[:3]] = r" ".join(abline.split()[1:-2])
    return masses, limits, titles

def parse_ddist(file_name):
    """ Parse text file """
    with open(ddist_path(file_name)) as binf:
        print binf.readline()  # events
        masses, limits, titles = parse_model_title(binf)
        ddist = np.array([[float(val) for val in line.split()] for line in binf.readlines()])
        return ddist, masses, limits, titles

def val_to_idx(value, grid_size, lims):
    """ Value into bin index """
    return np.array((value - lims[0]) / (lims[1] - lims[0]) * grid_size, dtype=int)

def npz_fname(fname):
    """ Corresponding .npz file """
    return MAIN_PATH + 'data/npz/' + fname.split('/')[-1].split('.')[0] + '.npz'

def parse_dtbl(file_name):
    """ Read tabulated decay model from file """
    with open(ddist_path(file_name)) as binf:
        grid_size = int(binf.readline().split()[-1])
        masses, limits, titles = parse_model_title(binf)
        npz_file_name = npz_fname(file_name)
        if os.path.isfile(npz_file_name):
            data = np.load(npz_file_name)
        else:
            data = np.array([[float(val) for val in FLOATS.findall(line)]
                             for line in binf.readlines()])
            data = ampl_map(data, grid_size, limits, masses)
            np.savez_compressed(npz_file_name, **data)
    keys = ["r", "phi", 'real', 'imag', "delt"]
    data_bc = dict(zip(keys, [data['bc'][:, :, idx] for idx in range(len(keys))]))
    data_ac = dict(zip(keys, [data['ac'][:, :, idx] for idx in range(len(keys))]))
    return data_bc, data_ac, limits, titles

def rect_subrange(data, cuts, limits):
    """ 2D subrange """
    xgrid, ygrid = np.shape(data)
    xmin, xmax = val_to_idx(cuts[:2], xgrid, limits[:2])
    ymin, ymax = val_to_idx(cuts[2:], ygrid, limits[2:])
    return data[xmin:xmax, ymin:ymax]

def max_filter(val, max_val=1):
    """ Fixing bugs in data... """
    return 0 if abs(val) > max_val else val

def calculus(apre, apim, anre, anim, bug_flags):
    """ Cartesian into polar """
    if bug_flags[0]:
        apre = max_filter(apre)
    if bug_flags[1]:
        apim = max_filter(apim)
    if bug_flags[2]:
        anre = max_filter(anre)
    if bug_flags[3]:
        anim = max_filter(anim)
    ampp, ampn = complex(apre, apim), complex(anre, anim)
    absp, phip = polar(ampp)
    absn, phin = polar(ampn)
    if abs(ampp) == 0:
        print ampp
        delta = phase(ampn)
    else:
        delta = phase(ampn / ampp)
    if delta == 0:
        delta = 0.0001
    if phin == 0:
        phin = 0.0001
    if phip == 0:
        phip = 0.0001
    return (absp, phip, apre, apim, delta), \
           (absn, phin, anre, anim, -delta)

def ampl_map(data, grid_size, limits, masses):
    """ Binning color map """
    gsize1, gsize2 = int(0.4*grid_size), int(0.4*grid_size)

    ab_list, ac_list = data[:, 0], data[:, 1]
    bc_list = mbc(ab_list, ac_list, masses)

    ab_ind = val_to_idx(ab_list, gsize1, limits['mAB'])
    ac_ind = val_to_idx(ac_list, gsize1, limits['mAC'])
    bc_ind = val_to_idx(bc_list, gsize2, limits['mBC'])

    bc_map = np.zeros((gsize1, gsize1, 5), dtype=float)
    ac_map = np.zeros((gsize2, gsize1, 5), dtype=float)

    bug_flags = [False] * 4
    for abidx, acidx, bcidx, vals in zip(ab_ind, ac_ind, bc_ind, data):
        apre, apim, anre, anim = vals[2:]
        posi, nega = calculus(apre, apim, anre, anim, bug_flags)
        bug_flags = [abs(posi[2]) < 0.5, abs(posi[3]) < 0.5,
                     abs(nega[2]) < 0.5, abs(nega[3]) < 0.5]
        bc_map[abidx, acidx, :], bc_map[acidx, abidx, :] = posi[:], nega[:]
        ac_map[bcidx, abidx, :], ac_map[bcidx, acidx, :] = posi[:], nega[:]
        if abidx == acidx:
            ac_map[bcidx-1, acidx, :] = ac_map[bcidx, acidx, :]
    for idx in xrange(gsize1-1):
        bc_map[idx, idx, :] = bc_map[idx+1, idx, :]
    return {"ac" : ac_map, "bc" : bc_map}
