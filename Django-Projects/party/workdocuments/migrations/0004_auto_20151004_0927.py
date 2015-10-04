# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('notifications', '0002_auto_20151004_0927'),
        ('workdocuments', '0003_document_filetype'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='additionaldocument',
            name='notification_set',
        ),
        migrations.AddField(
            model_name='additionaldocument',
            name='notification_set',
            field=models.ManyToManyField(to='notifications.Notification'),
        ),
        migrations.AlterField(
            model_name='document',
            name='file_path',
            field=models.CharField(max_length=400, verbose_name=b'File_path'),
        ),
    ]
