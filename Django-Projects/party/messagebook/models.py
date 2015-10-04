from django.db import models
from django.utils import timezone
# Create your models here.

class Message(models.Model):
	"""
	class Message defines a message with `author`,`content`,
	`pub_date`,`reply_to`.
	"""
	author=models.CharField('author',max_length=100)
	content=models.TextField('content')
	pub_date=models.DateTimeField('pub_date')
	reply_to=models.ForeignKey('self',blank=True,null=True)

	def __unicode__(self):
		return self.content


