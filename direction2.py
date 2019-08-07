from time import sleep
import serial
import pyautogui
import time
import os
ser = serial.Serial('/dev/ttyACM2',9600)
time.sleep(3)
prev_y = 0
prev_z = 0
print("Calibrating........")
for i in range(30):
	mydata = ser.readline()
	mydata = (ser.readline().strip().split(' '))
	prev_y += int(mydata[1].decode('utf-8'))
	prev_z += int(mydata[2].decode('utf-8'))
prev_y = prev_y/30
prev_z = prev_z/30
while (1 == 1):
	mydata = ser.readline()
	mydata = (ser.readline().strip().split(' '))
	y = int(mydata[1].decode('utf-8'))
	z = int(mydata[2].decode('utf-8'))
	print(y,z)
	if y == -11111 and z == -11111:
		#pyautogui.screenshot('my_sss.png')
		#im = pyautogui.screenshot(region=(542,240,1150,660))
		#im.save("my_sss.png")
        	pyautogui.hotkey('ctrl', 'e')
		os.system("gsutil cp /home/sashakt/Desktop/minor/my_sss.png gs://ocrimg11")
		os.system("""gcloud ml vision detect-document "gs://ocrimg11/my_sss.png" > output.txt""")
		os.system("""gcloud ml vision detect-document "gs://ocrimg11/my_sss.png" >> oldoutput.txt""")
		os.system("python outputprocess.py > output1.txt")
		os.system("python speechsynthesis.py")
	elif abs(z-prev_z) >= 1000 and z < prev_z:
		pyautogui.dragRel(-50, 0, duration = 1) 
		print ("LEFT")
		#prev_z = z
	elif abs(z-prev_z) >= 1200 and z > prev_z:
		pyautogui.dragRel(50, 0, duration = 1) 		
		print ("RIGHT")
	elif abs(y-prev_y) >= 1000 and y < prev_y:
		print("UP")
		pyautogui.dragRel(0, -50, duration = 1) 
		#prev_y = y
	elif abs(y-prev_y) >= 900 and y > prev_y:
		pyautogui.dragRel(0, 50, duration = 1) 
		print("DOWN")
		#prev_y = y
		#prev_z = z
     
	
    #print(mydata.decode('utf-8'))
    
    #if data < 300:
    #   pyautogui.press(['a','enter'])
        #time.sleep(5)
        #pyautogui.moveRel(0, 50, duration = 1) 
        #pyautogui.hotkey('ctrl', 'shift', 'esc')
        #pyautogui.dragRel(50,50,2, button='left')
