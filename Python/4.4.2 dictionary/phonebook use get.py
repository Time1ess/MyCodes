people={
    'Alice':{
        'phone':'2341',
        'addr':'Foo drive 23'
        },
    'Beth':{
        'phone':'9102',
        'addr':'Bar street 42'
        },
    'Cecil':{
        'phone':'3158',
        'addr':'Baz avenue 90'
        }
    }

labels={
    'phone':'phone number',
    'addr':'address'
    }

name=raw_input("Name:")

request=raw_input("Phone number (p) or address (a)?")

if request=='p':key='phone'
if request=='a':key='addr'

person=people.get(name,{})
label=labels.get(key,key)
result=person.get(key,'not available')

print "%s's %s is %s." %\
   (name,label,result)
