from django.contrib import admin

from .models import Document,AdditionalDocument


class AdditionalDocumentShipInline(admin.TabularInline):
	model=AdditionalDocument.notification_set.through

class DocumentAdmin(admin.ModelAdmin):
	list_display=('filename','author',
	'pub_date','was_published_in_recent_14_days')
	list_filter=['pub_date']
	search_fields=['filename','author','pub_date']

class AdditionalDocumentAdmin(DocumentAdmin):
	list_display=('filename','author',
			'pub_date',
			'was_published_in_recent_14_days')
	inlines=[
			AdditionalDocumentShipInline,
			]
	exclude=('notification_set',)



admin.site.register(Document,DocumentAdmin)
admin.site.register(AdditionalDocument,AdditionalDocumentAdmin)

