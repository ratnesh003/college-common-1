from queue import PriorityQueue

def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def a_star(graph, start, goal):
    open_list = PriorityQueue()
    open_list.put((0, start))  
    came_from = {} 
    g_score = {start: 0}
    f_score = {start: heuristic(start, goal)}

    while not open_list.empty():
        current = open_list.get()[1]  
        
        if current == goal:
            return reconstruct_path(came_from, current)

        for neighbor in graph[current]:
            tentative_g_score = g_score[current] + graph[current][neighbor]

            if neighbor not in g_score or tentative_g_score < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g_score
                f_score[neighbor] = tentative_g_score + heuristic(neighbor, goal)
                open_list.put((f_score[neighbor], neighbor))

    return None  

def reconstruct_path(came_from, current):
    total_path = [current]
    while current in came_from:
        current = came_from[current]
        total_path.append(current)
    total_path.reverse()
    return total_path


graph = {
    (0, 0): {(0, 1): 1, (1, 0): 1},
    (0, 1): {(0, 0): 1, (1, 1): 1, (0, 2): 1},
    (1, 0): {(0, 0): 1, (1, 1): 1},
    (1, 1): {(1, 0): 1, (0, 1): 1, (1, 2): 1},
    (0, 2): {(0, 1): 1, (1, 2): 1},
    (1, 2): {(1, 1): 1, (0, 2): 1},
}

start = (0, 0)
goal = (1, 2)
path = a_star(graph, start, goal)
print("Path found by A*:", path)
