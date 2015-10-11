# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import datetime


class Migration(migrations.Migration):

    dependencies = [
        ('rango', '0003_auto_20151011_2016'),
    ]

    operations = [
        migrations.AlterField(
            model_name='page',
            name='first_visit',
            field=models.DateTimeField(default=datetime.datetime.now),
        ),
        migrations.AlterField(
            model_name='page',
            name='last_visit',
            field=models.DateTimeField(default=datetime.datetime.now),
        ),
    ]
