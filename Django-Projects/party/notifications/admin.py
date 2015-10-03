#coding=UTF-8
from django.contrib import admin

from .models import Notification

class NotificationAdmin(admin.ModelAdmin):
	list_display=('title','pub_date','content','was_published_in_recent_14_days')
	list_filter=['pub_date']
	search_fields=['title']

admin.site.register(Notification,NotificationAdmin)

