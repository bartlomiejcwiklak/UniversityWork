import random  # import random module for generating random numbers
import math  # import math module for mathematical functions
from collections import deque  # import deque for efficient queue operations (bfs)
import matplotlib.pyplot as plt  # import pyplot for plotting graphs
import numpy as np  # import numpy for numerical operations and adjacency matrix

# helper function to compute euclidean distance between two cities
def computeDistance(a, b, coords):  # define function taking two city indices and coords dict
    x1, y1 = coords[a]  # unpack x,y of city a
    x2, y2 = coords[b]  # unpack x,y of city b
    return math.hypot(x2 - x1, y2 - y1)  # return euclidean distance

# helper function to plot the road network
def plotRoadNetwork(edges, coords, title):  # define function with edge list, coords, and title
    plt.figure()  # start a new figure
    for u, v in edges:  # iterate through each road (edge)
        x1, y1 = coords[u]  # get coordinates of city u
        x2, y2 = coords[v]  # get coordinates of city v
        plt.plot([x1, x2], [y1, y2], '-', alpha=0.5)  # draw line between u and v
    xs, ys = zip(*coords.values())  # unzip all x and y values
    plt.scatter(xs, ys, c='red')  # scatter plot all cities in red
    for i, (x, y) in coords.items():  # label each city with its index
        plt.text(x, y, str(i), color='blue')  # place text at each city
    plt.title(title)  # set plot title
    plt.axis('equal')  # keep same scaling on x and y axes
    plt.show()  # display the plot

# helper function to plot a path through cities
def plotPath(path, coords, title):  # define function with path list, coords, and title
    if path is None:  # check if path is valid
        print(f"[!] {title}: no route found.")  # warn if no path found
        return  # exit function early
    plt.figure()  # start a new figure
    for i in range(len(path) - 1):  # iterate through consecutive pairs in path
        u, v = path[i], path[i + 1]  # get each pair of cities
        x1, y1 = coords[u]  # get coords for city u
        x2, y2 = coords[v]  # get coords for city v
        plt.plot([x1, x2], [y1, y2], '-o')  # draw line with circle markers
    total = sum(  # compute total path cost
        computeDistance(path[i], path[i+1], coords)
        for i in range(len(path)-1)
    )
    plt.title(f"{title} (cost={total:.2f})")  # set title with total cost
    plt.axis('equal')  # keep axes equal
    plt.show()  # display the plot

# exercise 1: generate city coordinates and road networks
numCities = 6  # number of cities to create
cityCoords = {  # dictionary comprehension for city coordinates
    i: (random.uniform(-100,100), random.uniform(-100,100))
    for i in range(numCities)
}
completeEdges = [  # list of all possible roads (complete graph)
    (i, j)
    for i in range(numCities)
    for j in range(i+1, numCities)
]
sparseEdges = [e for e in completeEdges if random.random() < 0.8]  # keep ~80% of roads randomly

plotRoadNetwork(completeEdges, cityCoords, "Exercise 1a: Complete Road Network")  # plot full road network
plotRoadNetwork(sparseEdges,   cityCoords, "Exercise 1b: Sparse (~80%) Road Network")  # plot sparse network

# exercise 2: build and display adjacency matrix for sparse graph
adjMatrix = np.zeros((numCities, numCities))  # initialize zero matrix
for u, v in sparseEdges:  # fill in distances for each existing road
    d = computeDistance(u, v, cityCoords)  # compute distance
    adjMatrix[u, v] = adjMatrix[v, u] = d  # assign symmetric values

plt.figure()  # new figure for adjacency matrix
plt.imshow(adjMatrix, interpolation='none')  # show matrix as heatmap
plt.colorbar(label="Distance")  # add colorbar
plt.title("Exercise 2: Adjacency Matrix (Sparse Graph)")  # set title
plt.show()  # display

# exercise 3a: exact tsp via bfs search
def tspByBfs(edges, coords):  # define tsp solver using bfs
    start = 0  # start city index
    bestCost, bestRoute = float('inf'), None  # initialize best cost and path
    queue = deque([([start], 0.0)])  # initialize queue with start path and cost
    while queue:  # loop until queue empties
        route, costSoFar = queue.popleft()  # get next partial route
        if len(route) == numCities:  # if visited all cities
            total = costSoFar + computeDistance(route[-1], start, coords)  # close loop
            if total < bestCost:  # check for improvement
                bestCost, bestRoute = total, route + [start]  # record best
        else:
            for nxt in range(numCities):  # try extending route
                if nxt not in route and (route[-1], nxt) in edges:  # if edge exists
                    queue.append((  # add new route to queue
                        route + [nxt],
                        costSoFar + computeDistance(route[-1], nxt, coords)
                    ))
    return bestRoute  # return best found route

# exercise 3a: exact tsp via dfs search
def tspByDfs(edges, coords):  # define tsp solver using dfs
    start = 0  # start city
    bestCost, bestRoute = float('inf'), None  # track best solution
    stack = [([start], 0.0)]  # initialize stack with start
    while stack:  # loop until stack empties
        route, costSoFar = stack.pop()  # get last partial route
        if len(route) == numCities:  # if complete route
            total = costSoFar + computeDistance(route[-1], start, coords)  # close tour
            if total < bestCost:  # update if better
                bestCost, bestRoute = total, route + [start]
        else:
            for nxt in range(numCities):  # extend route
                if nxt not in route and (route[-1], nxt) in edges:  # valid next city
                    stack.append((  # push new route
                        route + [nxt],
                        costSoFar + computeDistance(route[-1], nxt, coords)
                    ))
    return bestRoute  # return best tour

bfsRoute = tspByBfs(sparseEdges, cityCoords)  # compute tsp via bfs
plotPath(bfsRoute, cityCoords, "Exercise 3a: TSP by BFS")  # plot bfs result

dfsRoute = tspByDfs(sparseEdges, cityCoords)  # compute tsp via dfs
plotPath(dfsRoute, cityCoords, "Exercise 3a: TSP by DFS")  # plot dfs result

# exercise 3b: tsp via mst preorder approximation
def buildMst(edges, coords):  # define prim's growth of mst
    visited = {0}  # start at city 0
    mst = []  # list to hold mst edges
    while len(visited) < numCities:  # until all cities covered
        candidates = [  # collect crossing edges
            (computeDistance(u, v, coords), u, v)
            for u in visited
            for v in range(numCities)
            if v not in visited and (u, v) in edges
        ]
        if not candidates:  # no more connections
            break
        _, u, v = min(candidates)  # pick smallest edge
        visited.add(v)  # add new city
        mst.append((u, v))  # record edge
    return mst  # return mst edges

def tspByMst(edges, coords):  # build tsp tour from mst
    tree = {i: [] for i in range(numCities)}  # adjacency list
    for u, v in buildMst(edges, coords):  # fill tree
        tree[u].append(v)
        tree[v].append(u)
    tour = []  # list for preorder tour
    def dfsTree(u, parent):  # recursive dfs
        tour.append(u)  # visit city
        for w in tree[u]:  # for each neighbor
            if w != parent:  # avoid going back
                dfsTree(w, u)  # recurse
    dfsTree(0, -1)  # start dfs at city 0
    tour.append(0)  # return to start
    return tour  # return approximate tour

mstRoute = tspByMst(sparseEdges, cityCoords)  # get mst-based tour
plotPath(mstRoute, cityCoords, "Exercise 3b: TSP approx via MST")  # plot it

# exercise 3c: tsp via greedy nearest-neighbor
def tspByGreedy(edges, coords):  # define greedy heuristic
    current = 0  # start city
    unvisited = set(range(1, numCities))  # remaining cities
    route = [0]  # initialize route
    while unvisited:  # while there are cities left
        choices = [c for c in unvisited if (current, c) in edges]  # reachable
        if not choices:  # if stuck
            return None  # no solution
        nxt = min(choices, key=lambda c: computeDistance(current, c, coords))  # pick closest
        route.append(nxt)  # add to route
        unvisited.remove(nxt)  # mark visited
        current = nxt  # move to next city
    route.append(0)  # return to start
    return route  # return greedy tour

greedyRoute = tspByGreedy(sparseEdges, cityCoords)  # compute greedy tour
plotPath(greedyRoute, cityCoords, "Exercise 3c: TSP approx via Greedy")  # plot it

# exercise 4: bidirectional search for shortest path
def bidirectionalSearch(start, goal, edges, coords):  # define bi-dir search
    if start == goal:  # trivial case
        return [start]  # return single-node path
    front, back = {start}, {goal}  # frontiers from both ends
    predF, predB = {start:None}, {goal:None}  # predecessor maps
    meeting = None  # to record meeting node

    while front and back and meeting is None:  # until search finishes or meets
        newFront = set()  # next layer front
        for u in front:  # expand front frontier
            for v in range(numCities):  # check all cities
                if (u,v) in edges and v not in predF:  # valid edge and unseen
                    predF[v] = u  # set predecessor
                    newFront.add(v)  # add to new front
                    if v in predB:  # if meets back frontier
                        meeting = v  # record meeting
                        break
            if meeting: break
        front = newFront  # update front
        if meeting: break
        newBack = set()  # next layer back
        for u in back:  # expand back frontier
            for v in range(numCities):
                if (u,v) in edges and v not in predB:  # valid unseen
                    predB[v] = u  # record predecessor
                    newBack.add(v)  # add to new back
                    if v in predF:  # if meets front frontier
                        meeting = v
                        break
            if meeting: break
        back = newBack  # update back

    if meeting is None:  # if no meeting found
        return None  # graph disconnected

    # reconstruct path from start to meeting
    pathF, node = [], meeting  # forward path
    while node is not None:  # follow preds to start
        pathF.append(node)
        node = predF[node]
    # reconstruct path from meeting to goal
    pathB, node = [], predB[meeting]
    while node is not None:  # follow preds to goal
        pathB.append(node)
        node = predB[node]

    return pathF[::-1] + pathB  # combine forward and backward

shortestRoute = bidirectionalSearch(0, 1, sparseEdges, cityCoords)  # find shortest between 0 and 1
plotPath(shortestRoute, cityCoords, "Exercise 4: Bidirectional 0→1")  # plot result
