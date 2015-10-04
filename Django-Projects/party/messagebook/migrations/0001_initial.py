# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Message',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('author', models.CharField(max_length=100, verbose_name=b'author')),
                ('content', models.TextField(verbose_name=b'content')),
                ('pub_date', models.DateTimeField(verbose_name=b'pub_date')),
                ('reply_to', models.ForeignKey(to='messagebook.Message')),
            ],
        ),
    ]
