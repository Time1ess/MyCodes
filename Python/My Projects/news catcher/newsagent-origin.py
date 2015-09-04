#coding=UTF-8
__metaclass__=type
from urllib import urlopen
import re
class NewsAgent:
	"""
	可以从新闻来源获取新闻项目并且发布到新闻目标的对象。
	"""
	def __init__(self):
		self.sources=[]
		self.destinations=[]
	
	def addSource(self,source):
		self.sources.append(source)
	
	def addDestination(self,dest):
		self.destinations.append(dest)

	def distribute(self):
		"""
		从所有来源获取所有新闻项目并且发布到所有目标。
		"""
		items=[]
		for source in self.sources:
			items.extend(source.getItems())
		for dest in self.destinations:
			dest.receiveItems(items)	

class NewsItem:
	"""
	包括标题和主体文本、时间来源的简单新闻项目。
	"""
	def __init__(self,title,body):
		self.title=title
		self.body=body

class WebSource:
	"""
	使用正则表达式从网页中提取新闻项目的新闻来源。
	"""
	def __init__(self,url,sourcename,starttag,
			endtag,titlePattern,contentPattern):
		self.url=url
		self.sourcename=sourcename
		self.starttag=starttag
		self.endtag=endtag
		self.titlePattern=re.compile(titlePattern)
		self.contentPattern=re.compile(contentPattern)
	
	def getItems(self):
		pass
class NeteaseSource(WebSource):

	def __init__(self,url,sourcename,starttag,endtag,subtag,
			titlePattern,contentPattern):
		super(NeteaseSource,self).__init__(url,sourcename,
				starttag,endtag,titlePattern,contentPattern)
		self.subtag=subtag

	def getItems(self):
		webcontent=urlopen(self.url).read()
		contentdata=''
		webcontent=webcontent.splitlines()
		flag=False

		for line in webcontent:
			if self.endtag in line:
				break
			if self.starttag in line:
				flag=True
			if flag:
				contentdata+=line.strip()
		results=self.titlePattern.findall(contentdata)
		newsdata=[]

		maintitle=-1
		for tag,link,title in results:
			if title and not self.subtag in tag:
				maintitle+=1
				newsdata.append([[title,link]])
			if title and self.subtag in tag:
				newsdata[maintitle].append([title,link])

		f=open('dict.txt','w')
		for item in newsdata:
			print >>f,item[0][0],':',item[0][1]
			if len(item)>1:
				for subitem in item[1:]:
					print >>f,'\t',subitem[0],':',subitem[1]
		f.close()
		for item in newsdata:
			#do with item[0],notice that item[0][0] is title,item[0][1] is link


			pass
			#if exists subitem
			#do with item[1:]
			if len(item)>1:
				for subitem in item[1:]:
					pass
	#	for title,body in zip(titles,bodies):
			#yield NewsItem(title,body)
class HTMLDestination:
	"""
	将所有新闻项目格式化为HTML的目标类。
	"""
	def __init__(self,filename):
		self.filename=filename
	
	def receiveItems(self,items):

		out=open(self.filename,'w')
		print >>out,"""
		<html>
		 <head>
		  <title>Today's News</title>
		 </head>
		 <body>
		 <h1>Today's News</h1>
		"""

		print >>out,'<ul>'
		id=0
		for item in items:
			id+=1
			print >>out,'<li><a href="#%i">%s</a></li>' % (id,item.title)
		print >>out,'</ul>'

		id=0
		for item in items:
			id+=1
			print >>out,'<h2><a name="%i">%s</a></h2>' % (id,item.title)
			print >>out,'    '+item.body

		print >>out,"""
		 </body>
		</html>
		"""
def DefaultMain():
	"""
	来源和目标的默认设置，可以自己修改。
	"""

	agent=NewsAgent()

	#从新闻网站获取新闻的SimpleWebSource:
	url='http://news.163.com/'
	sourcename='网易'
	starttag='<!-- 头条区 -->'
	endtag='<div class="ns-wnews ns-recommand mb30" id="nsRecForYou"></div>'
	subtag='target="_blank"'
	titlePattern=r'<a(.*?)href="(http://.*?\.163\.com.*?)">(.*?)</a>'
	contentPattern=r'''
	<h1 id="h1title" class="ep-h1">(.*?)</h1>
	[\s\S]*?
	<div class="ep-time-soure cDGray">(.*?) 来源
	[\s\S]*?
	<div id="endText" class="end-text">
	([\s\S]*?)
	本文来源：(.*?)</span>
	'''
	netease=NeteaseSource(url,sourcename,starttag,
			endtag,subtag,titlePattern,contentPattern)
	#增加纯文本目标和HTML目标
	agent.addSource(netease)
	agent.addDestination(HTMLDestination('news.html'))

	#发布新闻项目
	agent.distribute()

def testMain():
	url='http://news.163.com/'
	content=urlopen(url).read()
	starttag='<!-- 头条区 -->'
	endtag='<div class="ns-wnews ns-recommand mb30" id="nsRecForYou"></div>'
	contentdata=''
	content=content.splitlines()
	flag=False
	for line in content:
		if endtag in line:
			break
		if starttag in line:
			flag=True
		if flag:
			contentdata+=line.strip()
	subtag='target="_blank"'
	pat=re.compile(r'<a(.*?)href="(http://.*?\.163\.com.*?)">(.*?)</a>')
	results=pat.findall(contentdata)
	tags=[s[0] for s in results]
	links=[s[1] for s in results]
	titles=[s[2] for s in results]
	newsdata=[]
	maintitle=-1
	for tag,link,title in results:
		if title and not subtag in tag:
			maintitle+=1
			newsdata.append([[title,link]])
		if title and subtag in tag:
			newsdata[maintitle].append([title,link])
	f=open('dict.txt','w')
	for item in newsdata:
		print >>f,item[0][0],':',item[0][1]
		if len(item)>1:
			for subitem in item[1:]:
				print >>f,'\t',subitem[0],':',subitem[1]
	f.close()
def testcontent():
	url='http://news.163.com/15/0902/09/B2GG6MBL0001124J.html'
	headPattern=r'([\s\S]*?)<body>'
	contentPattern=r'''<h1 id="h1title" class="ep-h1">(.*?)</h1>[\s\S]*?<div class="ep-time-soure cDGray">([\s\S]*?)来源[\s\S]*?<div id="endText" class="end-text">([\s\S]*?)本文来源：(.*?)</span>'''
#	contentPattern=r'''<h1 id="h1title" class="ep-h1">(.*?)</h1>[\s\S]*?<div class="ep-time-soure cDGray">(.*?)来源	[\s\S]*?
#	<div id="endText" class="end-text">
#	([\s\S]*?)
#	本文来源：(.*?)</span>'''
	allPattern=r'(<div class="ep-content-main" id="epContentLeft">[\s\S]*?本文来源：)(.*?)(</span>[\s\S]*?)<div class="sharecommend-wrap clearfix">[\s\S]*?(<div class="ep-content-side" id="epContentRight">)'
	contentdata=urlopen(url).read()
	headpat=re.compile(headPattern)
	heads=headpat.search(contentdata)
	print heads.group(1)
	pat=re.compile(allPattern)
	result=pat.search(contentdata)
	print result.group(1)
	print result.group(2)
	print result.group(3)

if __name__=='__main__':
	#DefaultMain()
	testcontent()
	#testMain()
