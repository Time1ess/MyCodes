import re,fileinput
pat=re.compile(r'[a-z\-\.]+@[a-z\-\.]+',re.IGNORECASE)
addresses=set()
for line in fileinput.input():
	for address in pat.findall(line):
		addresses.add(address)

for address in sorted(addresses):
	print address
