# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0009_auto_20151006_1537'),
    ]

    operations = [
        migrations.AlterField(
            model_name='document',
            name='filetype',
            field=models.CharField(default=b'dependent', max_length=10, verbose_name='\u7c7b\u578b', choices=[(b'dependent', '\u72ec\u7acb\u6587\u4ef6'), (b'independent', '\u9644\u4ef6\u6587\u4ef6')]),
        ),
    ]
