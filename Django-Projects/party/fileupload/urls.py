from django.conf.urls import url

import views

urlpatterns=[
		url(r'^$',views.uploadPage),
		url(r'^uploadFile.html',views.fileUpload,name='uploadFile'),
		]
