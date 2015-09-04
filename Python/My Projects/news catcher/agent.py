#coding=UTF-8
__metaclass__=type
from urllib import urlopen
import re
class Agent:
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
