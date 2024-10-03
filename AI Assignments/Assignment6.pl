edge(a, b).
edge(a, c).
edge(b, d).
edge(b, e).
edge(c, f).
edge(c, g).

dfs(Start, Goal, Path) :-
    dfs_helper(Start, Goal, [Start], Path).

dfs_helper(Goal, Goal, Path, Path). 
dfs_helper(Node, Goal, Visited, Path) :-
    edge(Node, Next),               
    \+ member(Next, Visited),        
    dfs_helper(Next, Goal, [Next|Visited], Path).


bfs(Start, Goal, Path) :-
    bfs_helper([[Start]], Goal, Path).

bfs_helper([[Goal|Rest]|_], Goal, Path) :- 
    reverse([Goal|Rest], Path).
bfs_helper([CurrentPath|OtherPaths], Goal, Path) :-
    CurrentPath = [CurrentNode|_],
    findall([NextNode|CurrentPath],
            (edge(CurrentNode, NextNode), \+ member(NextNode, CurrentPath)),
            NewPaths),
    append(OtherPaths, NewPaths, UpdatedPaths),
    bfs_helper(UpdatedPaths, Goal, Path).