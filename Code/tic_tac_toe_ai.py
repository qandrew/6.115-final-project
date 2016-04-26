from tic_tac_toe import tic_tac_toe
import random
from copy import deepcopy

class ai_tic(tic_tac_toe):
	def __init__(self,hardness = 10,size = 4,dimension = 3,player = 'A'):
		super(ai_tic,self).__init__(size,dimension,player)
		#hardness is on a scale from 1 to 10 where 1 is easy and 10 is hard
		self.hardness = hardness
		self.init_ai_stuff()

	def init_ai_stuff(self):
		self.board = {'flat':[0 for i in xrange(self.size*self.size)],'horiz':[0 for i in xrange(self.size*self.size)],'vert':[0 for i in xrange(self.size*self.size)],}
		self.board['planar'] = [0 for i in xrange(8)]
		self.board['frontal'] = [0 for i in xrange(8)]
		self.board['sidal'] = [0 for i in xrange(8)]
		self.board['superdiag'] = [0 for i in xrange(4)]

		self.grid_eval = [0 for i in xrange(self.size**3)]
		self.grid_eval_cause = [[] for i in xrange(self.size**3)]

	def get_grid_eval(self,z,x,y):
		return self.grid_eval[z*16+x*4+y]

	def set_grid_eval(self,z,x,y,value):
		self.grid_eval[z*16+x*4+y] = value	

	def add_grid_eval(self,z,x,y,value):
		self.grid_eval[z*16+x*4+y] += value	
		# self.grid_eval_cause[z*16+x*4+y].append(cause)

	def loc_to_grid(self,loc):
		z = loc/16
		loc -= z*16
		x = loc/4
		y = loc%4
		return (z,x,y)

	def disp_grid_eval(self):
		i = 0
		print ''
		for z in xrange(4):
			for x in xrange(4):
				print self.grid_eval[i:i+4]
				i += 4
			print ''

	def step(self,z=0,x=0,y=0):
		#print("\033c") #clear terminal window
		if self.player == 'B': #AI is player B
			self.ai_move()
			self.check_win() #check for AI
			self.change_player()
		elif self.player == 'A':
			if self.check_valid(z,x,y):
				self.grid[z][x][y] = self.player
				self.set_grid_eval(z,x,y,-1000)
				print '\n', self.player, 'has input', z,x,y
				self.check_win() #check for human
				self.change_player()
			else:
				print 'invalid input'
		self.print_board()

	def play_game(self):
		while self.game_not_won:
			if self.player == 'A':
				print self.player, 'turn', self.turn
				inp = raw_input('input location zxy: ')
				self.step(int(inp[0]),int(inp[1]),int(inp[2]))
			else:
				self.step()
		self.change_player()
		print self.player, 'has won'

	def ai_move(self):
		if self.hardness == 0:
			self.rand_ai_move()
		else:
			self.algorithm()

	def rand_ai_move(self): #dumb random one
		x = random.randint(0,3)
		y = random.randint(0,3)
		z = random.randint(0,3)
		print z,y,x
		while not self.check_valid(z,x,y):
			x = random.randint(0,3)
			y = random.randint(0,3)
			z = random.randint(0,3)
			print z,y,x
		self.grid[z][x][y] = self.player	
		print '\n', self.player, 'has input', x,y,z	

	def algorithm(self): #this is our AI algorithm
		self.evaluate_board()
		# self.disp_grid_eval()
		self.play_best_move()

	def play_best_move(self):
		#this looks at self.grid_eval and plays the highest valued spot
		val = max(self.grid_eval)
		locs = [i for i, j in enumerate(self.grid_eval) if j == max(self.grid_eval)]
		if len(locs) == 1:
			loc = locs[0]
		else: #if we have more than one optimal answer, randomly select
			loc = locs[random.randint(0,len(locs)-1)]		
		self.grid_eval[loc] = -1000 #now that we have played move, don't play there anymore
		z,x,y = self.loc_to_grid(loc)
		self.grid[z][x][y] = self.player	
		print '\n', self.player, 'has input', z,x,y, 'with score', val

	def define_score(self,diag_type,index,empty_places):
		if self.board[diag_type][index] == -3: #1 we win on 3 in a row
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,10000) 
		elif self.board[diag_type][index] == 3: #2 we block an opponent 3
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,5000) 
		elif self.board[diag_type][index] == 2: #3 block opponent has 2 in a row
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,200)
			z,x,y = empty_places[1]
			self.add_grid_eval(z,x,y,200)
		elif self.board[diag_type][index] == -2: #4 make 2 in a row a 3
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,150)
			z,x,y = empty_places[1]
			self.add_grid_eval(z,x,y,150)
		elif self.board[diag_type][index] == -1: #5 make 1 in a row a 2
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,50)
			z,x,y = empty_places[1]
			self.add_grid_eval(z,x,y,50)
			z,x,y = empty_places[2]
			self.add_grid_eval(z,x,y,50)
		elif self.board[diag_type][index] == 0: #6 start a row 1
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,30)
			z,x,y = empty_places[1]
			self.add_grid_eval(z,x,y,30)
			z,x,y = empty_places[2]
			self.add_grid_eval(z,x,y,30)
			z,x,y = empty_places[3]
			self.add_grid_eval(z,x,y,30)
		elif self.board[diag_type][index] == 1: #7 block opponent's 1
			z,x,y = empty_places[0]
			self.add_grid_eval(z,x,y,20)
			z,x,y = empty_places[1]
			self.add_grid_eval(z,x,y,20)
			z,x,y = empty_places[2]
			self.add_grid_eval(z,x,y,20)

	def evaluate_board(self):
		self.init_ai_stuff()
		#this computes the number of 3 in a row, 2 in a row, and 1 in a row
		print 'evaluating for', self.player
		for z in xrange(len(self.grid)):
			#first, check nondiagonals
			for x in xrange(len(self.grid[z])): #first, check horiz
				empty_places = []
				a,b = False,False #we have not visited a,b
				for y in xrange(len(self.grid[z][x])):
					if self.grid[z][x][y] == 'A':
						self.board['flat'][z*4+x] += 1; a = True
						self.set_grid_eval(z,x,y,-1000) #has already been played
					elif self.grid[z][x][y] == 'B':
						self.board['flat'][z*4+x] -= 1; b = True
						self.set_grid_eval(z,x,y,-1000)
					else:
						empty_places.append(tuple((z,x,y)))

				if (a and b) == False: #the row does not have both A and B inputs
					self.define_score('flat',z*4+x,empty_places)

			for y in xrange(len(self.grid[z][0])): #then, check flat
				empty_places = []
				a,b = False,False #we have not visited a,b
				for x in xrange(len(self.grid[z])):
					if self.grid[z][x][y] == 'A':
						self.board['horiz'][z*4+y] += 1; a = True
					elif self.grid[z][x][y] == 'B':
						self.board['horiz'][z*4+y] -= 1; b = True
					else:
						empty_places.append(tuple((z,x,y)))
				if (a and b) == False: #the row does not have both A and B inputs
					self.define_score('horiz',z*4+y,empty_places)

			for y in xrange(len(self.grid[z][0])): #finally, check verticals, and z is actually x here
				empty_places = []
				a,b = False,False #we have not visited a,b
				for zp in xrange(len(self.grid)):
					if self.grid[zp][z][y] == 'A':
						self.board['vert'][z*4+y] += 1; a = True
					elif self.grid[zp][z][y] == 'B':
						self.board['vert'][z*4+y] -= 1; b = True
					else:
						empty_places.append(tuple((zp,z,y)))
				if (a and b) == False: #the row does not have both A and B inputs
					self.define_score('vert',z*4+y,empty_places)
			#next, check diagonals
			#check planar first
			empty_places = []
			a,b = False,False #we have not visited a,b
			for i in xrange(len(self.grid[0])):
				if self.grid[z][i][i] == 'A':
					self.board['planar'][z*2] += 1; a = True
				elif self.grid[z][i][i] == 'B':
					self.board['planar'][z*2] -= 1; b = True
				else:
					empty_places.append(tuple((z,i,i)))
			if (a and b) == False: #the row does not have both A and B inputs
				self.define_score('planar',z*2,empty_places)

			empty_places = []
			a,b = False,False #we have not visited a,b
			for i in xrange(len(self.grid[0])):
				if self.grid[z][3-i][i] == 'A':
					self.board['planar'][z*2+1] += 1; a = True
				elif self.grid[z][3-i][i] == 'B':
					self.board['planar'][z*2+1] -= 1; b = True
				else:
					empty_places.append(tuple((z,3-i,i)))
			if (a and b) == False: #the row does not have both A and B inputs
				self.define_score('planar',z*2+1,empty_places)

			#check sidal
			empty_places = []
			a,b = False,False #we have not visited a,b
			for i in xrange(len(self.grid[0])):
				if self.grid[i][z][i] == 'A':
					self.board['sidal'][z*2] += 1; a = True
				elif self.grid[i][z][i] == 'B':
					self.board['sidal'][z*2] -= 1; b = True
				else:
					empty_places.append(tuple((i,z,i)))
			if (a and b) == False: #the row does not have both A and B inputs
				self.define_score('sidal',z*2,empty_places)
			empty_places = []
			a,b = False,False #we have not visited a,b
			for i in xrange(len(self.grid[0])):
				if self.grid[3-i][z][i] == 'A':
					self.board['sidal'][z*2+1] += 1; a = True
				elif self.grid[3-i][z][i] == 'B':
					self.board['sidal'][z*2+1] -= 1; b = True
				else:
					empty_places.append(tuple((3-i,z,i)))
			if (a and b) == False: #the row does not have both A and B inputs
				self.define_score('sidal',z*2+1,empty_places)

			#check frontal
			empty_places = []
			a,b = False,False #we have not visited a,b
			for i in xrange(len(self.grid[0])):
				if self.grid[i][i][z] == 'A':
					self.board['frontal'][z*2] += 1; a = True
				elif self.grid[i][i][z] == 'B':
					self.board['frontal'][z*2] -= 1; b = True
				else:
					empty_places.append(tuple((i,i,z)))
			if (a and b) == False: #the row does not have both A and B inputs
				self.define_score('frontal',z*2,empty_places)
			empty_places = []
			a,b = False,False #we have not visited a,b
			for i in xrange(len(self.grid[0])):
				if self.grid[3-i][i][z] == 'A':
					self.board['frontal'][z*2+1] += 1; a = True
				elif self.grid[3-i][i][z] == 'B':
					self.board['frontal'][z*2+1] -= 1; b = True
				else:
					empty_places.append(tuple((3-i,i,z)))
			if (a and b) == False: #the row does not have both A and B inputs
				self.define_score('frontal',z*2+1,empty_places)

		#finally, check superdiagonals
		empty_places = [[] for i in xrange(4)]
		a,b = [False for i in xrange(4)],[False for i in xrange(4)] #we have not visited a,b
		for i in xrange(len(self.grid[0])):
			if self.grid[i][i][i] == 'A':
				self.board['superdiag'][0] += 1; a[0] = True
			elif self.grid[i][i][i] == 'B':
				self.board['superdiag'][0] -= 1; b[0] = True
			else:
				empty_places[0].append(tuple((i,i,i)))

			if self.grid[i][3-i][i] == 'A':
				self.board['superdiag'][1] += 1; a[1] = True
			elif self.grid[i][3-i][i] == 'B':
				self.board['superdiag'][1] -= 1; b[1] = True
			else:
				empty_places[1].append(tuple((i,3-i,i)))

			if self.grid[i][3-i][3-i] == 'A':
				self.board['superdiag'][2] += 1; a[2] = True
			elif self.grid[i][3-i][3-i] == 'B':
				self.board['superdiag'][2] -= 1; b[2] = True
			else:
				empty_places[2].append(tuple((i,3-i,3-i)))

			if self.grid[i][i][3-i] == 'A':
				self.board['superdiag'][3] += 1; a[3] = True
			elif self.grid[i][i][3-i] == 'B':
				self.board['superdiag'][3] -= 1; b[3] = True
			else:
				empty_places[3].append(tuple((i,i,3-i)))
		for count in xrange(4):
			if (a[count] and b[count]) == False: #the row does not have both A and B inputs
				self.define_score('superdiag',count,empty_places[count])

if __name__ == '__main__':
	game = ai_tic(hardness = 4,player = 'B')
	game.play_game()