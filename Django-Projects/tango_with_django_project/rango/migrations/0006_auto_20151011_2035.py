# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import datetime


class Migration(migrations.Migration):

    dependencies = [
        ('rango', '0005_auto_20151011_2032'),
    ]

    operations = [
        migrations.AlterField(
            model_name='page',
            name='first_visit',
            field=models.DateTimeField(default=datetime.datetime.now),
        ),
    ]
