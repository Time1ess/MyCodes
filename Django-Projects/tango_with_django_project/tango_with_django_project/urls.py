"""tango_with_django_project URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.8/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Add an import:  from blog import urls as blog_urls
    2. Add a URL to urlpatterns:  url(r'^blog/', include(blog_urls))
"""
from django.conf.urls import include, url,patterns
from django.contrib import admin
from registration.backends.simple.views import RegistrationView
from django.conf import settings
from django.conf.urls.static import static
class MyRegistrationView(RegistrationView):
	def get_success_url(self,request,user):
		return '/rango/register_profile/'

urlpatterns = [
    url(r'^admin/', include(admin.site.urls)),
	url(r'^rango/',include('rango.urls',namespace='rango')),
	url(r'^accounts/register/$',MyRegistrationView.as_view(),name='registration_register'),
	url(r'^accounts/',include('registration.backends.simple.urls')),
]
urlpatterns+=patterns('django.views.static',(r'^profile_images/(?P<path>.*)','serve',{'document_root':settings.MEDIA_ROOT}),)
