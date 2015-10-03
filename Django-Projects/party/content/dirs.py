#!C:\python27\python.exe
#coding=utf-8
__metaclass__=type

import os
import MySQLdb

def list_dir(dir_name,data):
	for elem in os.listdir(dir_name):
		temp_dir=os.path.join(dir_name,elem)
		if os.path.isdir(temp_dir):
			list_dir(temp_dir,data)
		else:
			data.append(dir_name+'\\'+elem)

data=[]
list_dir('pdfcontents',data)
conn=MySQLdb.connect(host='localhost',user='root',passwd='root',
		port=3306,db='test',charset='gbk')
curs=conn.cursor()
query='drop table files'
try:
	curs.execute(query)
	conn.commit()
except:
	pass

query='''
CREATE TABLE files (
id  int NOT NULL AUTO_INCREMENT ,
filename  varchar(255) NULL ,
path  varchar(255) NULL ,
PRIMARY KEY (id)
)
;
'''
curs.execute(query)
conn.commit()
query="insert into files (filename,path) values (%s,%s)"

for elem in data:
	elem=elem.replace('\\','/')
	print elem
	curs.execute(query,(elem[elem.rfind('/')+1:],'../'+elem))
conn.commit()
conn.close()


