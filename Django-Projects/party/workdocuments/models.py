# -*- coding:gb18030 -*-
from django.db import models
from django.utils import timezone
import datetime

from notifications.models import Notification


FILE_TYPES=(
		(u'独立文档',u'独立文档'),
		(u'附件文档',u'附件文档'),
		)

class Document(models.Model):
	"""
	class Document defines a document with a `filename`,`pub_date`,
	`file_path`,`author`
	"""
	filename=models.CharField(u'文件名',max_length=200)
	pub_date=models.DateTimeField(u'发布时间')
	file_path=models.FileField(u'文件路径',upload_to='workdocuments/media/uploadFiles',default=None)
	author=models.CharField(u'作者',max_length=100)
	filetype=models.CharField(u'类型',choices=FILE_TYPES,max_length=10,default=u'独立文档')
	def __unicode__(self):
		return self.filename

	def was_published_in_recent_14_days(self):
		now=timezone.now()
		return now-datetime.timedelta(days=14)<=self.pub_date<=now
	was_published_in_recent_14_days.admin_order_field='pub_date'
	was_published_in_recent_14_days.boolean=True
	was_published_in_recent_14_days.short_description=u"最近发布"	


class AdditionalDocument(Document):
	"""
	Inherits from Document,`notification` is required.
	"""
	notification_set=models.ManyToManyField(Notification)
