# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0002_auto_20151003_1548'),
    ]

    operations = [
        migrations.AddField(
            model_name='document',
            name='filetype',
            field=models.CharField(default=0, max_length=10, verbose_name=b'type'),
        ),
    ]
