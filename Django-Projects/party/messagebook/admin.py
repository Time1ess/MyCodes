from django.contrib import admin

from .models import Message
# Register your models here.

class MessageAdmin(admin.ModelAdmin):
	list_display=('id','author','pub_date','short_content','self_reply_to_id')
	list_filter=['pub_date']
	search_fields=['content']


admin.site.register(Message,MessageAdmin)
