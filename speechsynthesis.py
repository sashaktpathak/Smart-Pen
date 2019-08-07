import talkey
tts = talkey.Talkey()
with open("output1.txt") as f:
	while True:
		c = f.read(1)
		if not c:
			print ("End of file")
			break
		else:
			print ("character: ",c)
			tts.say(c)
		
