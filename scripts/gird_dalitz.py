""" Beautiful plots of Dalitz distributions """

import sys
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import matplotlib.ticker as ticker
import numpy as np
import dalitz_tools as dt
import plot_style as plst

INTRPL = 'none'
DBINS = 400
FSIZE = (5, 4)
DPI = 130
PADS = dict(left=0.17, bottom=0.2, right=0.95, top=0.95)
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
    'reim'  : colors.SymLogNorm(linthresh=0.001, linscale=0.003),
    'p'     : colors.LogNorm()
}

PHASE_TICKS = [-np.pi, -0.5*np.pi, 0, 0.5*np.pi, np.pi]
PHASE_LBL = [r'$-\pi$', r'$-\pi/2$', r'$0$', r'$\pi/2$', r'$\pi$']
BOUND_COEF = np.array([1., 1., 1., 1.])

def tabular_data(fname, proj):
    """ Tabulated amplitude for a Dalitz variables """
    if proj == 'AC':
        _, data, limits, titles = dt.parse_dtbl(fname)
        abmin, abmax = limits['mAB']
        bcmin, bcmax = limits['mBC']
        lim_list = np.array([bcmin, bcmax, abmin, abmax])
        xtitle = r'$'+titles['mBC']+'$'
        ytitle = r'$'+titles['mAB']+'$'
    else:
        data, _, limits, titles = dt.parse_dtbl(fname)
        abmin, abmax = limits['mAB']
        acmin, acmax = limits['mAC']
        lim_list = np.array([acmin, acmax, abmin, abmax])
        xtitle = r'$'+titles['mAC']+'$'
        ytitle = r'$'+titles['mAB']+'$'
    return data, lim_list, xtitle, ytitle

def plot_real(data, lim_list, xtitle, ytitle, num=None):
    """ Real part of amplitude model """
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    limit = float(10**(int(np.log10(np.absolute(data).max())) + 1))
    plt.imshow(data.T, cmap=CMAPS['reim'], origin='lower', norm=CNORM['reim'],
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
    # data[np.absolute(data) > 1] = 0
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    limit = float(10**(int(np.log10(np.absolute(data).max())) + 1))
    plt.imshow(data.T, cmap=CMAPS['reim'], origin='lower', norm=CNORM['reim'],
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
    plt.imshow(data.T, cmap=CMAPS['phase'], origin='lower', aspect='auto', extent=lim_list,
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
    plt.imshow(data.T, cmap=CMAPS['phase'], origin='lower', aspect='auto', extent=lim_list,
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
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    plt.imshow(data.T, cmap=CMAPS['p'], origin='lower', norm=CNORM['p'],
               aspect='auto', extent=lim_list, interpolation=INTRPL)
    cbar = plt.colorbar(pad=0.02)
    cbar.ax.tick_params(labelsize=18)
    plt.ylabel(ytitle, fontsize=LBL_SIZE)
    plt.xlabel(xtitle, fontsize=LBL_SIZE)
    plt.axis(BOUND_COEF*lim_list)
    plt.subplots_adjust(**PADS)
    return fig

def plot_mbc(data, limits, mbclo, mbchi, mablo, mabhi, col='b-', num=None):
    """ Project Dalitz distribution """
    data = dt.rect_subrange(data, [mbclo, mbchi, mablo, mabhi], limits)
    xsize, ysize = np.shape(data)
    X = np.linspace(mbclo, mbchi, xsize)
    Y = np.sum(data.T, axis=1) / np.sum(data)
    fig = plt.figure(num=num, figsize=FSIZE, dpi=DPI)
    plt.plot(np.sqrt(X), Y, col)

def save_eps(label, cmd, pdi=DPI):
    """ eps file """
    plt.savefig('pics/' + cmd + '_' + label + '.eps', format='eps', dpi=pdi)
    plt.savefig('pics/png/' + cmd + '_' + label + '.png', format='png', dpi=pdi)

def make_plot():
    """ Main driver """
    plst.general_settings(FONT_SIZE)
    proj = 'AC'
    cmd = sys.argv[1]
    fname = "tbl_kuz_bdpp.txt" if len(sys.argv) == 2 else sys.argv[2]
    label = fname.split('.')[0]
    data, lim_list, xtitle, ytitle = tabular_data(fname, proj)
    if cmd == 'mbc':
        plot_mbc(data['r'], lim_list, lim_list[0], 10, lim_list[2], lim_list[3], 'b-', 1)
        plot_mbc(data['r'], lim_list, lim_list[0], 10, 4, lim_list[3], 'r-', 1)
        plt.show()
        return
    if cmd == 'delt':
        plot_delta(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'real':
        plot_real(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'imag':
        plot_imag(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'phi':
        plot_phi(data[cmd], lim_list, xtitle, ytitle)
    elif cmd == 'p':
        plot_p(data['r'], lim_list, xtitle, ytitle)
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
        plt.show()
        return
    else:
        print "Wrong input!"
        print "Usage: python scatter_dalitz.py [plot_name] [data_file]"
    save_eps(label, cmd, 200)
    plt.show()

if __name__ == "__main__":
    make_plot()
