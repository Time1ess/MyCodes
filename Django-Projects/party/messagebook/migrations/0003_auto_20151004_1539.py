# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('messagebook', '0002_auto_20151004_1536'),
    ]

    operations = [
        migrations.AlterField(
            model_name='message',
            name='reply_to',
            field=models.ForeignKey(blank=True, to='messagebook.Message', null=True),
        ),
    ]
