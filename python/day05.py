inputstring = "dabAcCaCBAcCcaDA"

def keep_removing(inputstring): 
    while True:
        willkeep = [True for _ in inputstring]
        index = 0
        while index < len(inputstring)-1:
            ch1, ch2 = inputstring[index], inputstring[index+1]
            if ch1.lower() == ch2.lower() and ch1 != ch2:
                # same char, different polarity
                willkeep[index] = False
                willkeep[index+1] = False
                index += 2
                continue
            index += 1
            
        if all(willkeep):
            return inputstring
        else:
            newstring = str()
            for char, keep in zip(inputstring, willkeep):
                if keep:
                    newstring += char
            inputstring = newstring
    return inputstring
        
assert(len(keep_removing('aA'))==0)
assert(len(keep_removing('abBA'))==0)
assert(len(keep_removing('aabAAB'))==6)
assert(len(keep_removing('dabAcCaCBAcCcaDA'))==10)

# Part 1
with open('../input/input_day5.txt') as f:
    inputstring = f.readline()
    inputstring = inputstring.strip()
    print("Done reading")
    assert(len(keep_removing(inputstring))==11042)
    
# Part 2
with open('../input/input_day5.txt') as f:
    inputstring = f.readline()
    inputstring = inputstring.strip()

possiblelengths = list()
for testchar in set(inputstring.lower()):
    totest = [char for char in inputstring if char.lower() != testchar]
    possiblelengths.append(len(keep_removing(totest)))
print(min(possiblelengths))