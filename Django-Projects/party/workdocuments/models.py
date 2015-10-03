#coding=UTF-8
from django.db import models
from django.utils import timezone
import datetime

from notifications.models import Notification

class Document(models.Model):
	"""
	class Document defines a document with a `filename`,`pub_date`,
	`file_path`,`author`
	"""
	filename=models.CharField('Filename',max_length=200)
	pub_date=models.DateTimeField('Pub_date')
	file_path=models.CharField('File_path',max_length=400)
	author=models.CharField('Author',max_length=100)
	filetype=models.CharField('type',max_length=10,default=0)
	def __unicode__(self):
		return self.filename

	def was_published_in_recent_14_days(self):
		now=timezone.now()
		return now-datetime.timedelta(days=14)<=self.pub_date<=now
	was_published_in_recent_14_days.admin_order_field='pub_date'
	was_published_in_recent_14_days.boolean=True
	was_published_in_recent_14_days.short_description="Recently"	


class AdditionalDocument(Document):
	"""
	Inherits from Document,`notification` is required.
	"""
	notification_set=models.ForeignKey(Notification)
