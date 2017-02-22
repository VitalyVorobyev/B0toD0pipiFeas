""" pyplot style setting """

import matplotlib.pyplot as plt

def general_settings(font_size=26):
    """ Clean """
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')
    plt.rc('font', size=font_size)
    plt.style.use('seaborn-white')

def set_ticks():
    """ Ticks """
    # ticks and grid
    # plt.gca().grid(which='minor', linestyle=':')
    # plt.gca().grid(which='major')
    # major_ticks = np.arange(-1, 1.01, 0.5)
    # minor_ticks = np.arange(-1.25, bound+0.1, 0.125)
    plt.gca().tick_params(axis='both', which='major', direction='out', width=1, size=4)
    plt.gca().tick_params(axis='both', which='minor', direction='in', width=1, size=2)
    # plt.gca().set_xticks(minor_ticks, minor=True)
    # plt.gca().set_xticks(major_ticks)
    # plt.gca().set_yticks(minor_ticks, minor=True)
    # plt.gca().set_yticks(major_ticks)
    # plt.savefig('pics/cs_' + title + '.eps', format='eps', dpi=150)
