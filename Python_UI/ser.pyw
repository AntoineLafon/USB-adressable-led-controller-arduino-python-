import serial
import time
import tkinter as tk

ZERO = int.to_bytes(0, 1, "big")

FRAMES = {}

class Application(tk.Frame):

    def __init__(self, portCom, master=None):
        super().__init__(master)
        self.master = master
        self.pack()
        self.ser = serial.Serial(portCom, 11200)
        time.sleep(2)

        self.r = tk.Scale(self, from_ = 0, to = 255, orient=tk.HORIZONTAL, command=self.sendRed)
        self.r.pack()
        self.g = tk.Scale(self, from_ = 0, to = 255, orient=tk.HORIZONTAL, command=self.sendGreen)
        self.g.pack()
        self.b = tk.Scale(self, from_ = 0, to = 255, orient=tk.HORIZONTAL, command=self.sendBlue)
        self.b.pack()
        self.rainbowButton = tk.Button(self, text = "rainbow effect", command=self.sendRainbow);
        self.rainbowButton.pack();
        self.button = tk.Button(self, text = "Quitter", command=self.master.destroy)
        self.button.pack()

    def sendBlue(self, val):
        self.ser.write(bytes('B', 'utf-8'))
        self.ser.write(int.to_bytes(int(val), 1, "big"))
        self.ser.write(int.to_bytes(0, 3, "big"))
        while(self.ser.inWaiting()>0):
            pass
        print("answer: ", self.ser.readline())

    def sendRed(self, val):
        self.ser.write(bytes('R', 'utf-8'))
        self.ser.write(int.to_bytes(int(val), 1, "big"))
        self.ser.write(int.to_bytes(0, 3, "big"))
        while(self.ser.inWaiting()>0):
            pass
        print("answer: ", self.ser.readline())

    def sendRainbow(self):
        self.ser.write(bytes('W', 'utf-8'))
        self.ser.write(int.to_bytes(1, 1, "big"))
        self.ser.write(int.to_bytes(0, 3, "big"))
        while(self.ser.inWaiting()>0):
            pass
        print("answer: ", self.ser.readline())

    def sendGreen(self, val):
        self.ser.write(bytes('G', 'utf-8'))
        self.ser.write(int.to_bytes(int(val), 1, "big"))
        self.ser.write(int.to_bytes(0, 3, "big"))
        while(self.ser.inWaiting()>0):
            pass
        print("answer: ", self.ser.readline())






root = tk.Tk()
f = Application("COM5", master = root)
f.mainloop()
"""
i = 0
ser = serial.Serial("COM5", 9600)
time.sleep(2)
i += ser.write(bytes('B', 'utf-8'))
i += ser.write(int.to_bytes(255, 1, "big"))
print(i, ser.readline())

print(ser.read())
"""
