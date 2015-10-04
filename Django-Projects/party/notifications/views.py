#coding=UTF-8
from django.shortcuts import render,get_object_or_404
from django.http import HttpResponse
from django.core.serializers.json import DjangoJSONEncoder
import json
from .models import Notification
from workdocuments.models import Document,AdditionalDocument
import simplejson


def detail(request):
	notification_id=request.POST.get('id',-1)
	notification=get_object_or_404(Notification,pk=notification_id)
	response_data={}
	response_data['title']=notification.title
	response_data['pub_date']=notification.pub_date.strftime('%Y-%m-%d %H:%M:%S')
	response_data['content']=notification.content
	response_data['id']=notification.id
	additionalFiles=AdditionalDocument.objects.filter(notification_set__id=notification_id)
	filesJSON={}
	for item in additionalFiles:
		filesJSON[item.filename]=item.file_path
	if filesJSON:
		response_data['additionalFiles']=filesJSON
	return HttpResponse(simplejson.dumps(response_data,ensure_ascii=False),content_type="application/json")
	#return HttpResponse(json.dumps(response_data,cls=DjangoJSONEncoder),content_type="application/json")
