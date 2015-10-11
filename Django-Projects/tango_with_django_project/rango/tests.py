from django.test import TestCase
from django.core.urlresolvers import reverse
import datetime
from django.utils import timezone
from rango.models import Category,Page

class CategoryMethodTests(TestCase):

	def test_ensure_views_are_positive(self):
		"""
		ensure_views_are_positive should results True for categories where
		are zero or positive.
		"""
		cat=Category(name='test',views=-1,likes=0)
		cat.save()
		self.assertEqual((cat.views>=0),True)

	def test_slug_line_creation(self):
		"""
		slug_line_creation check to make sure that when we add a category
		an appropriate slug line is created. i.e. "Random Category String"->
		"random-category-string"
		"""
		cat=Category(name='Random Category String')
		cat.save()
		self.assertEqual(cat.slug,'random-category-string')

def add_cat(name,views,likes):
	c=Category.objects.get_or_create(name=name)[0]
	c.views=views
	c.likes=likes
	c.save()
	return c


class IndexViewTests(TestCase):

	def test_index_view_with_no_categories(self):
		"""
		If no questions exist,an appropriate message should be displayed.
		"""
		response=self.client.get(reverse('rango:index'))
		self.assertEqual(response.status_code,200)
		self.assertContains(response,"There are no categories present.")
		self.assertQuerysetEqual(response.context['categories'],[])
		
	def test_index_view_with_categories(self):
		"""
		If no questions exist,an appropriate message should be displayed.
		"""

		add_cat('test',1,1)
		add_cat('temp',1,1)
		add_cat('tmp',1,1)
		add_cat('tmp test temp',1,1)

		response=self.client.get(reverse('rango:index'))
		self.assertEqual(response.status_code,200)
		self.assertContains(response,'tmp test temp')

		num_cats=len(response.context['categories'])
		self.assertEqual(num_cats,4)

def add_page(cat,title,url,views,last_visit,first_visit):
	page=Page(category=cat,title=title,url=url,views=views,
			last_visit=last_visit,first_visit=first_visit)
	page.save()
	return page

class PageVisitTimeTests(TestCase):

	def test_visit_time_not_in_the_future(self):
		c=add_cat('test',1,1)
		p=add_page(c,'tmp','http://www.baidu.com',0,timezone.now()-datetime.timedelta(days=1),timezone.now())
		self.assertEqual((p.last_visit<=timezone.now()),True)
		self.assertEqual((p.first_visit<=timezone.now()),True)




