import re

Edges = []
Edge_list = {}


def graphlet_count(filename):
    with open("./graphlet/{}_2node.txt".format(filename), 'w') as fp:
        fp.writelines("In graph {}, there're {} 2-node graphlets.\n".format(filename, format(len(Edges))))
        graphlets_cnt = 0
        for item in Edge_list:
            degree = len(Edge_list[item])
            graphlets_cnt += ((degree * (degree - 1)) / 2)

        fp.writelines("In graph {}, there're {} 3-node line graphlets.\n".format(filename, int(graphlets_cnt)))
        triangle_count = triangleCount(Edge_list)
        fp.writelines("In graph {}, there're {} 3-node triangle graphlets.\n".format(filename, triangle_count))


def triangleCount(graph):
    count = 0
    tringle = []
    for srcId in graph:
        srcSet = graph.get(srcId)
        for destId in srcSet:
            if (destId > srcId):
                destSet = graph.get(destId)
                for vertexId in destSet:
                    if (vertexId in srcSet) and (vertexId > destId):
                        count += 1
                        tringle.append((srcId, destId, vertexId))
    return count


if __name__ == "__main__":
    label = "s1"
    filename = "./graphs/{}.txt".format(label)
    file = open(filename)
    print("Name of file: ", file.name)
    line = file.readline()
    n = int(line)

    # init adjacent list
    for i in range(n):
        Edge_list[i] = list()

    for line in file.readlines():
        line_arr = re.sub("[^\w]]", " ", line).split()
        int_arr = []
        for element in line_arr:
            int_arr.append(int(element))
        u = int_arr[0]
        v = int_arr[1]
        if (u, v) not in Edges and (v, u) not in Edges:
            Edges.append((u, v))

    for item in Edges:
        u = item[0]
        v = item[1]
        if v not in Edge_list[u]:
            Edge_list[u].append(v)

        if u not in Edge_list[v]:
            Edge_list[v].append(u)

    graphlet_count(label)
