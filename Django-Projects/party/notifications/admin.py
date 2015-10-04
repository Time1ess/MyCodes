#coding=UTF-8
from django.contrib import admin

from .models import Notification
from workdocuments.models import Document,AdditionalDocument

class AdditionalDocumentShipInline(admin.TabularInline):
	model=AdditionalDocument.notification_set.through


class NotificationAdmin(admin.ModelAdmin):
	list_display=('title','pub_date','content','was_published_in_recent_14_days')
	list_filter=['pub_date']
	search_fields=['title']
	inlines=[
			AdditionalDocumentShipInline,
			]

admin.site.register(Notification,NotificationAdmin)

