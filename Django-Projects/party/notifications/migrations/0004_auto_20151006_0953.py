# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models
import ckeditor.fields


class Migration(migrations.Migration):

    dependencies = [
        ('notifications', '0003_auto_20151004_1409'),
    ]

    operations = [
        migrations.AlterField(
            model_name='notification',
            name='content',
            field=ckeditor.fields.RichTextField(verbose_name='\u5185\u5bb9'),
        ),
        migrations.AlterField(
            model_name='notification',
            name='pub_date',
            field=models.DateTimeField(verbose_name='\u53d1\u5e03\u65f6\u95f4'),
        ),
        migrations.AlterField(
            model_name='notification',
            name='title',
            field=models.CharField(max_length=200, verbose_name='\u6807\u9898'),
        ),
    ]
