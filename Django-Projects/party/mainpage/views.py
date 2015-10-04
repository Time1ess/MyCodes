#coding=UTF-8
from django.shortcuts import render_to_response
from django.shortcuts import render

from notifications.models import Notification
from workdocuments.models import Document
from messagebook.models import Message

def homepage(request):
	notifications=Notification.objects.all().order_by('-pub_date')[:10]
	documents=Document.objects.filter(filetype=0).order_by('-pub_date')[:10]
	messages=Message.objects.all().order_by('-pub_date')
	for message in messages:
		message.reply_to_set=Message.objects.filter(reply_to_id=message.id).order_by('pub_date')
	return render_to_response('mainpage/index.html',{
		'notifications':notifications,
		'documents':documents,
		'messages':messages,
		})
