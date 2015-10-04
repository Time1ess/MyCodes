from django.conf.urls import url

import views

urlpatterns=[
		url(r'^(?P<file_path>.*)$',views.downloadFile),
		]
