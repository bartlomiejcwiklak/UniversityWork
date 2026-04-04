import random
import math
from collections import deque
import heapq
import matplotlib.pyplot as plt

# create a set of cities with random coordinates
def generate_cities(n, coord_range=(-100, 100)):
    # generate n cities as (x, y) points randomly within coord_range
    cities = []
    for i in range(n):
        x = random.uniform(coord_range[0], coord_range[1])
        y = random.uniform(coord_range[0], coord_range[1])
        cities.append((x, y))
    return cities

# helper function to compute euclidean distance
def euclidean_distance(a, b):
    return math.hypot(a[0] - b[0], a[1] - b[1])

# represent the map as a weighted graph
def build_full_graph(cities):
    # build a fully connected graph (complete graph) where edge weights are distances
    graph = {i: [] for i in range(len(cities))}
    for i in range(len(cities)):
        for j in range(i + 1, len(cities)):
            dist = euclidean_distance(cities[i], cities[j])
            graph[i].append((j, dist))
            graph[j].append((i, dist))
    return graph

def build_partial_graph(cities, edge_probability=0.8):
    # same as above but with a probability
    graph = {i: [] for i in range(len(cities))}
    for i in range(len(cities)):
        for j in range(i + 1, len(cities)):
            if random.random() < edge_probability:
                dist = euclidean_distance(cities[i], cities[j])
                graph[i].append((j, dist))
                graph[j].append((i, dist))
    return graph

# helper to get the distance between two connected nodes
def get_distance(u, v, graph):
    for neighbor, dist in graph[u]:
        if neighbor == v:
            return dist
    return float('inf')  # if no direct edge ..

# helper to plot the graph structure
def plot_graph(cities, graph, title="Graph"):
    # plot cities and edges of the grapb
    x_coords, y_coords = zip(*cities)
    plt.figure()
    plt.title(title)
    # cities
    plt.scatter(x_coords, y_coords)
    for idx, (x, y) in enumerate(cities):
        plt.text(x, y, str(idx))
    # edges
    seen = set()
    for u, edges in graph.items():
        for v, w in edges:
            if (v, u) not in seen:
                x1, y1 = cities[u]
                x2, y2 = cities[v]
                plt.plot([x1, x2], [y1, y2], 'k-', linewidth=0.5)
                # annotate weight at midpoint
                mx, my = (x1 + x2) / 2, (y1 + y2) / 2
                plt.text(mx, my, f"{w:.1f}", fontsize=6)
                seen.add((u, v))
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.show()

# helper to plot any path
def plot_path(cities, path, title="Path"):
    x_coords, y_coords = zip(*cities)
    plt.figure()
    plt.title(title)
    # plot cities
    plt.scatter(x_coords, y_coords)
    for idx, (x, y) in enumerate(cities):
        plt.text(x, y, str(idx))
    # plot path edges
    for i in range(len(path) - 1):
        u, v = path[i], path[i+1]
        x1, y1 = cities[u]
        x2, y2 = cities[v]
        plt.plot([x1, x2], [y1, y2], 'r-')
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.show()

# depth-first search over all permutations of cities
def tsp_dfs(graph, start):
    n = len(graph)
    best_cost = float('inf')
    best_path = []

    def dfs(path, cost):
        nonlocal best_cost, best_path # makes these variables referencable outside dfs()
        # if we've visited all cities, complete the tour
        if len(path) == n:
            cost += get_distance(path[-1], start, graph)
            if cost < best_cost:
                best_cost = cost
                best_path = path + [start]
            return

        # branch-and-bound pruning
        if cost >= best_cost:
            return

        for neighbor, dist in graph[path[-1]]:
            if neighbor not in path:
                dfs(path + [neighbor], cost + dist)

    dfs([start], 0)
    return best_path, best_cost

# breadth-first search over state tree
def tsp_bfs(graph, start):
    n = len(graph)
    best_cost = float('inf')
    best_path = []
    queue = deque([([start], 0)])

    while queue:
        path, cost = queue.popleft()
        # if complete, update best
        if len(path) == n:
            cost_full = cost + get_distance(path[-1], start, graph)
            if cost_full < best_cost:
                best_cost = cost_full
                best_path = path + [start]
        else:
            for neighbor, dist in graph[path[-1]]:
                if neighbor not in path:
                    queue.append((path + [neighbor], cost + dist))

    return best_path, best_cost

# build a minimum spanning tree using prims algorithm. returns adjacency list of the mst
def prim_mst(graph, start):
    n = len(graph)
    visited = {start}
    mst_adj = {i: [] for i in range(n)}
    # min-heap of edges (cost, from, to)
    edges = [(dist, start, neighbor) for neighbor, dist in graph[start]]
    heapq.heapify(edges)

    while edges and len(visited) < n:
        cost, u, v = heapq.heappop(edges)
        if v in visited:
            continue
        visited.add(v)
        mst_adj[u].append(v)
        mst_adj[v].append(u)
        for to_next, dist in graph[v]:
            if to_next not in visited:
                heapq.heappush(edges, (dist, v, to_next))

    return mst_adj

def preorder_traversal(tree, node, visited=None, tour=None):
# preorder dfs of mst tree to generate an approximation
    if visited is None:
        visited = set()
    if tour is None:
        tour = []
    visited.add(node)
    tour.append(node)
    for neighbor in tree[node]:
        if neighbor not in visited:
            preorder_traversal(tree, neighbor, visited, tour)
    return tour

def tsp_mst_approx(graph, start):
# approximate by walking around mst in preorder
    tree = prim_mst(graph, start)
    tour = preorder_traversal(tree, start)
    tour.append(start)
    # compute total cost
    cost = sum(get_distance(tour[i], tour[i+1], graph) for i in range(len(tour)-1))
    return tour, cost

# greedy tsp approximation
def tsp_greedy(graph, start):
    n = len(graph)
    path = [start]
    visited = {start}
    cost = 0
    current = start

    while len(path) < n:
        # find closest unvisited neighbor
        nearest, dist = min(
            ((neighbor, d) for neighbor, d in graph[current] if neighbor not in visited),
            key=lambda x: x[1],
            default=(None, None)
        )
        if nearest is None:
            break
        path.append(nearest)
        visited.add(nearest)
        cost += dist
        current = nearest

    # return to start
    cost += get_distance(current, start, graph)
    path.append(start)
    return path, cost

# bidirectional search for shortest path between two cities
def bidirectional_search(graph, start, goal):
    if start == goal:
        return [start], 0

    # initialize frontiers and visited maps: node -> path
    front_f = {start: [start]}
    front_b = {goal: [goal]}
    queue_f = deque([start])
    queue_b = deque([goal])

    while queue_f and queue_b:
        # expand from the side with fewer nodes
        if len(queue_f) <= len(queue_b):
            current = queue_f.popleft()
            for neighbor, _ in graph[current]:
                if neighbor not in front_f:
                    front_f[neighbor] = front_f[current] + [neighbor]
                    queue_f.append(neighbor)
                    if neighbor in front_b:
                        # paths meet
                        path_f = front_f[neighbor]
                        path_b = front_b[neighbor]
                        full_path = path_f + path_b[-2::-1]  # skip duplicate
                        total_cost = sum(
                            get_distance(full_path[i], full_path[i+1], graph)
                            for i in range(len(full_path)-1)
                        )
                        return full_path, total_cost
        else:
            current = queue_b.popleft()
            for neighbor, _ in graph[current]:
                if neighbor not in front_b:
                    front_b[neighbor] = front_b[current] + [neighbor]
                    queue_b.append(neighbor)
                    if neighbor in front_f:
                        path_f = front_f[neighbor]
                        path_b = front_b[neighbor]
                        full_path = path_f + path_b[-2::-1]
                        total_cost = sum(
                            get_distance(full_path[i], full_path[i+1], graph)
                            for i in range(len(full_path)-1)
                        )
                        return full_path, total_cost

    return None, float('inf')

def main():
    # Seed for reproducibility (optional)
    random.seed()

    # part 1: generate cities
    n = int(input("Number of cities to generate? "))
    cities = generate_cities(n)

    # part 2: build graph
    choice = input("Choose roads scenario: [a] full, [b] ~80% edges (default a): ").strip().lower()
    if choice == 'b':
        graph = build_partial_graph(cities)
    else:
        graph = build_full_graph(cities)

    # display said graph
    print("\n--- City coordinates ---")
    for i, (x, y) in enumerate(cities):
        print(f" {i}: ({x:.1f}, {y:.1f})")

    print("\n--- Graph (adjacency list) ---")
    for u, edges in graph.items():
        print(f" {u}:", ", ".join(f"{v}(d={d:.1f})" for v, d in edges))

    plot_graph(cities, graph, title="Road Network")

    # part 3: solving tsp
    start = int(input(f"Starting city for TSP (0..{n-1}): "))

    # dfs full search
    path_dfs, cost_dfs = tsp_dfs(graph, start)
    print("\n[DFS full search]")
    print(" Path:", path_dfs)
    print(" Cost: {:.2f}".format(cost_dfs))
    plot_path(cities, path_dfs, title="TSP DFS Tour")

    # bfs full search
    path_bfs, cost_bfs = tsp_bfs(graph, start)
    print("\n[BFS full search]")
    print(" Path:", path_bfs)
    print(" Cost: {:.2f}".format(cost_bfs))
    plot_path(cities, path_bfs, title="TSP BFS Tour")

    # mst approximation
    path_mst, cost_mst = tsp_mst_approx(graph, start)
    print("\n[MST approximation]")
    print(" Path:", path_mst)
    print(" Cost: {:.2f}".format(cost_mst))
    plot_path(cities, path_mst, title="TSP MST Approximation")

    # greedy approximation
    path_greedy, cost_greedy = tsp_greedy(graph, start)
    print("\n[Greedy approximation]")
    print(" Path:", path_greedy)
    print(" Cost: {:.2f}".format(cost_greedy))
    plot_path(cities, path_greedy, title="TSP Greedy Approximation")

    # part 4: automatic selection of two non-connected cities
    try:
        # find first non-adjacent pair
        u, v = next(
            (i, j)
            for i in range(n)
            for j in range(i + 1, n)
            if all(neigh != j for neigh, _ in graph[i])
        )
        print(f"\nSelected cities for bidirectional search: {u} and {v}")
        path_bi, cost_bi = bidirectional_search(graph, u, v)
        print(f"Shortest path between {u} and {v}: {path_bi}")
        print(f"Cost: {cost_bi:.2f}")
        plot_path(cities, path_bi, title=f"Shortest path {u}->{v}")
    except StopIteration:
        print("\nAll city pairs are directly connected; cannot find a non-adjacent pair.")

if __name__ == "__main__":
    main()