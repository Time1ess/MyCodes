# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0008_auto_20151006_0957'),
    ]

    operations = [
        migrations.AlterField(
            model_name='document',
            name='filetype',
            field=models.CharField(default='\u72ec\u7acb\u6587\u6863', max_length=10, verbose_name='\u7c7b\u578b', choices=[('\u72ec\u7acb\u6587\u6863', b'dependent'), ('\u9644\u4ef6\u6587\u6863', b'independent')]),
        ),
        migrations.AlterField(
            model_name='document',
            name='pub_date',
            field=models.DateTimeField(default=django.utils.timezone.now, verbose_name='\u53d1\u5e03\u65f6\u95f4'),
        ),
    ]
