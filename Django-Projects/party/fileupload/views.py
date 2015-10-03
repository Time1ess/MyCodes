from django.shortcuts import render
from django.http import HttpResponse
import os
from django.utils import timezone
from workdocuments.models import Document,AdditionalDocument


def uploadPage(request):
	return render(request,'fileupload/uploadFile.html')

def fileUpload(request):
	UPLOAD_ROOT=os.getcwd()+r'\fileupload\static\pdfcontents'
	file_path='/static/pdfcontents/'
	#return HttpResponse(UPLOAD_ROOT)
	file_name=request.POST.get('uploadFileName',None)
	encode_file_name=request.POST.get('encodeFileName',None)
	file_type=request.POST.get('fileType',0)
	file_obj=request.FILES.get('uploadFile',None)
	author=request.POST.get('Author',None)
	if file_obj==None or file_name==None or author==None or encode_file_name==None:
		return HttpResponse('404')
	file_full_path=os.path.join(UPLOAD_ROOT,file_name)
	file_path+=encode_file_name
	#return HttpResponse(file_full_path)
	dest=open(file_full_path,'wb+')
	dest.write(file_obj.read())
	dest.close()
	document=Document(filename=file_name,pub_date=timezone.now(),author=author,file_path=file_path,filetype=file_type)
	document.save()
	return render(request,'fileupload/uploadSuccess.html')

	


