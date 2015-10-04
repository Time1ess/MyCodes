# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0004_auto_20151004_0927'),
    ]

    operations = [
        migrations.AddField(
            model_name='document',
            name='file_content',
            field=models.FileField(default=None, upload_to=b'uploadFiles'),
        ),
    ]
