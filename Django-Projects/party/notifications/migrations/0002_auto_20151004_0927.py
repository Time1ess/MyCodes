# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('notifications', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='notification',
            name='content',
            field=models.TextField(verbose_name=b'content'),
        ),
        migrations.AlterField(
            model_name='notification',
            name='pub_date',
            field=models.DateTimeField(verbose_name=b'pub_date'),
        ),
        migrations.AlterField(
            model_name='notification',
            name='title',
            field=models.CharField(max_length=200, verbose_name=b'title'),
        ),
    ]
