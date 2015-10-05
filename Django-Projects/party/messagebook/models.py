# -*- coding:gb18030 -*-
from django.db import models
from django.utils import timezone
from django import forms
from django.forms import ModelForm
from django.utils.translation import ugettext_lazy as _


class Message(models.Model):
	"""
	class Message defines a message with `author`,`content`,
	`pub_date`,`reply_to`.
	"""
	author=models.CharField('author',max_length=100)
	content=models.TextField('content')
	pub_date=models.DateTimeField('pub_date',default=timezone.now)
	reply_to=models.ForeignKey('self',blank=True,null=True)

	def self_reply_to_id(self):
		reply=Message.objects.get(pk=self.reply_to_id)
		return reply.id

	def short_content(self):
		message=self.content[:70]
		if(len(self.content)>70):
			message+='...'
		return message
	self_reply_to_id.short_description="REPLY"

	def __unicode__(self):
		return self.content

class MessageForm(ModelForm):
	class Meta:
		model=Message
		exclude=('pub_date','reply_to')
		labels={
				'author':u'姓名',
				'content':u'内容',
				}
		widgets={
				'content':forms.Textarea(attrs={'cols':20,'class':'form-control',},),
				'author':forms.TextInput(attrs={'class':'form-control',},),
				}
