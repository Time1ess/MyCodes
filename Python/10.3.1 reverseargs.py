#reverseargs.py
import sys
args=sys.argv[1:]
args.reverse()
print ' '.join(args)

#to test this, please use cmd like this
#python "10.3.1 reverseargs.py" this is a test
