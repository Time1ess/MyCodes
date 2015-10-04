from django.contrib import admin

from .models import Message
# Register your models here.

class MessageAdmin(admin.ModelAdmin):
	list_display=('author','pub_date','content','reply_to')
	list_filter=['pub_date']
	search_fields=['content']


admin.site.register(Message,MessageAdmin)
