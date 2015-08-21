import MySQLdb

def convert(value):
	if value.startswith('~'):
		return value.strip('~')
	if not value:
		value='0'
	return float(value)

conn=MySQLdb.connect(host='localhost',user='root',passwd='Dyc19930418',
		port=3306,db='pythonsql')
curs=conn.cursor()

try:
	curs.execute('drop table food')
except Exception:	
	pass

curs.execute('''
		create table food(
		id			char(40)	primary key,
		description	char(200),
		water		float,
		kcal		float,
		protein		float,
		fat			float,
		ash			float,
		carbs		float,
		fiber		float,
		sugar		float
		);
		''')

query="insert into food values (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s);"#10 value to formatting
for line in open('ABBREV.txt'):
	fields=line.split('^')
	vals=[convert(f) for f in fields[:10]]
	#print vals
	#print query%tuple(vals)
	curs.execute(query,vals)
	#raw_input()
print 'Finished!'
conn.commit()
conn.close()
