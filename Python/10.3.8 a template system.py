import fileinput,re

#use for replace the special text
#like:
#'The sum of 7 and 9 is [7+9].'
#'[name="Mr. Gumby"]Hello, [name]'
#[x=2]
#[y=3]
#The sum of [x] and [y] is [x+y]

#pattern
field_pat=re.compile(r'\[(.+?)\]')

#vars collection
scope={}

#for re.sub
def replacement(match):
	code=match.group(1)
	try:
		#if able to eval
		return str(eval(code,scope))
	except SyntaxError:
		#otherwise execute assignment in the same scope
		exec code in scope
		return ''

#get inputs into a string
lines=[]
for line in fileinput.input():
	lines.append(line)
text=''.join(lines)

#replace match items using pattern
print field_pat.sub(replacement,text)
