#e.g. http://www.python.org/jobs

from urllib import urlopen
import re

p=re.compile('<a href=".*?">(.*?)</a><br/>([\s\S]*?)</span>')
text=urlopen('http://www.python.org/jobs/').read()

for job,company in p.findall(text):
	print '%s (%s)'%(job,company.strip())
