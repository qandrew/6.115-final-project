import serial, numpy, time

"""
Serial driver for PSoC-based VGA board
David Lawrence (dlaw@mit.edu), June 2013

Requires numpy and pyserial.
"""

# Open the serial port
s = serial.Serial('/dev/ttyUSB0', baudrate=19200)

def set_resolution(i):
    # Send the command byte to choose a resolution (see documentation)
    s.write(bytes([(i & 3) | 0x80]))

def convert_color(arr):
    # Convert an array of RGB colors to the one-byte values
    # closest to each color in the board's color space
    arr = numpy.asarray(arr)
    return (((arr[..., 0] >> 6) << 4) +
            ((arr[..., 1] >> 6) << 2) +
            ((arr[..., 2] >> 6) << 0))

def write_colors(arr):
    # Draw an array of pixels to the VGA board.
    # The resolution is automatically set based on the size of the array.
    set_resolution([(16, 12, 3), (32, 24, 3), (64, 48, 3), (128, 96, 3)]
                   .index(arr.shape))
    s.write(convert_color(arr.astype('uint8')).T.ravel())

def test():
    # Put a test image on the screen.
    write_colors(numpy.load('test_image.npy'))

def leeb():
    write_colors(numpy.load('leeb.npy'))

def rect_demo():
    a = numpy.zeros((32,24,3), 'ubyte')
    while True:
        x = numpy.random.randint(32)
        u = numpy.random.randint(32)
        y = numpy.random.randint(24)
        v = numpy.random.randint(24)
        c = numpy.random.randint(3)
        i = numpy.random.randint(128,256)
        if x == u: x,u = 0,32
        if y == v: y,v = 0,24
        a[min(x,u):max(x,u),min(y,v):max(y,v),c] ^= i
        write_colors(a)
        time.sleep(.6)
