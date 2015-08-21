import MySQLdb

conn=MySQLdb.connect(host='localhost',user='root',passwd='Dyc19930418',
		port=3306,db='pythonsql')
curs=conn.cursor()

vals=raw_input("Input the condition:")


query='select * from food where %s'%vals
print query
curs.execute(query)
names=[f[0] for f in curs.description]
for row in curs.fetchall():
	for pair in zip(names,row):
		print '%s:%s'%pair
	print
