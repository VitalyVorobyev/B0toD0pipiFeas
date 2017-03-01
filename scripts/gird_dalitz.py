""" Beautiful plots of Dalitz distributions """

import sys
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import matplotlib.ticker as ticker
import numpy as np
import tbl_tools as tblt
import plot_style as plst

MAXP = 0.8
INTRPL = 'none'
DBINS = 400
FSIZE = (5, 4)
DPI = 130
PADS = dict(left=0.17, bottom=0.2, right=0.95, top=0.95)
PADS_MBC = dict(left=0.13, bottom=0.2, right=0.95, top=0.95)
LBL_SIZE = 22
FONT_SIZE = 20
CMAPS = {
    'ddist' : plt.cm.PuBu,
    'reim'  : plt.cm.RdBu,
    'p'     : plt.cm.BuPu,
    'phase' : plt.cm.gist_rainbow,
    'bins'  : colors.ListedColormap(['white', 'deepskyblue', 'black', 'thistle', 'red',\
                              'limegreen', 'cornsilk', 'blue', 'yellow']),
    'binscb'  : colors.ListedColormap(['deepskyblue', 'black', 'thistle', 'red',\
                              'limegreen', 'cornsilk', 'blue', 'yellow'])
}

BIN_TICKS = np.arange(10)
BIN_BOUNDS = np.arange(10)-0.5

CNORM = {
    'ddist' : colors.LogNorm(),
    'reim'  : colors.SymLogNorm(linthresh=0.001, linscale=0.003),
    'p'     : colors.Normalize(vmin=0., vmax=MAXP), # colors.LogNorm()
    'bins'  : colors.BoundaryNorm(BIN_TICKS, CMAPS['bins'].N),
    'binscb'  : colors.BoundaryNorm(BIN_TICKS, CMAPS['binscb'].N)
}

PHASE_TICKS = [-np.pi, -0.5*np.pi, 0, 0.5*np.pi, np.pi]
PHASE_LBL = [r'$-\pi$', r'$-\pi/2$', r'$0$', r'$\pi/2$', r'$\pi$']
BOUND_COEF = np.array([1., 1., 1., 1.])

P_TICKS = [0., 0.25, 0.5, 0.75]
P_LBL = [r'$0$', r'$0.25$', r'$0.5$', r'$0.75$']

def tabular_data(fname):
    """ Tabulated amplitude for a Dalitz variables """
    data, binmap, limits, titles, var1, var2 = tblt.read_sym_table(fname)
    abmin, abmax = limits[var1]
    bcmin, bcmax = limits[var2]
    lim_list = np.array([bcmin, bcmax, abmin, abmax])
    xtitle = r'$'+titles[var2]+'$'
    ytitle = r'$'+titles[var1]+'$'
    return data, binmap, lim_list, xtitle, ytitle

def plot_real(data, lim_list, xtitle, ytitle, num=None):
    """ Real part of amplitude model """
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    limit = float(10**(int(np.log10(np.absolute(data).max())) + 1))
    plt.imshow(data, cmap=CMAPS['reim'], origin='lower', norm=CNORM['reim'],
               aspect='auto', extent=lim_list, interpolation=INTRPL,
               vmin=-limit, vmax=limit)
    cbar = plt.colorbar(pad=0.02, ticks=make_ticks(limit, 10, 4),
                        format=ticker.LogFormatterMathtext())
    cbar.ax.tick_params(labelsize=14)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def make_ticks(limit, factor=10., num=3):
    """ Double log scale """
    result = []
    for power in range(num):
        result.append(-limit / factor**power)
    for power in reversed(range(num)):
        result.append(limit / factor**power)
    return result

def plot_imag(data, lim_list, xtitle, ytitle, num=None):
    """ Imaginary part of amplitude model """
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    limit = float(10**(int(np.log10(np.absolute(data).max())) + 1))
    plt.imshow(data, cmap=CMAPS['reim'], origin='lower', norm=CNORM['reim'],
               aspect='auto', extent=lim_list, interpolation=INTRPL,
               vmin=-limit, vmax=limit)
    cbar = plt.colorbar(pad=0.02, ticks=make_ticks(limit, 10, 4),
                        format=ticker.LogFormatterMathtext())
    cbar.ax.tick_params(labelsize=14)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def plot_delta(data, lim_list, xtitle, ytitle, num=None):
    """ Phase difference map """
    data[data == 0] = None
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    plt.imshow(data, cmap=CMAPS['phase'], origin='lower', aspect='auto', extent=lim_list,
               vmin=-np.pi, vmax=np.pi, interpolation=INTRPL)
    cbar = plt.colorbar(pad=0.02, ticks=PHASE_TICKS)
    cbar.ax.set_yticklabels(PHASE_LBL)
    cbar.ax.tick_params(labelsize=18)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def plot_phi(data, lim_list, xtitle, ytitle, num=None):
    """ Amplitude model phase map """
    data[data == 0] = None
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    plt.imshow(data, cmap=CMAPS['phase'], origin='lower', aspect='auto', extent=lim_list,
               vmin=-np.pi, vmax=np.pi, interpolation=INTRPL)
    cbar = plt.colorbar(pad=0.02, ticks=PHASE_TICKS)
    cbar.ax.set_yticklabels(PHASE_LBL)
    cbar.ax.tick_params(labelsize=18)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def plot_p(data, lim_list, xtitle, ytitle, num=None):
    """ Squared absolute value of amplitude model """
    data[data == 0] = None
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    plt.imshow(data, cmap=CMAPS['p'], origin='lower', norm=CNORM['p'],
               aspect='auto', extent=lim_list, interpolation=INTRPL)
    cbar = plt.colorbar(pad=0.02, ticks=P_TICKS)
    cbar.ax.set_yticklabels(P_LBL)
    cbar.ax.tick_params(labelsize=18)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def plot_bins(binmap, lim_list, xtitle, ytitle, num=None):
    """ Binning """
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    img = plt.imshow(binmap, cmap=CMAPS['bins'], origin='lower', norm=CNORM['bins'],
                     aspect='auto', extent=lim_list, interpolation=INTRPL)
    cbar = plt.colorbar(img, cmap=CMAPS['binscb'], norm=CNORM['binscb'],\
                        boundaries=BIN_BOUNDS[1:], ticks=BIN_TICKS[1:], pad=0.02)
    cbar.ax.tick_params(labelsize=18)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def plot_mbc(data, limits, cuts, xtitle, ytitle, col='b-', num=None):
    """ Project Dalitz distribution """
    mbclo, mbchi = cuts[:2]
    data = tblt.rect_subrange(data, cuts, limits)
    # data = np.sqrt(data)
    _, xsize = np.shape(data)
    data_x = np.linspace(mbclo, mbchi, xsize)
    data_y = np.sum(data, axis=0) / np.sum(data) * xsize
    plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    plt.plot(data_x, data_y, col)
    plt.xlim(mbclo, mbchi)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.subplots_adjust(**PADS_MBC)
    plt.gca().grid(which='major')
    plt.gca().tick_params(axis='both', which='major', direction='in', width=1, size=4)
    plot_p(data, cuts, xtitle, ytitle, 2)

def save_eps(label, cmd, pdi=DPI):
    """ eps file """
    plt.savefig('pics/' + cmd + '_' + label + '.eps', format='eps', dpi=pdi)
    plt.savefig('pics/png/' + cmd + '_' + label + '.png', format='png', dpi=pdi)

def make_plot():
    """ Main driver """
    plst.general_settings(FONT_SIZE)
    cmd = sys.argv[1]
    fname = 'tblSymABBC_kuz_bdpp_1M_om.txt' if len(sys.argv) == 2 else sys.argv[2]
    # fname = 'tblSymABAC_kuz_bdpp_1M.txt' if len(sys.argv) == 2 else sys.argv[2]
    label = fname.split('.')[0]
    data, binmap, lim_list, xtitle, ytitle = tabular_data(fname)
    if cmd == 'mbc':
        cuts = [lim_list[0], 1.6**2, 9., lim_list[3]]
        plot_mbc(data['r'], lim_list, cuts, xtitle, ytitle, 'b-', 1)
        plt.show()
        return
    if cmd == 'bins':
        plot_bins(binmap, lim_list, xtitle, ytitle)
    elif cmd == 'delt':
        plot_delta(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'real':
        plot_real(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'imag':
        plot_imag(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'phi':
        plot_phi(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'p':
        plot_p(data['r'], lim_list, xtitle, ytitle)
    elif cmd == 'calc':
        kpv, knv, cosv, sinv = tblt.calc_bin_parameters(data, binmap)
        for a, b, c, d in zip(kpv, knv, cosv, sinv):
            print "K+ =", a, ", K- =", b, ", C =", c, ", S =", d
    elif cmd == 'all':
        plot_delta(data['delt'], lim_list, xtitle, ytitle, 1)
        save_eps(label, 'delt')
        plot_real(data['real'], lim_list, xtitle, ytitle, 2)
        save_eps(label, 'real')
        plot_imag(data['imag'], lim_list, xtitle, ytitle, 3)
        save_eps(label, 'imag')
        plot_phi(data['phi'], lim_list, xtitle, ytitle, 4)
        save_eps(label, 'phi')
        plot_p(data['r'], lim_list, xtitle, ytitle, 5)
        save_eps(label, 'r')
        plot_bins(binmap, lim_list, xtitle, ytitle)
        save_eps(label, 'bins')
        plt.show()
        return
    else:
        print "Wrong input!"
        print "Usage: python scatter_dalitz.py [plot_name] [data_file]"
    save_eps(label, cmd, 200)
    plt.show()

if __name__ == "__main__":
    make_plot()
