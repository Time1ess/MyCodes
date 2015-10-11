# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('rango', '0002_userprofile'),
    ]

    operations = [
        migrations.AddField(
            model_name='page',
            name='first_visit',
            field=models.DateTimeField(default=None),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='page',
            name='last_visit',
            field=models.DateTimeField(default=None),
            preserve_default=False,
        ),
    ]
