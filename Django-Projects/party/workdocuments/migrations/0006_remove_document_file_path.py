# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0005_document_file_content'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='document',
            name='file_path',
        ),
    ]
