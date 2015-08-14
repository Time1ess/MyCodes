name=raw_input('What is your name?')

if name.endswith('david'):
    if name.startswith('Mr.'):
        print 'Hello,Mr. David'
    elif name.startswith('Mrs.'):
        print 'Hello,Mrs. David'
    else:
        print 'Hello,David'
else:
    print 'Hello,Stranger'
