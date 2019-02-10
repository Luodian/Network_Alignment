import matplotlib

matplotlib.use('Agg')
import matplotlib.pyplot as plt
import networkx as nx
import re
import random
import matplotlib.patches as mpc
import numpy as np


def readRawFile(filename, Raw_edge):
    file = open(filename)
    print("Name of file: ", file.name)
    line = file.readline()
    line_arr = re.sub("[^\w]]", " ", line).split()
    n = line_arr[0]
    for line in file.readlines():
        line_arr = re.sub("[^\w]]", " ", line).split()
        int_arr = []
        for element in line_arr:
            int_arr.append(int(element))

        u = int_arr[0]
        v = int_arr[1]
        if (u, v) not in Raw_edge:
            Raw_edge.append((u, v))
    return n


def readBccFile(filename, Bcc_matrix, cut_arr):
    file = open(filename)
    print("Name of file: ", file.name)
    line = file.readline()
    cut_num = int(line[0])
    line = file.readline()
    line_arr = re.sub("[^\w]]", " ", line).split()
    for element in line_arr:
        cut_arr.append(int(element))

    line = file.readline()
    bcc_num = int(line)
    for i in range(0, bcc_num):
        bcc_array = []
        line = file.readline()
        int_arr = re.sub("[^\w]", " ", line).split()
        for element in int_arr:
            bcc_array.append(int(element))
        Bcc_matrix.append(bcc_array)


def plot(label):
    # set default color
    # colors = ['brown', 'r', 'b', 'oldlace', 'yellowgreen', 'teal', 'tomato', 'palegreen', 'cornsilk', 'pink', 'crimson', 'darkgreen', 'hotpink', 'gray', 'green', 'gold', 'beige', 'bisque']
    colors = [(0., 1, 1), (0.05, 1, 1), (0.11, 0, 0), (0.66, 1, 1), (0.89, 1, 1), (1, 0.5, 0.5), (0, 1, 1),
              (0.05, 1, 1), (0.11, 0, 0), (0.375, 1, 1), (0.64, 1, 1), (0.91, 0, 0), (1, 0, 0), (0., 1, 1),
              (0.05, 1, 1),
              (0.11, 1, 1),
              (0.34, 1, 1),
              (0.65, 0, 0),
              (1, 0, 0)]

    Raw_edge = []
    n = readRawFile("/Users/luodian/Desktop/network_alignment/graphs/{}.txt".format(label), Raw_edge)

    n = int(n)
    all_node = range(0, n)

    G = nx.DiGraph()
    G.add_edges_from(Raw_edge)
    G.add_nodes_from(all_node)
    pos = nx.spring_layout(G)
    nx.draw_networkx_edges(G, pos, edge_color='blue', arrows=True, arrowstyle='->', arrowsize=20, alpha=1, width=0.8)
    nx.draw_networkx_labels(G, pos)
    # print type(node_blue)
    # nx.draw_networkx_edges(G, pos = nx.spring_layout(G), edgelist=[(1,2)], edge_color = 'blue')
    nx.draw_networkx_nodes(G, pos, nodelist=all_node, node_color='orange')
    font = {'color': 'k',
            'fontweight': 'bold',
            'fontsize': 14}
    plt.title("Graph of {}".format(label), font)
    # plt.annotate('The cut vertexs', (1, 1.15))
    # plt.plot([0.95], [1.1666], color='salmon', marker='o', markersize=15)
    plt.axis('off')
    plt.cool()
    plt.savefig('{}_digraph.png'.format(label), dpi=200)
    plt.show()


def vis_histogram(label):
    data = np.loadtxt("{}_out.txt".format(label))
    # print(data.shape)
    # last_item = int(data[data.size - 1])
    bins = np.arange(0, 22, 1)  # 修改直方柱宽度修改“1”的值
    plt.hist(data, bins=bins, edgecolor='black')
    plt.title("Histogram with {} nodes".format(label))
    plt.savefig("{}_hist.png".format(label), dpi=100)
    plt.show()


if __name__ == "__main__":
    plot("n100")
    # vis_histogram("s1")
