import serial
import time

#tram mode
CUSTOM = 1
BUNCH = 2
MODE = 3
TOGGLE = 4


#RGB mods
RAINBOW = 1
FADE = 2


def create_header(mode, crc, length):
    ext = (length >= 8)
    if ext:
        header = [((mode << 5) + (crc << 4) + (ext << 3))]
        i = 0
        while length > 0:
            i += 1
            if length > 255 :
                header += [0xFF]
                length -= 255
            else:
                header += [length]
                length = 0
        header[0] += i
        assert i<8, "trame trop grande"
        return header
    else:
        return [(mode << 5) + (crc << 4) + length]


class Trame(object):
	def __init__(self, ident=0, ack=False, data=[]):
		super(Trame, self).__init__()
		self.ident = ident
		self.ack = ack
		self.data = data
		self.header = create_header(self.ident, self.ack, len(self.data))
	def setData(self, data):
		self.data = data
		self.header = create_header(self.ident, self.ack, len(self.data))
	def append(self, val):
		self.data.append(val)
		self.header += 1
	def send(self, ser, timeout = 0.01):
		ser.write(self.header+self.data)
		ser.flush()
		if (self.ack):
			t = ser.timeout
			ser.timeout = timeout
			rep = ser.read()
			return (rep == int.to_bytes(~self.header[0],1,"big",signed=True))
		return True


def send_custom(num_led, red, green, blue, ser):
    trame = Trame(CUSTOM)
    trame.setData([num_led, red, green, blue])
    trame.send(ser)


def send_bunch(start, leds, ser):
    trame = Trame(BUNCH, ack = True)
    data = [start]
    for (r,g,b) in leds:
        data += [r, g, b]
    trame.setData(data)
    while ( not trame.send(ser)):
    	time.sleep(0.005)

def send_rainbow(speed, ser):
    trame = Trame(MODE,data=[RAINBOW, speed])
    trame.send(ser)

def send_fade(speed, ser):
    header = create_header(MODE, False, 2)
    data = [FADE, speed]
    ser.write(header + data)

def send_toggle(ser):
    trame = Trame(TOGGLE)
    trame.send(ser)




<<<<<<< Updated upstream

seri = serial.Serial("COM3", 115200, timeout=1)
print("connected!")
time.sleep(2)
#send_custom(0,255,255,255,seri)
"""l = 90
for j in range(0,3):
    for i in range(0,99):
        time.sleep(0.001)
        if i > 89:
            send_bunch(i,[(0,0,0)] +([(255,(255*k*k*k//(l*l*l)),(255*k*k*k//(l*l*l))) for k in range(0,l)]), seri)
        else:
            if i == 0:
                send_custom(99, 255, 0, 0, seri)
                time.sleep(0.001)
            send_bunch(i, [(0,0,0)] +([(255,(255*k*k*k//(l*l*l)),(255*k*k*k//(l*l*l))) for k in range(0,l)]), seri)"""

send_fade(100, seri)
for i in range(10):
    print("[","="*i," "*(9-i),"]", sep="")
    time.sleep(1)
print("envoie de bunch")
send_bunch(0, [(200,0,0)]*50, seri)
print(seri.read())


=======
def test_bunch():
	seri = serial.Serial("COM9", 115200)
	print("connected!")
	time.sleep(2)
	l = 80
	for j in range(0,4):
	    for i in range(0,99):
	        send_bunch(i, [(0,0,0)] +([(255,(255*k*k*k//(l*l*l)),(255*k*k*k//(l*l*l))) for k in range(0,l)]), seri)
test_bunch()
>>>>>>> Stashed changes
