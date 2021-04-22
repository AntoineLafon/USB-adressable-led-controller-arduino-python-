import serial
import time

#tram mode
CUSTOM = 1
BUNCH = 2
MODE = 3
TOGGLE = 4


#RGB mods
RAINBOW = 1


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


def checksum(data):
    sum = 0
    for d in data:
        sum ^= d
    return sum


def send_custom(num_led, red, green, blue, ser):
    header = create_header(CUSTOM, False, 4)
    data = [num_led, red, green, blue]
    ser.write(header+data)


def send_bunch(start, leds, ser):
    header = create_header(BUNCH, False, len(leds)*3+1)
    data = [start]
    for (r,g,b) in leds:
        data += [r, g, b]
    ser.write(header+data)

def send_rainbow(speed, ser):
    header = create_header(MODE, False, 2)
    data = [RAINBOW, speed]
    ser.write(header + data)

def send_toggle(ser):
    header = create_header(TOGGLE, False, 0)
    ser.write(header)





seri = serial.Serial("COM3", 115200, timeout=1)
print("connected!")
time.sleep(2)
#send_custom(0,255,255,255,seri)
l = 90
for j in range(0,3):
    for i in range(0,99):
        time.sleep(0.001)
        if i > 89:
            send_bunch(i,[(0,0,0)] +([(255,(255*k*k*k//(l*l*l)),(255*k*k*k//(l*l*l))) for k in range(0,l)]), seri)
        else:
            if i == 0:
                send_custom(99, 255, 0, 0, seri)
                time.sleep(0.001)
            send_bunch(i, [(0,0,0)] +([(255,(255*k*k*k//(l*l*l)),(255*k*k*k//(l*l*l))) for k in range(0,l)]), seri)

print(seri.read())


