

# gamecoord = raw_input('enter_coordinate')


class tic_tac_toe(object): #make it an object instead of classobj
	def __init__(self,size = 4,dimension = 3,player = 'A'):
		self.size = size
		self.dimension = dimension
		if dimension == 3:
			self.grid = [[[' ' for i in xrange(size)] for j in xrange(size)] for k in xrange(size)]
		elif dimension == 2:
			self.grid = [[[' '] for i in xrange(size)] for j in xrange(size)]
		self.player = player
		self.game_not_won = True #the game is still running
		self.turn = 1 #count number of turns

	def check_win(self):
		for z in xrange(len(self.grid)):
			#first, check nondiagonals
			for x in xrange(len(self.grid[z])): #first, check flat
				# print 'trying flat',z,x,0,self.grid[z][x][0]
				if self.grid[z][x][0] == self.player: #check if this place filled
					#print 'checking flat', z,x,0,self.grid[z][x][0]
					connected = True #assume that we connect at first
					for y in xrange(len(self.grid[z][x])):
						if self.grid[z][x][y] != self.player:
							connected = False
					if connected == True:
						print 'got here! flat', z,x,y
						self.game_not_won = False
						return
			for y in xrange(len(self.grid[z][0])): #then, check horizontals
				# print 'trying horiz',z,0,y,self.grid[z][0][y]
				if self.grid[z][0][y] == self.player: #check if this place filled
					#print 'checking horiz',z,0,y,self.grid[z][0][y]
					connected = True #assume that we connect at first
					for x in xrange(len(self.grid[z])):
						if self.grid[z][x][y] != self.player:
							connected = False
					if connected == True:
						print 'got here! horiz',z,x,y
						self.game_not_won = False
						return
			for y in xrange(len(self.grid[z][0])): #finally, check verticals, and z is actually x here
				# print 'trying vert',0,z,y,self.grid[0][z][y]
				if self.grid[0][z][y] == self.player: #check if this place filled
					#print 'checking vert',0,z,y,self.grid[0][z][y]
					connected = True #assume that we connect at first
					for zp in xrange(len(self.grid)):
						if self.grid[zp][z][y] != self.player:
							connected = False
					if connected == True:
						print 'got here! vert',zp,z,y
						self.game_not_won = False
						return
			#next, check diagonals
			#check planar first
			if self.grid[z][0][0] == self.player: 
				connected = True #assume that we connect at first
				for i in xrange(len(self.grid[0])):
					if self.grid[z][i][i] != self.player:
						connected = False
				if connected == True:
						print 'got here! planar', z,i,i
						self.game_not_won = False
						return
			if self.grid[z][3][0] == self.player: 
				connected = True #assume that we connect at first
				for i in xrange(len(self.grid[0])):
					if self.grid[z][3-i][i] != self.player:
						connected = False
				if connected == True:
						print 'got here! planar2',z,3-i,i
						self.game_not_won = False
						return
			#check frontal
			if self.grid[0][z][0] == self.player: 
				connected = True #assume that we connect at first
				for i in xrange(len(self.grid[0])):
					if self.grid[i][z][i] != self.player:
						connected = False
				if connected == True:
						print 'got here! frontal',i,z,i
						self.game_not_won = False
						return
			if self.grid[3][z][0] == self.player: 
				connected = True #assume that we connect at first
				for i in xrange(len(self.grid[0])):
					if self.grid[3-i][z][i] != self.player:
						connected = False
				if connected == True:
						print 'got here! frontal2',3-i,z,i
						self.game_not_won = False
						return
			#check sidal
			if self.grid[0][0][z] == self.player: 
				connected = True #assume that we connect at first
				for i in xrange(len(self.grid[0])):
					if self.grid[i][i][z] != self.player:
						connected = False
				if connected == True:
						print 'got here! sidal',i,i,z
						self.game_not_won = False
						return
			if self.grid[3][z][0] == self.player: 
				connected = True #assume that we connect at first
				for i in xrange(len(self.grid[0])):
					if self.grid[3-i][i][z] != self.player:
						connected = False
				if connected == True:
						print 'got here! sidal2',3-i,i,z
						self.game_not_won = False
						return
		#finally, check superdiagonals
		if self.grid[0][0][0] == self.player:
			connected = True #assume that we connect at first
			for i in xrange(len(self.grid[0])):
				if self.grid[i][i][i] != self.player:
					connected = False
			if connected == True:
					print 'got here! superdiag1',i,i,i
					self.game_not_won = False
					return
		if self.grid[0][3][0] == self.player:
			connected = True #assume that we connect at first
			for i in xrange(len(self.grid[0])):
				if self.grid[i][3-i][i] != self.player:
					connected = False
			if connected == True:
					print 'got here! superdiag2',i,3-i,i
					self.game_not_won = False
					return
		if self.grid[0][3][3] == self.player:
			connected = True #assume that we connect at first
			for i in xrange(len(self.grid[0])):
				if self.grid[i][3-i][3-i] != self.player:
					connected = False
			if connected == True:
					print 'got here! superdiag3',i,3-i,3-i
					self.game_not_won = False
					return
		if self.grid[0][0][3] == self.player:
			connected = True #assume that we connect at first
			for i in xrange(len(self.grid[0])):
				if self.grid[i][i][3-i] != self.player:
					connected = False
			if connected == True:
					print 'got here! superdiag4',i,i,3-i
					self.game_not_won = False
					return

	def step(self,z,x,y):
		print("\033c") #clear terminal window
		if self.check_valid(z,x,y):
			self.grid[z][x][y] = self.player
			print '\n', self.player, 'has input', x,y,z
			self.print_board()
			self.check_win()
			self.change_player()
		else:
			print 'invalid input'

	def check_valid(self,z,x,y):
		if z >= self.size or x >= self.size or y >= self.size:
			return False
		elif z < 0 or y < 0 or x < 0:
			return False
		elif self.grid[z][x][y] != ' ':
			return False
		else:
			return True

	def change_player(self):
		self.turn += 1
		if self.player == 'A':
			self.player = 'B'
		else:
			self.player = 'A'

	def print_board(self):
		for dimension in self.grid:
			for line in dimension:
				print line
			print ''

	def play_game(self):
		while self.game_not_won:
			print self.player, 'turn', self.turn
			inp = raw_input('input location xyz: ')
			#loc = [int(inp[0]),int(inp[1]),int(inp[2])]
			self.step(int(inp[0]),int(inp[1]),int(inp[2]))
		self.change_player()
		print self.player, 'has won'


if __name__ == '__main__':
	test = tic_tac_toe()
	test.play_game()
	#test.step(1,2,3)

"""
A 000, 020, 021, 023, 111, 121, 202, 203, 211, 223, 321, 322, 302, 012, 003
B 022, 032, 120, 122, 123, 212, 220, 221, 222, 232, 233, 320, 112, 330, 030

"""