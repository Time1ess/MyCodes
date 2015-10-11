# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('rango', '0004_auto_20151011_2023'),
    ]

    operations = [
        migrations.AlterField(
            model_name='page',
            name='first_visit',
            field=models.DateTimeField(default=django.utils.timezone.now),
        ),
        migrations.AlterField(
            model_name='page',
            name='last_visit',
            field=models.DateTimeField(default=django.utils.timezone.now),
        ),
    ]
