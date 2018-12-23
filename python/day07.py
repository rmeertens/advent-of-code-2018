dependencies = list()
all_letters = set()
with open('input_day7.txt') as f:
    for line in f:
        _, first, second = a = [char for char in line if char.isupper()]
        dependencies.append((first, second))
        all_letters.add(first)
        all_letters.add(second)
        
def get_dependencys(letter, deps):
    dofirst = list()
    for first, then in deps:
        if then == letter:
            dofirst.extend(get_dependencys(first, deps))
            dofirst.append(first)
    return dofirst

    
letter_prio = list()    
for letter in all_letters:
    letter_prio.append((get_dependencys(letter, dependencies), letter))
    
letter_prio.sort()
# s = str()
# while len(letter_prio) > 0:
#     deps, letter = letter_prio.pop(0)
#     assert(len(deps)==0)
#     s += letter
#     for rem, origletter in letter_prio:
#         while letter in rem:
#             rem.remove(letter)
#     letter_prio.sort()
# print(s)

alphabet = "abcdefghijklmnopqrstuvwxyz".upper()

second = 0
NUM_WORKERS = 5
TIME_PENALTY = 60
remaining_seconds = [(0,'*') for _ in range(NUM_WORKERS)]
seconddone_letter = list()
while len(letter_prio) > 0 or any([x >1 for x, _ in remaining_seconds]):
    second += 1
    remaining_seconds = [(x-1,y) for x,y in remaining_seconds]
    for index_seconds in range(NUM_WORKERS):
        rem, lettersolved = remaining_seconds[index_seconds]
        if rem<=0:
            # remove the letter that just got resolved
            for rem, _ in letter_prio:
                while lettersolved in rem:
                    rem.remove(lettersolved)
                    
            letter_prio.sort()
            if len(letter_prio) == 0:
                continue
            deps, letter = letter_prio[0]
            if (len(deps)==0):
                deps, letter = letter_prio.pop(0)
                assert(letter in alphabet)
                remaining_seconds[index_seconds] = (TIME_PENALTY + alphabet.index(letter)+1, letter)
            

# print(s)
print(second)


for a, b in letter_prio:
    print(a)



letter = 'A'
letter_prio = [(['A'], 'B')]
for rem, _ in letter_prio:
    if letter in rem:
        print('rem before ' + str(rem))
        rem.remove(letter)
        print('rem after ' + str(rem))
    