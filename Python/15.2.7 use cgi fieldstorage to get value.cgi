#!C:\Python27\python.exe

import cgi
form=cgi.FieldStorage()

name=form.getvalue('name','Unknown')

print 'Content-type:text/plain'
print
print 'Hello,%s!'%name
