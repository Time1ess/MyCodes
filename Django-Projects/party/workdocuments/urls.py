from django.conf.urls import url

import views

urlpatterns=[
		url(r'^media/(?P<file_path>.*)$',views.downloadFile),
		url(r'^getalldocuments/',views.getAllDocuments,name='getAllDocuments'),
		
		]
