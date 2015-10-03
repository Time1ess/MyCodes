# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Notification',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('title', models.CharField(max_length=200, verbose_name=b'\xcd\xa8\xd6\xaa\xb1\xea\xcc\xe2')),
                ('pub_date', models.DateTimeField(verbose_name=b'\xb7\xa2\xb2\xbc\xca\xb1\xbc\xe4')),
                ('content', models.TextField(verbose_name=b'\xbe\xdf\xcc\xe5\xc4\xda\xc8\xdd')),
            ],
        ),
    ]
