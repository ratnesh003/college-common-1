class Graph:
    def __init__(self, graph, h):
        self.graph = graph  
        self.h = h  
        self.solution_graph = {}  

    def and_or_search(self, node):
        print("Processing Node:", node)

        
        if node not in self.graph or not self.graph[node]:
            return self.h[node]

        min_cost = float('inf')
        best_child = None

        
        for child_set in self.graph[node]:
            cost = 0
            for child in child_set:
                cost += self.h.get(child, float('inf'))

            
            if cost < min_cost:
                min_cost = cost
                best_child = child_set

        
        self.h[node] = min_cost

        
        if best_child is None:
            return self.h[node]

        
        self.solution_graph[node] = best_child

        
        for child in best_child:
            self.and_or_search(child)

        return self.h[node]


graph = {
    'A': [['B', 'C'], ['D']],
    'B': [['E'], ['F']],
    'C': [['G'], ['H']],
    'D': [['I']],
    'E': [], 'F': [], 'G': [], 'H': [], 'I': []
}


h = {'A': 1, 'B': 6, 'C': 2, 'D': 12, 'E': 2, 'F': 4, 'G': 3, 'H': 5, 'I': 7}

graph_instance = Graph(graph, h)
graph_instance.and_or_search('A')
print("Solution graph:", graph_instance.solution_graph)
