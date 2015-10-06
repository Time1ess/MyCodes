# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0007_auto_20151004_1153'),
    ]

    operations = [
        migrations.AlterField(
            model_name='document',
            name='author',
            field=models.CharField(max_length=100, verbose_name='\u4f5c\u8005'),
        ),
        migrations.AlterField(
            model_name='document',
            name='file_path',
            field=models.FileField(default=None, upload_to=b'workdocuments/media/uploadFiles', verbose_name='\u6587\u4ef6\u8def\u5f84'),
        ),
        migrations.AlterField(
            model_name='document',
            name='filename',
            field=models.CharField(max_length=200, verbose_name='\u6587\u4ef6\u540d'),
        ),
        migrations.AlterField(
            model_name='document',
            name='filetype',
            field=models.CharField(default='\u72ec\u7acb\u6587\u6863', max_length=10, verbose_name='\u7c7b\u578b', choices=[('\u72ec\u7acb\u6587\u6863', '\u72ec\u7acb\u6587\u6863'), ('\u9644\u4ef6\u6587\u6863', '\u9644\u4ef6\u6587\u6863')]),
        ),
        migrations.AlterField(
            model_name='document',
            name='pub_date',
            field=models.DateTimeField(verbose_name='\u53d1\u5e03\u65f6\u95f4'),
        ),
    ]
