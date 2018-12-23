total = 0

with open('../input_day1.txt') as f:
    for line in f: 
        total += int(line)
print(total)

def find_repeating():
    total = 0
    seen = set()
    while True:
        with open('../input_day1.txt') as f:
            for line in f: 
                total += int(line)
                if total in seen: 
                    return total
                seen.add(total)
                
res = find_repeating()
print(res)