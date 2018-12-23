
testinput = """#1 @ 1,3: 4x4
#2 @ 3,1: 4x4
#3 @ 5,5: 2x2"""
lines = [line.strip() for line in open('../input/input_day3.txt')]
# lines = [line.strip() for line in testinput.split("\n")]

import re
import numpy as np

def parseline(line):
    pattern = re.compile(r"\d+")    
    result = pattern.findall(line)
    result = [int(x) for x in result]
    return result


lines = [line.strip() for line in open('input_day3.txt')]
fabric = np.zeros((1000,1000))
for line in lines:
    idnum, startx, starty, width, height = parseline(line)
    fabric[startx:startx+width,starty:starty+height] += 1
double = fabric > 1
print(double.sum())

for line in lines:
    idnum, startx, starty, width, height = parseline(line)
    cutout = fabric[startx:startx+width,starty:starty+height]
    if cutout.sum() == width*height:
        print(idnum)