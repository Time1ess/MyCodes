#coding=UTF-8
__metaclass__=type
from agent import Agent
from websource import *
from urllib import urlopen
from HTMLParser import HTMLParser

class NeteaseWebParser(HTMLParser):
	
	in_content=False
	in_link=False
	in_title=False
	in_data=False
	in_date=False
	in_source=False
	in_bold=False
	in_image=False
	data=[]
	date=''
	title=''
	source=[]
	author=''
	def handle_starttag(self,tag,attrs):
		
		attrs=dict(attrs)

		if tag=='div' and 'class' in attrs and 'ep-content-main' in attrs['class']:
			self.in_data=True
		if tag=='div' and 'class' in attrs and 'ep-time-soure' in attrs['class']:
			self.in_date=True
		if tag=='div' and 'class' in attrs and 'ep-source' in attrs['class']:
			self.in_source=True
		if tag=='div' and 'class' in attrs and 'sharecommend-wrap' in attrs['class']:
			self.in_data=False
		if self.in_data and tag=='h1':
			self.in_title=True
		if tag=='div' and 'class' in attrs and 'text' in attrs['class'] and self.in_data:
			self.in_content=True
		if tag=='b':
			self.in_bold=True

	def handle_data(self,data):
		if self.in_data:
			if self.in_title:
				self.title=data.strip()
				self.in_title=False
			elif self.in_bold:
				self.data[-1]=self.data[-1]+data
			elif self.in_content:
				self.data.append(data)
			elif self.in_date:
				self.date=data.strip()[:19]
				self.in_date=False
			elif self.in_source:
				self.source.append(data)
				
	def handle_endtag(self,tag):
		if tag=='div':
			self.in_source=False
			self.in_content=False
		if tag=='b':
			self.in_bold=False


	def initData(self):
		self.source=self.source[1].strip()
		self.data=[s for s in self.data if len(s.strip())>0]
		self.data='    '+'\n    '.join(self.data)

	def printAll(self):
		print self.title
		print self.date
		print self.source
		print self.data
	
	def printline(self):
		cnt=1
		for line in self.data:
			print cnt,'-:',line
			cnt+=1

text=urlopen('http://news.163.com/15/0902/09/B2GG6MBL0001124J.html').read()
parser=NeteaseWebParser()
parser.feed(text)
parser.initData()
parser.printAll()
#parser.printline()
parser.close()

