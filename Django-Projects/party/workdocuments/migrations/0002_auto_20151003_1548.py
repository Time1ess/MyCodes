# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('workdocuments', '0001_initial'),
    ]

    operations = [
        migrations.RenameModel(
            old_name='AddtionalDocument',
            new_name='AdditionalDocument',
        ),
        migrations.AlterField(
            model_name='document',
            name='author',
            field=models.CharField(max_length=100, verbose_name=b'Author'),
        ),
        migrations.AlterField(
            model_name='document',
            name='file_path',
            field=models.CharField(max_length=200, verbose_name=b'File_path'),
        ),
        migrations.AlterField(
            model_name='document',
            name='filename',
            field=models.CharField(max_length=200, verbose_name=b'Filename'),
        ),
        migrations.AlterField(
            model_name='document',
            name='pub_date',
            field=models.DateTimeField(verbose_name=b'Pub_date'),
        ),
    ]
