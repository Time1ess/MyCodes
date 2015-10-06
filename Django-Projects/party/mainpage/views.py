# -*- coding:gb18030 -*-
from django.shortcuts import render

from notifications.models import Notification
from workdocuments.models import Document
from messagebook.models import Message,MessageForm

def homepage(request):
	notifications=Notification.objects.all().order_by('-pub_date')[:10]
	documents=Document.objects.filter(filetype='indep').order_by('-pub_date')[:10]
	messages=Message.objects.all().order_by('-pub_date')
	for message in messages:
		if message.reply_to:
			message.reply_to=Message.objects.get(id=message.reply_to_id)
	return render(request,'mainpage/index.html',{
		'notifications':notifications,
		'documents':documents,
		'messages':messages,
		'form':MessageForm(),
		})
