from django.conf.urls import include, url

import views

urlpatterns=[
		url(r'replyMessage/$',views.replyMessage,name='replyMessage'),
		url(r'detail/$',views.detail),
		url(r'message/$',views.postMessage,name='message'),
		]
