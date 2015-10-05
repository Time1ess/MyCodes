# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models
import datetime
from django.utils.timezone import utc


class Migration(migrations.Migration):

    dependencies = [
        ('messagebook', '0003_auto_20151004_1539'),
    ]

    operations = [
        migrations.AlterField(
            model_name='message',
            name='pub_date',
            field=models.DateTimeField(default=datetime.datetime(2015, 10, 5, 3, 4, 24, 83000, tzinfo=utc), verbose_name=b'pub_date'),
        ),
    ]
