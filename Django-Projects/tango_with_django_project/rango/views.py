from django.shortcuts import render,redirect
from django.http import HttpResponse,HttpResponseRedirect
from rango.models import Category,Page,UserProfile
from rango.forms import CategoryForm,PageForm,UserForm,UserProfileForm
from django.contrib.auth import authenticate,login,logout
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.utils import timezone
from datetime import datetime
from rango.bing_search import run_query
def index(request):
	category_list=Category.objects.order_by('-likes')[:5]
	page_list=Page.objects.order_by('-views')[:5]
	context_dict={'categories':category_list,
			'pages':page_list,
			}
	visits=request.session.get('visits')
	if not visits:
		visits=1

	reset_last_visit_time=False
	last_visit=request.session.get('last_visit')
	if last_visit:
		last_visit_time=datetime.strptime(last_visit[:-7],"%Y-%m-%d %H:%M:%S")


		if(datetime.now()-last_visit_time).seconds>10:
			visits=visits+1
			reset_last_visit_time=True
	else:
		reset_last_visit_time=True

	
	if reset_last_visit_time:
		request.session['last_visit']=str(datetime.now())
		request.session['visits']=visits

	context_dict['visits']=visits
	response=render(request,'rango/index.html',context_dict)
	return response

def about(request):
	context_dict={'boldmessage':'I am bold font from the context to About',}
	visits=request.session.get('visits')
	if not visits:
		visits=0
	context_dict['visits']=visits
	return render(request,'rango/about.html',context_dict)

def category(request,category_name_slug):
	context_dict={}
	try:
		category=Category.objects.get(slug=category_name_slug)
		context_dict['category_name']=category.name
		pages=Page.objects.filter(category=category)
		context_dict['pages']=pages
		context_dict['category']=category
		context_dict['category_name_slug']=category_name_slug
	except Category.DoesNotExist:
		pass
	result_list=[]
	query=None
	if request.method=='POST':
		query=request.POST['query'].strip()
		if query:
			# Run our Bing function to get the results list!
			result_list=run_query(query)
	context_dict['result_list']=result_list
	context_dict['query']=query

	return render(request,'rango/category.html',context_dict)
@login_required
def add_category(request):
	if request.method=='POST':
		form=CategoryForm(request.POST)

		if form.is_valid():
			form.save(commit=True)

			return index(request)
		else:
			print form.errors
	else:
		form=CategoryForm()

	return render(request,'rango/add_category.html',{'form':form})

@login_required
def add_page(request,category_name_slug):
	try:
		cat=Category.objects.get(slug=category_name_slug)
	except Category.DoesNotExist:
		cat=None

	if request.method=='POST':
		form=PageForm(request.POST)
		if form.is_valid():
			if cat:
				page=form.save(commit=False)
				page.category=cat
				page.first_visit=timezone.now()
				page.last_visit=timezone.now()
				page.views=0
				page.save()

				return category(request,category_name_slug)
		else:
			print form.errors
	else:
		form=PageForm()
	context_dict={'form':form,'category':cat}

	return render(request,'rango/add_page.html',context_dict)
		
def error_404(request):
	return render(request,'rango/404.html')

#def register(request):
#	#A boolean value for telling the template whether the registration was successful.
#	#Set to False initially,Code changes value to True when registration suceeds.
#	registered=False
#    #If it's a HTTP POST,we're interested in processing form data
#	if request.method=='POST':
#		#Attempt to grab information from the raw form information
#		#Note the we make use of both UserForm and UserProfileForm
#		user_form=UserForm(data=request.POST)
#		profile_form=UserProfileForm(data=request.POST)
#
#		if user_form.is_valid() and profile_form.is_valid():
#			#Save the user's form data to the database.
#			user=user_form.save()
#			
#			#Now we hash the password with the set_password method.
#			#Once hashed,we can update the user object.
#			user.set_password(user.password)
#			user.save()
#
#			#Now sort out the UserProfileForm instance.
#			#Since we need to set the user attribute ourselves,we commit=False.
#			#This delays saving the model until we're ready to avoid integrity problems.
#			profile=profile_form.save(commit=False)
#			profile.user=user
#
#			if 'picture' in request.FILES:
#				profile.picture=request.FILES['picture']
#
#			profile.save()
#
#			registered=True
#
#		else:
#			print user_form.errors,profile_form.errors
#	else:
#		user_form=UserForm()
#		profile_form=UserProfileForm()
#
#	return render(request,'rango/register.html',
#			{'user_form':user_form,'profile_form':profile_form,'registered':registered})
#
#def user_login(request):
#
#	if request.method=='POST':
#		username=request.POST.get('username')
#		password=request.POST.get('password')
#
#		user=authenticate(username=username,password=password)
#
#		if user:
#			if user.is_active:
#				login(request,user)
#				return HttpResponseRedirect('/rango/')
#			else:
#				return HttpResponse('Your Rango account is disabled.')
#		else:
#			print "Invalid login detals:{0},{1}".format(username,password)
#			return HttpResponse("Invalid login details supplied.")
#
#	else:
#		return render(request,'rango/login.html',{})

@login_required
def restricted(request):
	return render(request,'rango/restricted.html',{})

#@login_required
#def user_logout(request):
#	logout(request)
#
#	return HttpResponseRedirect('/rango/')

def search(request):

	result_list=[]
	query=None

	if request.method=='POST':
		query=request.POST['query'].strip()

		if query:
			# Run our Bing function to get the results list!
			result_list=run_query(query)

	return render(request,'rango/search.html',{
		'result_list':result_list,
		'query':query,
		})

def track_url(request):
	if request.method=='GET':
		if 'page_id' in request.GET:
			page_id=request.GET['page_id']
			try:
				page=Page.objects.get(pk=page_id)
				page.views+=1
				page.last_visit=timezone.now()
				if not page.first_visit:
					page.first_visit=timezone.now()
				page.save()
				return redirect(page.url)
			except:
				pass
	return redirect('/rango/')
@login_required
def register_profile(request):
	if request.method=='POST':
		user_id=request.POST['user_id'] 
		old_profile_form=None
		try:
			old_profile_form=UserProfile.objects.get(user_id=user_id)
		except:
			pass
		profile_form=UserProfileForm(data=request.POST) 
		user=None 
		try: 
			user=User.objects.get(pk=user_id) 
		except: 
			pass 
		if user and profile_form.is_valid():
			if not old_profile_form:
				profile=profile_form.save(commit=False)
				profile.user=user
				if 'picture' in request.FILES:
					profile.picture=request.FILES['picture'] 
				profile.save()
			else:
				old_profile_form.website=request.POST['website']
				if 'picture' in request.FILES: 
					old_profile_form.picture=request.FILES['picture'] 
				old_profile_form.save() 
				return redirect('/rango/') 
		else: 
			print profile_form.errors 
			return render(request,'rango/404.html',{}) 
	else: 
		profile_form=UserProfileForm() 
		return render(request,'registration/profile_registration.html',{ 'profile_form':profile_form, }) 

def users(request):
	users=User.objects.all()
	return render(request,'rango/users.html',{'users':users})

def user(request):
	user_id=request.GET['user_id']
	user=None
	try:
		user=User.objects.get(pk=user_id)
	except:
		pass
	return render(request,'rango/user.html',{'user':user})
@login_required
def like_category(request):

	cat_id=None
	if request.method=='GET':
		cat_id=request.GET['category_id']

	likes=0
	if cat_id:
		cat=Category.objects.get(id=int(cat_id))
		if cat:
			likes=cat.likes+1
			cat.likes=likes
			cat.save()
	return HttpResponse(likes)

def get_category_list(max_results=0,starts_with=''):
	cat_list=[]
	if starts_with:
		cat_list=Category.objects.filter(name__istartswith=starts_with)

	if max_results>0:
		if len(cat_list)>max_results:
			cat_list=cat_list[:max_results]
	return cat_list

def suggest_category(request):

	cat_list=[]
	starts_with=''
	if request.method=='GET':
		starts_with=request.GET['suggestion']

	cat_list=get_category_list(8,starts_with)

	return render(request,'rango/category_list.html',{'cat_list':cat_list})

def auto_add_page(request):
	title=None
	url=None
	cat_id=None

	if request.method=='GET':
		title=request.GET['title']
		url=request.GET['url']
		cat_id=request.GET['category']

		if title and url and cat_id:
			category=Category.objects.get(id=int(cat_id))
			p=Page.objects.get_or_create(category=category,title=title,url=url,first_visit=timezone.now(),last_visit=timezone.now())
			
			return HttpResponse('SUCCESS')
	return HttpResponse('FAIL')
