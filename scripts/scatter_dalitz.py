""" Beautiful plots of Dalitz distributions """

import os.path
import sys
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import numpy as np
import dalitz_tools as dt
import ddist_tools as ddt
import plot_style as plst

INTRPL = 'none'
DBINS = 400
FSIZE = (5, 4)
DPI = 130
PADS_DDIST = dict(left=0.17, bottom=0.2, right=0.95, top=0.95)
PADS_MBC = dict(left=0.13, bottom=0.2, right=0.95, top=0.95)
LBL_SIZE = 22
FONT_SIZE = 20
CMAPS = {
    'ddist' : plt.cm.PuBu,
    'reim'  : plt.cm.RdBu,
    'p'     : plt.cm.RdBu,
    'phase' : plt.cm.gist_rainbow
}
CNORM = {
    'ddist' : colors.LogNorm(),
    'reim'  : colors.LogNorm(),
    'p'     : colors.LogNorm()
}

PHASE_TICKS = [-np.pi, -0.5*np.pi, 0, 0.5*np.pi, np.pi]
PHASE_LBL = [r'$-\pi$', r'$-\pi/2$', r'$0$', r'$\pi/2$', r'$\pi$']
BOUND_COEF = np.array([1., 1., 1., 1.])

def plot_ddist(fname):
    """ Scatter plot of Dalitz distribution """
    ddist, masses, _, titles = ddt.parse_ddist(fname)
    mab, mac = ddist[:, 0], ddist[:, 1]
    mbc = dt.mbc(mab, mac, masses)

    plt.figure(num=None, figsize=FSIZE, dpi=DPI)
    plt.hist2d(mbc, mab, bins=DBINS, norm=CNORM['ddist'], cmap=CMAPS['ddist'])
    plt.colorbar(pad=0.02)
    plt.ylabel(r'$'+titles['mAB']+'$', fontsize=LBL_SIZE)
    plt.xlabel(r'$'+titles['mBC']+'$', fontsize=LBL_SIZE)
    plt.subplots_adjust(**PADS_DDIST)

    if not os.path.isfile(dt.pict_path(fname)):
        plt.savefig(dt.pict_path(fname), format='eps', dpi=DPI)

def dalitz_to_mass(title):
    """ m^{2} -> m """
    return title.replace('m^{2}', 'm').replace('GeV^{2}', 'GeV').replace('c^{4}', 'c^{2}')

def plot_mabdist(fname, mabmax=9, mbcmin=3):
    """ Scatter plot of Dalitz distribution """
    ddist, masses, _, titles = ddt.parse_ddist(fname)
    mab, mac = ddist[:, 0], ddist[:, 1]
    mbc = dt.mbc(mab, mac, masses)
    mab = mab[mbc > mbcmin]
    mab = np.sqrt(mab[mab < mabmax])

    plt.figure(num=None, figsize=FSIZE, dpi=DPI)
    plt.hist(mab, bins=DBINS, normed=True, edgecolor="none", color=["navy"])
    title = dalitz_to_mass(r'$'+titles['mAB']+'$')
    plt.xlabel(title, fontsize=LBL_SIZE)
    plt.subplots_adjust(**PADS_MBC)
    plt.xlim(min(mab), max(mab))

    plt.gca().grid(which='major')
    plt.gca().tick_params(axis='both', which='major', direction='in', width=1, size=4)

def plot_mbcdist(fname, mbcmax=1.6**2, mabmin=9):
    """ Scatter plot of Dalitz distribution """
    ddist, masses, _, titles = ddt.parse_ddist(fname)
    mab, mac = ddist[:, 0], ddist[:, 1]
    mbc = dt.mbc(mab, mac, masses)
    mbc = mbc[mab > mabmin]
    # mbc = np.sqrt(mbc[mbc < mbcmax])
    mbc = mbc[mbc < mbcmax]

    plt.figure(num=None, figsize=FSIZE, dpi=DPI)
    plt.hist(mbc, bins=DBINS, normed=True, edgecolor="none", color=["navy"])
    title = dalitz_to_mass(r'$'+titles['mBC']+'$')
    plt.xlabel(title, fontsize=LBL_SIZE)
    plt.subplots_adjust(**PADS_MBC)
    plt.xlim(min(mbc), max(mbc))

    plt.gca().grid(which='major')
    plt.gca().tick_params(axis='both', which='major', direction='in', width=1, size=4)

def save_eps(label, cmd, pdi=DPI):
    """ eps file """
    plt.savefig('pics/' + cmd + '_' + label + '.eps', format='eps', dpi=pdi)

def make_plot():
    """ Main driver """
    plst.general_settings(FONT_SIZE)
    if len(sys.argv) == 1:
        plot_ddist("ddist_kuz_bdpp_1M.txt")
        return
    cmd = sys.argv[1]
    fname = "ddist_kuz_bdpp_1M.txt" if len(sys.argv) == 2 else sys.argv[2]
    label = fname.split('.')[0]
    if cmd == 'ddist':
        plot_ddist(fname)
    elif cmd == 'mab':
        plot_mabdist(fname)
    elif cmd == 'mbc':
        plot_mbcdist(fname)
    else:
        print "Wrong input!"
        print "Usage: python scatter_dalitz.py [plot_name] [data_file]"
    save_eps(label, cmd, 200)
    plt.show()

if __name__ == "__main__":
    make_plot()
