# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0006_remove_document_file_path'),
    ]

    operations = [
        migrations.RenameField(
            model_name='document',
            old_name='file_content',
            new_name='file_path',
        ),
    ]
