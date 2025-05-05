#!/usr/bin/env python3

import random
from tqdm import tqdm
from science.euler import genperms, numperms

# suit1 = ['a1', 'a2', 'a3', 'a4', 'a5', 'a6', 'a7', 'a8', 'a9', 'a10', 'a11', 'a12', 'a13']
# suit2 = ['b1', 'b2', 'b3', 'b4', 'b5', 'b6', 'b7', 'b8', 'b9', 'b10', 'b11', 'b12', 'b13']
# suit3 = ['c1', 'c2', 'c3', 'c4', 'c5', 'c6', 'c7', 'c8', 'c9', 'c10', 'c11', 'c12', 'c13']
# suit4 = ['d1', 'd2', 'd3', 'd4', 'd5', 'd6', 'd7', 'd8', 'd9', 'd10', 'd11', 'd12', 'd13']
# deck  = suit1 + suit2 + suit3 + suit4

# Generate deck
N = 4
deck = []
for num in range(1, N + 1):
    deck += 4 * [num]
random.shuffle(deck)

count = 0
maxLengths = 0

for deck in tqdm(genperms(deck, unique=True), total=numperms(deck, unique=True)):

    maxLen = 0
    piles = {}

    for card in deck:
        
        try:
            piles[card].append(card)

            non_empty_piles = len(piles)
            if non_empty_piles > maxLen:
                maxLen = non_empty_piles

            if len(piles[card]) == 4:
                del piles[card]

        except KeyError:
            piles[card] = [card]

    maxLengths += maxLen
    count += 1

    # print(f"{maxLengths / float(count):.12f}", end='\r')
print(f"{maxLengths / float(count):.12f}")

# n = 3 -> 3.86988212  
