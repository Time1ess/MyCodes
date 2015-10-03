from django.conf.urls import url

import views

urlpatterns=[
		url(r'^uploadFile/',views.uploadFile,name='uploadFile'),
		]
