#!C:\python27\python.exe

print 'Content-type: text/html\n'

import cgitb;
cgitb.enable()

import MySQLdb
conn=MySQLdb.connect(host='localhost',user='root',passwd='Dyc19930418',
		port=3306,db='pythonsql')
curs=conn.cursor()

print """
<html>
 <head>
  <title>The David Bulletin Board</title>
 </head>
 <body>
  <h1>The David Bulletin Board</h1>
  """
dictindex=['id','subject','sender','reply_to','text']
curs.execute('select * from messages')
#originrows=curs.fetchall()

#rows={}
#for row in originrows:
#	rows[row[0]]=dict(zip(dictindex,row))

names=[d[0] for d in curs.description]
rows=[dict(zip(names,row)) for row in curs.fetchall()]

toplevel=[]
children={}

#for k,row in rows.items():
for row in rows:
	parent_id=row['reply_to']
	if parent_id is None:
		toplevel.append(row)
	else:
		children.setdefault(parent_id,[]).append(row)
	def format(row):
		print row['subject']
		try:
			kids=children[row['id']]
		except KeyError:
			pass
		else:
			print '<blockquote>'
			for kid in kids:
				format(kid)
			print '</blockquote>'
print '<p>'
for row in toplevel:
	format(row)
	
print """
		</p>
	 </body>
	</html>
	"""
