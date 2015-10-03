# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('notifications', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Document',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('filename', models.CharField(max_length=200, verbose_name=b'\xce\xc4\xbc\xfe\xc3\xfb\xb3\xc6')),
                ('pub_date', models.DateTimeField(verbose_name=b'\xb7\xa2\xb2\xbc\xca\xb1\xbc\xe4')),
                ('file_path', models.CharField(max_length=200, verbose_name=b'\xce\xc4\xbc\xfe\xc2\xb7\xbe\xb6')),
                ('author', models.CharField(max_length=100, verbose_name=b'\xb7\xa2\xb2\xbc\xd5\xdf')),
            ],
        ),
        migrations.CreateModel(
            name='AddtionalDocument',
            fields=[
                ('document_ptr', models.OneToOneField(parent_link=True, auto_created=True, primary_key=True, serialize=False, to='workdocuments.Document')),
                ('notification_set', models.ForeignKey(to='notifications.Notification')),
            ],
            bases=('workdocuments.document',),
        ),
    ]
