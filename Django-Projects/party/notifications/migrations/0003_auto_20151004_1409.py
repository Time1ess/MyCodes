# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import ckeditor.fields


class Migration(migrations.Migration):

    dependencies = [
        ('notifications', '0002_auto_20151004_0927'),
    ]

    operations = [
        migrations.AlterField(
            model_name='notification',
            name='content',
            field=ckeditor.fields.RichTextField(verbose_name=b'content'),
        ),
    ]
