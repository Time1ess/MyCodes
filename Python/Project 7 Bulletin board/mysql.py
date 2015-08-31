import MySQLdb
conn=MySQLdb.connect(host='localhost',user='root',passwd='Dyc19930418',
		port=3306,db='pythonsql')
curs=conn.cursor()
curs.execute('select * from messages')
print curs.fetchall()
