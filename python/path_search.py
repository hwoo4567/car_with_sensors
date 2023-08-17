def is_valid_move(grid, x, y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[0])

def get_possible_moves(x, y):
    moves = [
        (x + 1, y), (x - 1, y),
        (x, y + 1), (x, y - 1),
        (x, y)  # Turn left
    ]
    return moves

def find_path(grid, start, end):
    visited = set()
    queue = [(start, [])]

    while queue:
        (x, y), path = queue.pop(0)

        if (x, y) == end:
            return path

        if (x, y) not in visited:
            visited.add((x, y))

            for new_x, new_y in get_possible_moves(x, y):
                if is_valid_move(grid, new_x, new_y) and (new_x, new_y) not in visited:
                    queue.append(((new_x, new_y), path + [(new_x, new_y)]))

    return None  # No path found

def find_ideal_paths(grid, start_points, end_points):
    paths = []
    
    for start, end in zip(start_points, end_points):
        path = find_path(grid, start, end)
        if path is None:
            return None  # No valid path found
        
        paths.append(path)
        grid = [[(x, y) if (x, y) != path[-1] else (None, None) for x, y in row] for row in grid]

    return paths

# Example usage (same as before)
grid = [[(0, 0), (0, 1), (0, 2)],
        [(1, 0), (1, 1), (1, 2)],
        [(2, 0), (2, 1), (2, 2)]]

start_points = [(1, 0), (2, 0), (2, 0)]
end_points = [(1, 2), (0, 0), (0, 0)]

ideal_paths = find_ideal_paths(grid, start_points, end_points)
if ideal_paths:
    for i, path in enumerate(ideal_paths):
        print(f"Dot {chr(65 + i)} path:", path)
else:
    print("No valid paths found.")
