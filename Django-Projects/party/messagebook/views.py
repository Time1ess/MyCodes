#coding=UTF-8
from django.shortcuts import render
from django.http import HttpResponse
import simplejson
from django.utils import timezone
from django.http import Http404
from django.http import HttpResponseRedirect
from .models import Message,MessageForm



def replyMessage(request):
	reply_to_id=request.POST.get('replyID',None)
	reply_to_name=request.POST.get('replyName',None)
	reply_to_content=request.POST.get('replyContent',None)
	if reply_to_id==None or reply_to_name==None or reply_to_content==None:
		return Http404('404 ERROR')
	reply_to_time=timezone.now()
	message=Message(author=reply_to_name,content=reply_to_content,pub_date=reply_to_time,reply_to=Message.objects.get(pk=reply_to_id))
	message.save()
	return HttpResponseRedirect('/#messages')

def detail(request):
	message_id=request.POST.get('id',None)
	message=Message.objects.get(id=message_id)
	response={}
	response['id']=message.id
	response['author']=message.author
	response['pub_date']=message.pub_date.strftime('%Y-%m-%d %H:%M:%S')
	response['content']=message.content
	return HttpResponse(simplejson.dumps(response,ensure_ascii=False),content_type="application/json")


def postMessage(request):
	if request.method=='POST':
		form=MessageForm(request.POST)
		if form.is_valid():
			form.save()
			return HttpResponseRedirect('/#messages')
	else:
		return Http404('404 ERROR')


