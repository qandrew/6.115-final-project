#Andrew Xia

class Game(object):
	def __init__(self,width, height, ball_position, ball_velocity, bricks):
		self.width = width
		self.height = height
		self.ball_position = ball_position
		self.ball_velocity = ball_velocity
		self.bricks = bricks
		#return None

def init(width, height, ball_position, ball_velocity, bricks):
	global game
	game = Game(width, height, ball_position, ball_velocity, bricks)
	return None

def step(time, paddle_1_xpos, paddle_2_xpos, paddle_offset, paddle_radius):
	#check collision with wall
	global game
	i_left = intersect_line(game.ball_position,game.ball_velocity,[0,0],[0,game.height])
	i_right = intersect_line(game.ball_position,game.ball_velocity,[game.width,0],[game.width,game.height])
	i_top = intersect_line(game.ball_position,game.ball_velocity,[0,0],[game.width,0])
	i_bot = intersect_line(game.ball_position,game.ball_velocity,[0,game.height],[game.width,game.height])
	i_pad_1 = intersect_circle(game.ball_position,game.ball_velocity,[paddle_1_xpos,game.height+paddle_offset],paddle_radius)
	i_pad_2 = intersect_circle(game.ball_position,game.ball_velocity,[paddle_2_xpos,-paddle_offset],paddle_radius)
	i_brick = []
	for brick in game.bricks:
		i_brick.append(intersect_brick(game.ball_velocity,game.ball_position,brick))
	intersect_array = [i_left,i_right,i_top,i_bot,i_pad_1,i_pad_2] + [i[0] for i in i_brick]
	print 'huding'
	print intersect_array
	next_intersect_index = intersect_array.index(min(intersect_array,key =lambda x:x[0])) #we compare the times x[0]
	if intersect_array[next_intersect_index][0] <= time:
		game.ball_position = intersect_array[next_intersect_index][1] #place ball at intersect place
		if next_intersect_index == 0 or next_intersect_index == 1: #i_left or i_right
			game.ball_velocity = [-game.ball_velocity[0], game.ball_velocity[1]]
			game.ball_position = [game.ball_position[0]+0.001*game.ball_velocity[0], game.ball_position[1]+0.001*game.ball_velocity[1]]
			return 0
		elif next_intersect_index == 2 or next_intersect_index == 3: #i_top or i_bot
			game.ball_velocity = [game.ball_velocity[0], -game.ball_velocity[1]]
			game.ball_position = [game.ball_position[0]+0.001*game.ball_velocity[0], game.ball_position[1]+0.001*game.ball_velocity[1]]
			return cmp(game.ball_velocity[1],0) #player 1, bottom, wins if ball now heading in positive/down direction. and vice versa
		elif next_intersect_index == 4: #paddle 1 collision
			norm = normal_circle([paddle_1_xpos,-paddle_offset],game.ball_position)
			game.ball_velocity = reflection(norm,game.ball_velocity)
			game.ball_position = [game.ball_position[0]+0.001*game.ball_velocity[0], game.ball_position[1]+0.001*game.ball_velocity[1]]
			return 0
		elif next_intersect_index == 5: #paddle 1 collision
			norm = normal_circle([paddle_1_xpos,-paddle_offset],game.ball_position)
			game.ball_velocity = reflection(norm,game.ball_velocity)
			game.ball_position = [game.ball_position[0]+0.001*game.ball_velocity[0], game.ball_position[1]+0.001*game.ball_velocity[1]]
			return 0
		elif next_intersect_index == 6: #paddle 2 collision
			norm = normal_circle([paddle_2_xpos,game.height+paddle_offset],game.ball_position)
			game.ball_velocity = reflection(norm,game.ball_velocity)
			game.ball_position = [game.ball_position[0]+0.001*game.ball_velocity[0], game.ball_position[1]+0.001*game.ball_velocity[1]]
			return 0
		else: #bricks
			brick_index = next_intersect - 6
			# direction of reflection
			if i_brick[brick_index]:
				# wall is horizontal
				game.ball_velocity = [game.ball_velocity[0], -game.ball_velocity[1]]
			else:
				# wall is vertical
				game.ball_velocity = [-game.ball_velocity[0], game.ball_velocity[1]]
			game.ball_position = [game.ball_position[0]+0.001*game.ball_velocity[0], game.ball_position[1]+0.001*game.ball_velocity[1]]
			# remove brick
			game.bricks = game.bricks[:brick_index] + game.bricks[brick_index+1:]
			return 0

	else: #no collide
		game.ball_position = [game.ball_position[0]+time*game.ball_velocity[0], game.ball_position[1]+time*game.ball_velocity[1]]
		return 0

# You may assume the canvas is blank
def draw(canvas, paddle_1_xpos, paddle_2_xpos, paddle_offset, paddle_radius):
	global game
	canvas.draw_circle(paddle_1_xpos, -paddle_offset, paddle_radius, '#ffffff')
	canvas.draw_circle(paddle_2_xpos, game.height + paddle_offset, paddle_radius, '#ffffff')
	canvas.draw_circle(game.ball_position[0], game.ball_position[1], 5, '#ffffff')
	for brick in game.bricks:
		canvas.draw_rectangle(brick['center'][0]-brick['width']*0.5, brick['center'][1]-brick['height']*0.5, \
			brick['center'][0]+brick['width']*0.5, brick['center'][1]+brick['height']*0.5, brick['color'])
	return None

	return None


#AUX FUNCTIONS
def dot(a,b): #return the dot product between [x,y] and [x,y]
	return 1.0*(a[0]*b[0] + a[1]*b[1]) #force float

def cross_z(a,b):
	return 1.0*(a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2],a[0]*b[1] - a[1]*b[0])

def cross(a,b):
	test = 1.0*(a[0]*b[1] - a[1]*b[0]) #force float
	# print test
	return test

def normal_circle(circle, point):
	norm = (point[0]-circle[0],point[1] - circle[1])
	if norm[0] == 0 and norm[1] == 0: #at the point
		return [0,0]
	else:
		normalized = (norm[0]**2 + norm[1]**2)**0.5
		return [norm[0]/normalized,norm[1]/normalized]

def projection(v,n): #velocity v in direction of normal n
	return [dot(v,n)/dot(n,n)*n[0],dot(v,n)/dot(n,n)*n[1]]

def reflection(v,n):
	proj = projection(v,n)
	return [v[0] - 2*proj[0], v[1] - 2*proj[1]]

def intersect_line(p1,v1,p3,p4): #return time and location of collision
	v2 = [p4[0] - p3[0],p4[1] - p3[1]]
	p31 = [p3[0] - p1[0],p3[1] - p1[1]]
	p13 = [p1[0] - p3[0],p1[1] - p3[1]]
	if cross(v2,v1) != 0:
		t = cross(v2, p31)/cross(v2,v1)
		u = cross(v2, p13)/cross(v1,v2)

		if (u > 0 and u < 1) or (t > 0 and t < 1):
			return t, [p1[0] + t*v1[0], p1[1] + t*v1[1]]

	return float('inf'), float('inf') #return not possible

def intersect_circle(p1,v1,center,radius):
	distance = ((p1[0] - center[0])**2 + (p1[1] - center[1])**2)**0.5
	if distance < radius:
		return float('inf'), float('inf') #no collision
	a = dot(v1,v1)
	p1cc = [p1[0] - center[0],p1[1] - center[1]]
	b = 2*dot(v1,p1cc)
	c = dot(p1cc,p1cc) - radius**2
	discriminant = b**2-4*a*c
	if discriminant < 0: #no collision exists
		return float('inf'), float('inf') #no collision
	discriminant = discriminant**0.5
	t_0 = (-b + discriminant)/(2*a)
	t_1 = (-b - discriminant)/(2*a)
	t = min(t_0,t_1)
	return t,[p1[0] + t*v1[0], p1[1] + t*v1[1]]

def intersect_brick(p1,v1,brick):
	center = brick['center']
	width = 1.0*brick['width']
	height = 1.0*brick['height']
	top_right = [center[0]+width/2, center[1]-height/2]
	top_left = [center[0]-width/2, center[1]-height/2]
	bottom_right = [center[0]+width/2, center[1]+height/2]
	bottom_left = [center[0]-width/2, center[1]+height/2]
	intersect_top = intersect_line(p1,v1,top_right, top_left)
	intersect_right = intersect_line(p1,v1,top_right, bottom_right)
	intersect_left = intersect_line(p1,v1,bottom_left, top_left)
	intersect_bottom = intersect_line(p1,v1,bottom_right, bottom_left)
	intersections = [intersect_top, intersect_right, intersect_bottom, intersect_left]
	intersect_array = [intersection[0] for intersection in intersections]
	next_intersect = intersect_array.index(min(intersect_array)) #get the min val
	if next_intersect == 0 or next_intersect == 2: #top or bottom
		return [intersections[next_intersect], True]
	else:
		return [intersections[next_intersect], False]

"""
Notes:
"""

