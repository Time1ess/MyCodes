from django.shortcuts import render
from django.http import HttpResponse
import os

from .models import Document,AdditionalDocument

def readFile(fn,buf_size=262144):
	f=open(fn,"rb")
	while True:
		c=f.read()
		if c:
			yield c
		else:
			break
	f.close()

def downloadFile(request,file_path):
	download_path=os.getcwd()+'\\workdocuments\\media\\'+file_path.replace('/','\\')
	response = HttpResponse(readFile(download_path), content_type='APPLICATION/OCTET-STREAM')
	return response

def getAllDocuments(request):
	documents=Document.objects.filter(filetype='indep').order_by('-pub_date')
	return render(request,'workdocuments/index.html',{
		'documents':documents,
		})
	

