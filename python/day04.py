from collections import namedtuple
from collections import Counter

Point = namedtuple('Point', ['name', 'loc'])

def manhattan_distance(pta, ptb):
    return abs(pta[0]-ptb[0]) + abs(pta[1]-ptb[1])
coordinates = list()
letters = 'abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+ABCDEFGHIJKLMNOP'

for index, line in enumerate(open('input_day6.txt')):
    tup = [int(x) for x in line.split(',')]
    coordinates.append(Point(letters[index], tup))

def get_closest(coordinates, pt):
    distances = list() # (dist, char)
    for p in coordinates:
        distances.append((manhattan_distance(p.loc, pt), p.name))
    distances.sort()
    if distances[0][0] == distances[1][0]:
        return '.'
    else:
        return distances[0][1]

def extends_to_infinite(pt1, coordinates):
    minx, miny, maxx, maxy = 0,0,0,0
    has1, has2, has3, has4 = False, False, False, False
    for pt in coordinates:
        difx = pt1[0]-pt.loc[0]
        dify = pt1[1]-pt.loc[1]
        if difx > 0 and abs(difx) > abs(dify):
            has1 = True
        if difx < 0 and abs(difx) > abs(dify): 
            has2 = True
        if difx > 0 and abs(difx) < abs(dify):
            has3 = True
        if difx < 0 and abs(difx) < abs(dify):
            has4 = True
    return not (has1 and has2 and has3 and has4)

def get_closest_dict(minrange, maxrange):
    closest = dict()
    for x in range(minrange, maxrange):
        for y in range(minrange, maxrange):
            pt = (x,y)
            closest[pt] = get_closest(coordinates, pt)
    return closest

maxval = max([max(pt.loc) for pt in coordinates])           
# print("Max val: %d" % maxval)
closest1 = get_closest_dict(0,400)        
closest2 = get_closest_dict(-100, 500)        



counter1 = Counter(closest1.values())
counter2 = Counter(closest2.values())

maxfound = 0
for key in counter1:
    if key == '.':
        continue
    if counter1[key] == counter2[key]:
        print(key + " has " + str(counter1[key]))
        maxfound = max(counter1[key], maxfound)
print(maxfound)




def neighbors8(point): 
    "The eight neighboring squares."
    x, y = point 
    return ((x-1, y-1), (x, y-1), (x+1, y-1),
            (x-1, y),             (x+1, y),
            (x-1, y+1), (x, y+1), (x+1, y+1))
coordinates = list()

for index, line in enumerate(open('input_day6.txt')):
# for index, line in enumerate(open('untitled.txt')):
    tup = [int(x) for x in line.split(',')]
    coordinates.append(Point(letters[index], tup))

def calc_total_dist(point):
    distances = list()
    for p in coordinates:
        distances.append(manhattan_distance(p.loc, point))
    return sum(distances)

pos_dist_dict = dict()
toexpand = set()
for x in range(400):
    for y in range(400):
        toexpand.add((x,y))
MAXALLOWED = 10000

def expand(pos):
    for n in neighbors8(pos):
        if n in pos_dist_dict:
            continue
        total_dist = calc_total_dist(n)
        pos_dist_dict[n]= total_dist
        if total_dist < MAXALLOWED:
            toexpand.add(n)
    
while len(toexpand) > 0:
    p = toexpand.pop()
    expand(p)



acceptable = 0
for key in pos_dist_dict:
    if pos_dist_dict[key] < MAXALLOWED:
        acceptable += 1
print(acceptable)



from collections import defaultdict

distances_to_coordinates = defaultdict(list)
for coordinate in coordinates:
    print(coordinate)
    for difx in range(-1001, 1001):
        for dify in range(-1001, 1001):
            if difx + dify < 1000:
                distances_to_coordinates[(difx+coordinate.loc[0], dify+coordinate.loc[1])].append(difx+dify)


reach_to_all = [distances_to_coordinates[x] for x in distances_to_coordinates if len(distances_to_coordinates[x]) == len(coordinates)]                    
short_to_all = [x for x in reach_to_all if sum(x) < 10000]
print(len(short_to_all))
