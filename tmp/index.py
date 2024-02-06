import os

def find(dirname, res = None):
	if not res:
		res = {}
	listfiles = []
	try:
		listfiles = os.listdir(dirname)
	except:
		return ({})
	for basename in listfiles:
		if basename in ['.git', ".", ".."]:
			continue
		filename = os.path.realpath(os.path.join(dirname, basename))
		if not (find(filename, res)):
			res[filename] = basename
	return (res)

for filename, basename in find("..").items():
	print (basename)
