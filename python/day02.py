from collections import Counter
with_two = 0 
with_three = 0
possible_ids = [line.strip() for line in open("input_day2.txt")]
for line in possible_ids:
    line = [character for character in line.strip()]
    a = Counter(line)
    if 2 in a.values():
        with_two += 1
    if 3 in a.values():
        with_three += 1
print(with_two * with_three)

def diff_char_distance(id1, id2):
    assert len(id1) == len(id2)
    distance = 0 
    for idx in range(len(id1)):
        if id1[idx] != id2[idx]:
            distance += 1
    return distance


import itertools

for id1, id2 in itertools.combinations(possible_ids, 2):
    if diff_char_distance(id1, id2) == 1:
        common = str()
        for idx in range(len(id1)):
            if id1[idx] == id2[idx]:
                common += id1[idx]

print(common)                