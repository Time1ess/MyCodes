# -*- coding:gb18030 -*-
from django.shortcuts import render
from django.http import HttpResponse
from rango.models import Category,Page

def index(request):
	category_list=Category.objects.order_by('-likes')[:5]
	page_list=Page.objects.order_by('-views')[:5]
	context_dict={'categories':category_list,
			'pages':page_list,
			}
	return render(request,'rango/index.html',context_dict)

def about(request):
	context_dict={'boldmessage':'I am bold font from the context to About',}
	return render(request,'rango/about.html',context_dict)

def category(request,category_name_slug):

	context_dict={}

	try:
		category=Category.objects.get(slug=category_name_slug)
		context_dict['category_name']=category.name

		pages=Page.objects.filter(category=category)

		context_dict['pages']=pages

		context_dict['category']=category

	except Category.DoesNotExist:
		pass

	return render(request,'rango/category.html',context_dict)
