""" Manipulations with tabulated amplitude models """

import os
import pandas as pd
import numpy as np
from cmath import phase, polar
import dalitz_tools as dt

def val_to_idx(value, grid_size, lims):
    """ Value into bin index """
    return np.array((value - lims[0]) / (lims[1] - lims[0]) * grid_size, dtype=int)

def read_sym_line(line):
    """ Line in symm table """
    return [float(val) for val in dt.FLOATS.findall(line[:-2])] + [int(line[-2])]

def read_sym_table(fname):
    """ Read text file with symmetric tabulated Dalitz decay model """
    with open(dt.ddist_path(fname)) as binf:
        first_line = binf.readline().split()
        var1, var2, grid_size = first_line[0], first_line[2][:-1], int(first_line[4])
        print "grid size", grid_size
        _, limits, titles = dt.parse_model_title(binf)
        npz_file_name = dt.npz_fname(fname)
        if os.path.isfile(npz_file_name):
            info = np.load(npz_file_name)
            data, binmap = info["data"], info["binmap"]
        else:
            data = [read_sym_line(line) for line in binf.readlines()]
            data, binmap = sym_amp_map(np.array(data), grid_size, limits, var1, var2)
            np.savez_compressed(npz_file_name, data=data, binmap=binmap)
    keys = ["p", "pb", "phi", 'real', 'imag', "delt"]
    data = dict(zip(keys, [data[:, :, idx] for idx in range(len(keys))]))
    return data, binmap, limits, titles, var1, var2

def rect_subrange(data, cuts, limits):
    """ 2D subrange """
    xgrid, ygrid = np.shape(data)
    xmin, xmax = val_to_idx(cuts[2:], xgrid, limits[2:])
    ymin, ymax = val_to_idx(cuts[:2], ygrid, limits[:2])
    return data[xmin:xmax, ymin:ymax]

def max_filter(val, max_val=1):
    """ Fixing bugs in data... """
    return 0 if abs(val) > max_val else val

def calculus(apre, apim, anre, anim, bug_flags=None):
    """ Cartesian into polar """
    if bug_flags is not None:
        apre = max_filter(apre) if bug_flags[0] else apre
        apim = max_filter(apim) if bug_flags[1] else apim
        anre = max_filter(anre) if bug_flags[2] else anre
        anim = max_filter(anim) if bug_flags[3] else anim
    ampp, ampn = complex(apre, apim), complex(anre, anim)
    absp, phip = polar(ampp)
    absn, phin = polar(ampn)
    if abs(ampp) == 0:
        print ampp
        delta = phase(ampn)
    else:
        delta = phase(ampn / ampp)
    delta = 0.0001 if delta == 0 else delta
    phin = 0.0001 if phin == 0 else phin
    phip = 0.0001 if phip == 0 else phip
    posi = (absp, absn, phip, apre, apim, delta)
    nega = (absn, absp, phin, anre, anim, -delta)
    return posi, nega

def sym_amp_map(data, grid_size, limits, var1, var2):
    """ Masses to bins """
    gsize1, gsize2 = grid_size, grid_size
    print data.shape
    var1_list, var2_list = data[:, 0], data[:, 1]
    var1_ind = val_to_idx(var1_list, gsize1, limits[var1])
    var2_ind = val_to_idx(var2_list, gsize2, limits[var2])
    amap = np.zeros((gsize1, gsize2, 6), dtype=float)
    binmap = np.zeros((gsize1, gsize2), dtype=int)
    for v1idx, v2idx, vals in zip(var1_ind, var2_ind, data):
        apre, apim, anre, anim = vals[2:-1]
        posi, nega = calculus(apre, apim, anre, anim)
        if var2 == 'mAC':
            amap[v2idx, v1idx, :] = nega[:]
            binmap[v2idx, v1idx] = vals[-1]
        amap[v1idx, v2idx, :] = posi[:]
        binmap[v1idx, v2idx] = vals[-1]
    return amap, binmap

def calc_bin_parameters(data, binmap):
    """ Integrals over Dalitz plot bins """
    valc, vals, valkp, valkn = [], [], [], []
    posi, nega, delt = data['p'], data['pb'], data['delt']
    kpkn = np.sqrt(posi * nega)
    for idx in xrange(8):
        mask = binmap == idx+1
        valkp.append(np.sum(posi[mask]))
        valkn.append(np.sum(nega[mask]))
        valc.append(np.sum(kpkn[mask] * np.cos(delt[mask])))
        vals.append(np.sum(kpkn[mask] * np.sin(delt[mask])))
    valkp = np.array(valkp)
    valkn = np.array(valkn)
    valc = np.array(valc)
    vals = np.array(vals)
    knorm = np.sum(valkp) + np.sum(valkn)
    p_row_prod = valkp * valkn
    valkp = valkp/knorm
    valkn = valkn/knorm
    valc = valc / p_row_prod
    vals = vals / p_row_prod
    return valkp, valkn, valc, vals

# def ampl_map(data, grid_size, limits, masses):
#     """ Binning color map """
#     gsize1, gsize2 = int(0.4*grid_size), int(0.4*grid_size)
#     ab_list, ac_list = data[:, 0], data[:, 1]
#     bc_list = mbc(ab_list, ac_list, masses)

#     ab_ind = val_to_idx(ab_list, gsize1, limits['mAB'])
#     ac_ind = val_to_idx(ac_list, gsize1, limits['mAC'])
#     bc_ind = val_to_idx(bc_list, gsize2, limits['mBC'])

#     bc_map = np.zeros((gsize1, gsize1, 5), dtype=float)
#     ac_map = np.zeros((gsize2, gsize1, 5), dtype=float)

#     bug_flags = [False] * 4
#     for v1idx, acidx, v2idx, vals in zip(ab_ind, ac_ind, bc_ind, data):
#         apre, apim, anre, anim = vals[2:]
#         posi, nega = calculus(apre, apim, anre, anim, bug_flags)
#         bug_flags = [abs(posi[2]) < 0.5, abs(posi[3]) < 0.5,
#                      abs(nega[2]) < 0.5, abs(nega[3]) < 0.5]
#         bc_map[v1idx, acidx, :], bc_map[acidx, v1idx, :] = posi[:], nega[:]
#         ac_map[v2idx, v1idx, :], ac_map[v2idx, acidx, :] = posi[:], nega[:]
#         if v1idx == acidx:
#             ac_map[v2idx-1, acidx, :] = ac_map[v2idx, acidx, :]
#     for idx in xrange(gsize1-1):
#         bc_map[idx, idx, :] = bc_map[idx+1, idx, :]
#     return {"ac" : ac_map, "bc" : bc_map}
