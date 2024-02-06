import random
__TEMPLATES__ = '''
NO ./texture/NO.png
SO ./texture/SO.png
WE ./texture/WE.png
EA ./texture/EA.png

F 153,204,255                                        
C 209,160,240
'''

for i in range(10):
	filename = "../maps/valid_map_" + ("00" + str(i))[-2:] + ".cub"
	content  = __TEMPLATES__ + "\n"
	n = 2 ** (i + 3)
	content += n * '1' + '\n'
	player  = random.randint(1, n - 1)
	for p in range(1, n):
		line = ""
		for s in range(n - 2):
			line += str(random.randint(0, 1))
		if (player == p):
			c = ["N", "S", "E", "W"][random.randint(0, 3)]
			k = random.randint(1, len(line) - 1)
			line = line[:k - 1] + c + line[k:]
			line = line.replace(c + "1", c + "0").replace("1" + c, "0" + c)
		content += "1" + line + "1\n"
	content += n * '1'
	content  = content.strip()
	print (filename, n * n)
	with open(filename, "w") as fp:
		fp.write(content.strip())


