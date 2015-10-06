# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('messagebook', '0005_auto_20151005_1127'),
    ]

    operations = [
        migrations.AlterField(
            model_name='message',
            name='author',
            field=models.CharField(max_length=100, verbose_name='\u53d1\u5e03\u8005'),
        ),
        migrations.AlterField(
            model_name='message',
            name='content',
            field=models.TextField(verbose_name='\u5185\u5bb9'),
        ),
        migrations.AlterField(
            model_name='message',
            name='pub_date',
            field=models.DateTimeField(default=django.utils.timezone.now, verbose_name='\u53d1\u5e03\u65f6\u95f4'),
        ),
    ]
