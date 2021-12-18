## Aaron Ciminelli
## CS-210-T2586 Programming Languages 21EW2
## Bary Pollack Ph.D.
## 12/12/2021 


import re
import string
import collections

def Items(): 
    with open('Inputfile.txt') as fp: # opens input file, reads and lists items sold 
        counts = collections.Counter(line.strip() for line in fp)
    for key in counts:
        print('%s %d' % (key, counts[key]))

def SpecificItem(v):
    v = v.capitalize() # user does not have to capitalize letter 
    with open('Inputfile.txt') as fp: # opens input file, reads and reads specific item user entered 
        data = fp.read()
        occurences = data.count(v)
        return occurences

def Histogram():
    with open('frequency.dat', "w") as wp:   # counts frequency of  items purchased 
        with open('Inputfile.txt') as fp: # opens input file, reads items purchaced and counts frequency of items and writes without repeating the same item 
            counts = collections.Counter(line.strip() for line in fp)
        for key in counts:
            wp.write('%s %d\n' % (key, counts[key]))
    if wp.closed:
        print('Histogram Created. Frequency of purchased items will be represented by a "|"')

## Aaron Ciminelli
## CS-210-T2586 Programming Languages 21EW2
## Bary Pollack Ph.D.
## 12/12/2021 

# commenting out unnecessary code
#def printsomething():
    #print("Hello from python!")

#def PrintMe(v):
    #print("You sent me: " + v)
    #return 100;

#def SquareValue(v):
    #return v * v8
