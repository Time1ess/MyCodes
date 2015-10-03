from django.contrib import admin

from .models import Document,AdditionalDocument

class DocumentAdmin(admin.ModelAdmin):
	list_display=('filename','author',
	'pub_date','was_published_in_recent_14_days')
	list_filter=['pub_date']
	search_fields=['filename','author','pub_date']

class AdditionalDocumentAdmin(DocumentAdmin):
	list_display=('filename','author',
			'pub_date',
			'notification_set','was_published_in_recent_14_days')



admin.site.register(Document,DocumentAdmin)
admin.site.register(AdditionalDocument,AdditionalDocumentAdmin)

