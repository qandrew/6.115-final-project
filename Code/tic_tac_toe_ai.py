from tic_tac_toe import tic_tac_toe
import random

class ai_tic(tic_tac_toe):
	def __init__(self,hardness = 10,size = 4,dimension = 3):
		super(ai_tic,self).__init__(size,dimension)
		#hardness is on a scale from 1 to 10 where 1 is easy and 10 is hard
		self.hardness = hardness
		self.board = {'flat':[0 for i in xrange(size*size)],'horiz':[0 for i in xrange(size*size)],'vert':[0 for i in xrange(size*size)],}
		self.board['planar'] = [0 for i in xrange(8)]
		self.board['frontal'] = [0 for i in xrange(8)]
		self.board['sidal'] = [0 for i in xrange(8)]
		self.board['superdiag'] = [0 for i in xrange(4)]

	def step(self,z,x,y): #we2
		#print("\033c") #clear terminal window
		if self.check_valid(z,x,y):
			self.grid[z][x][y] = self.player
			print '\n', self.player, 'has input', x,y,z
			self.check_win() #check for human
			self.change_player()
			if self.game_not_won:
				self.ai_move()
				self.check_win() #check for AI
				self.change_player()
			self.print_board()
		else:
			print 'invalid input'

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

	def evaluate_board(self):
		#this computes
		pass



if __name__ == '__main__':
	print 'got here'
	# c = C('hu')
	# print c.huding

	ai = ai_tic(hardness = 0)
	ai.play_game()
