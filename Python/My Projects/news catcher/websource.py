#coding=UTF-8
__metaclass__=type

from agent import Agent
import re
from urllib import urlopen
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
		return newsdata

def main():
	"""
	来源和目标的默认设置，可以自己修改。
	"""

	agent=Agent()

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

	#发布新闻项目
	agent.distribute()

if __name__=='__main__':
	main()
