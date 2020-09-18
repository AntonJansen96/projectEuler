D = {'2':1,'3':2,'4':3,'5':4,'6':5,'7':6,'8':7,'9':8,'T':9,'J':10,'Q':11,'K':12,'A':13}

def highcard(p1,p2): #Ambigous shit zelf uitzoeken
	mem1 = mem2 = 0
	for i in D:
		if i in p1 and D[i] > mem1:
			mem1 = D[i]
		if i in p2 and D[i] > mem2:
			mem2 = D[i]
	if mem1 > mem2:
		return 'p1'
	if mem1 < mem2:
		return 'p2'
	if mem1 == mem2:
		print(p1,p2,"ambiguous!")
		return False

def onepair(p1,p2): #GOOD
	mem1 = mem2 = 0
	for i in D:
		if p1.count(i) == 2 and D[i] > mem1:
			mem1 = D[i]
		if p2.count(i) == 2 and D[i] > mem2:
			mem2 = D[i]			
	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False

def twopairs(p1,p2): #GOOD
	mem1 = mem2 = 0
	for i in D:
		for j in D:
			if i != j:
				if p1.count(i) == 2 and p1.count(j) == 2:
					if D[i] > D[j]:
						mem1 = D[i]
					else:
						mem1 = D[j]
				if p2.count(i) == 2 and p2.count(j) == 2:
					if D[i] > D[j]:
						mem2 = D[i]
					else:
						mem2 = D[j]
	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False

def threeofakind(p1,p2): #GOOD
	mem1 = mem2 = 0
	for i in D:
		if p1.count(i) == 3 and D[i] > mem1:
			mem1 = D[i]
		if p2.count(i) == 3 and D[i] > mem2:
			mem2 = D[i]			
	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False	

def straight(p1,p2): #GOOD
	mem1 = mem2 = count = 0
	for i in ['2','3','4','5','6','7','8','9','T','J','Q','K','A']:
		if i in p1:
			count += 1
		else:
			count = 0
		
		if count == 5:
			mem1 = D[i]
			break
	count = 0
	for i in ['2','3','4','5','6','7','8','9','T','J','Q','K','A']:
		if i in p2:
			count += 1
		else:
			count = 0
		if count == 5:
			mem2 = [i]
			break
	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False

def flush(p1,p2): #GOOD
	mem1 = mem2 = 0
	for i in ['C','D','H','S']:
		if p1.count(i) == 5:
			mem1 = 1
		if p2.count(i) == 5:
			mem2 = 1

	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False

def fullhouse(p1,p2): #GOOD
	mem1 = mem2 = 0
	for i in D:
		for j in D:
			if i != j:
				if p1.count(i) == 3 and p1.count(j) == 2:
					mem1 = D[i]
				if p2.count(i) == 3 and p2.count(j) == 2:
					mem2 = D[i]
	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False

def fourofakind(p1,p2): #GOOD
	mem1 = mem2 = 0
	for i in D:
		if p1.count(i) == 4 and D[i] > mem1:
			mem1 = D[i]
		if p2.count(i) == 4 and D[i] > mem2:
			mem2 = D[i]			
	if mem1 > mem2:
		return 'p1'
	elif mem1 < mem2:
		return 'p2'
	else:
		return False	

#Already checked the flushes:
#there are no straight_flushes, royal_flushes.

with open("pokerhands") as f:
    content = f.readlines()
pokerlist = [x.strip() for x in content]

wins = []

for i in xrange(0,len(pokerlist)):

	hand = pokerlist[i]

	player1 = hand[:14]
	player2 = hand[15:]

	if fourofakind(player1,player2) != False:
		wins.append(fourofakind(player1,player2))
	elif fullhouse(player1,player2) != False:
		wins.append(fullhouse(player1,player2))
	elif flush(player1,player2) != False:
		wins.append(flush(player1,player2))
	elif straight(player1,player2) != False:
		wins.append(straight(player1,player2))
	elif threeofakind(player1,player2) != False:
		wins.append(threeofakind(player1,player2))
	elif twopairs(player1,player2) != False:
		wins.append(twopairs(player1,player2))
	elif onepair(player1,player2) != False:
		wins.append(onepair(player1,player2))
	elif highcard(player1,player2) != False:
		wins.append(highcard(player1,player2))

print(wins.count('p1'))

#Solved (376) Took 2.5 hrs to do