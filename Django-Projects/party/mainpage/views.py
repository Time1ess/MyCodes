#coding=UTF-8
from django.shortcuts import render_to_response
from django.shortcuts import render

from notifications.models import Notification
from workdocuments.models import Document

def homepage(request):
	notifications=Notification.objects.all()[:5]
	documents=Document.objects.filter(filetype=0)[:5]
	return render_to_response('mainpage/index.html',{
		'notifications':notifications,
		'documents':documents,
		})
