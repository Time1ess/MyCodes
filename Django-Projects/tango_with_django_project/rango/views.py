from django.shortcuts import render
from django.http import HttpResponse,HttpResponseRedirect
from rango.models import Category,Page
from rango.forms import CategoryForm,PageForm,UserForm,UserProfileForm
from django.contrib.auth import authenticate,login,logout
from django.contrib.auth.decorators import login_required
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
		context_dict['category_name_slug']=category_name_slug
	except Category.DoesNotExist:
		pass
	return render(request,'rango/category.html',context_dict)

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

def register(request):
	#A boolean value for telling the template whether the registration was successful.
	#Set to False initially,Code changes value to True when registration suceeds.
	registered=False
    #If it's a HTTP POST,we're interested in processing form data
	if request.method=='POST':
		#Attempt to grab information from the raw form information
		#Note the we make use of both UserForm and UserProfileForm
		user_form=UserForm(data=request.POST)
		profile_form=UserProfileForm(data=request.POST)

		if user_form.is_valid() and profile_form.is_valid():
			#Save the user's form data to the database.
			user=user_form.save()
			
			#Now we hash the password with the set_password method.
			#Once hashed,we can update the user object.
			user.set_password(user.password)
			user.save()

			#Now sort out the UserProfileForm instance.
			#Since we need to set the user attribute ourselves,we commit=False.
			#This delays saving the model until we're ready to avoid integrity problems.
			profile=profile_form.save(commit=False)
			profile.user=user

			if 'picture' in request.FILES:
				profile.picture=request.FILES['picture']

			profile.save()

			registered=True

		else:
			print user_form.errors,profile_form.errors
	else:
		user_form=UserForm()
		profile_form=UserProfileForm()

	return render(request,'rango/register.html',
			{'user_form':user_form,'profile_form':profile_form,'registered':registered})

def user_login(request):

	if request.method=='POST':
		username=request.POST.get('username')
		password=request.POST.get('password')

		user=authenticate(username=username,password=password)

		if user:
			if user.is_active:
				login(request,user)
				return HttpResponseRedirect('/rango/')
			else:
				return HttpResponse('Your Rango account is disabled.')
		else:
			print "Invalid login detals:{0},{1}".format(username,password)
			return HttpResponse("Invalid login details supplied.")

	else:
		return render(request,'rango/login.html',{})

@login_required
def restricted(request):
	return HttpResponse("Since you're logged in, you can see this text!")

@login_required
def user_logout(request):
	logout(request)

	return HttpResponseRedirect('/rango/')
