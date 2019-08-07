from time import sleep
import serial
import pyautogui
import time


ser = serial.Serial('/dev/ttyACM0',9600)
time.sleep(4)
prev_y = 0
prev_z = 0
print("Calibrating........")
for i in range(30):
	mydata = ser.readline()
	mydata = (ser.readline().strip().split(' '))
	prev_y += int(mydata[1].decode('utf-8'))
	prev_z += int(mydata[2].decode('utf-8'))
prev_y = prev_y/50
prev_z = prev_z/50
while (1 == 1):
	mydata = ser.readline()
	mydata = (ser.readline().strip().split(' '))
	y = int(mydata[1].decode('utf-8'))
	z = int(mydata[2].decode('utf-8'))
	print(y,z)
	if abs(y-prev_y) >= 1000 and y < prev_y:
		print("UP")
		pyautogui.dragRel(0, -50, duration = 1) 
		#prev_y = y
	elif abs(y-prev_y) >= 1200 and y > prev_y:
		pyautogui.dragRel(0, 50, duration = 1) 
		print("DOWN")
		#prev_y = y
	elif abs(z-prev_z) >= 800 and z < prev_z:
		pyautogui.dragRel(-50, 0, duration = 1) 
		print ("LEFT")
		#prev_z = z
	elif abs(z-prev_z) >= 1200 and z > prev_z:
		pyautogui.dragRel(50, 0, duration = 1) 		
		print ("RIGHT")
		#prev_z = z
     
	
    #print(mydata.decode('utf-8'))
    
    #if data < 300:
    #   pyautogui.press(['a','enter'])
        #time.sleep(5)
        #pyautogui.moveRel(0, 50, duration = 1) 
        #pyautogui.hotkey('ctrl', 'shift', 'esc')
        #pyautogui.dragRel(50,50,2, button='left')
