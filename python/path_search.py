import numpy as np

def toPath(vec2):
    result = []
    if vec2[0] > 0:
        result.extend(["e"] * vec2[0])
    if vec2[0] < 0:
        result.extend(["w"] * vec2[0])
    if vec2[1] > 0:
        result.extend(["n"] * vec2[0])
    if vec2[1] < 0:
        result.extend(["s"] * vec2[0])
        
    return result


start = np.array([1, 1])
end = np.array([3, 4])

vector = end - start

print(toPath(vector))
