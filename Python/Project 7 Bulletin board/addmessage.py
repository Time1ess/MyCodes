import MySQLdb
conn=MySQLdb.connect(host='localhost',user='root',passwd='Dyc19930418',
		port=3306,db='pythonsql')
curs=conn.cursor()

reply_to=raw_input('Reply to:')
subject=raw_input('Subject:')
sender=raw_input('Sender:')
text=raw_input('Text:')

if reply_to:
	query="""
	insert into messages(reply_to,sender,subject,text)
	values(%s,'%s','%s','%s')""" % (reply_to,sender,subject,text)
else:
	query="""
	insert into messages(sender,subject,text)
	values('%s','%s','%s')""" % (sender,subject,text)

curs.execute(query)
conn.commit()
