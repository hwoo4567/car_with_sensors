from itertools import permutations

def dir_changed(now, next):
    r = "neswn"
    
    if r.find(now + next) != -1:
        return "r90"
    elif r[::-1].find(now + next) != -1:
        return "l90"
    else:
        return None

def add_direction(lst):
    result = []
    
    for idx, item in enumerate(lst):
        result.append(item)
        try:
            next = lst[idx + 1]
            dir = dir_changed(item, next)
            if dir is not None:
                result.append(dir)

        except IndexError:
            break

    return result

def getPaths(start_pos, end_pos):
    move = end_pos[0] - start_pos[0], end_pos[1] - start_pos[1]

    path = []
    
    if move[0] > 0:  # x
        path.extend("e" * move[0])
    elif move[0] < 0:
        path.extend("w" * -move[0])
        
    if move[1] > 0:  # y
        path.extend("n" * move[1])
    elif move[1] < 0:
        path.extend("s" * -move[1])

    all_paths = list(set(  # 중복 제거
            permutations(path, len(path))))

    for i, lis in enumerate(all_paths):
        all_paths[i] = add_direction(lis)

    sorted_paths = sorted(all_paths, key=len)
    return sorted_paths

def toPos(start_pos, path):
    x, y = start_pos
    result = [(x, y)]
    
    for dir in path:
        if dir == "n":
            result.append((x, y + 1))
        elif dir == "e":
            result.append((x + 1, y))
        elif dir == "s":
            result.append((x, y - 1))
        elif dir == "w":
            result.append((x - 1, y))
        else:  # l90 or r90
            result.append(dir)
            continue
        
        x, y = result[-1]
    
    return result


