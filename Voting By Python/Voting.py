import thread
import urllib2
import sys
import time
U='http://zmxc.scdy.net/?tag=vote_ok&id=338'
 
def reloader(numthread):
    while True:
        try:
            urllib2.urlopen(U)       
        except KeyboardInterrupt:
            sys.exit('\nProcess aborted.')
 
def splash():
    print U

 
if __name__ == '__main__':
    splash()
    print '\nVoting Program in Python2.7.Programed By Timeless\n'
    print '[!] Voting ' + U + ' with ' + '4' + ' threads.'
    for reloadspawn in range(0, 4):
        thread.start_new_thread(reloader, (reloadspawn,))
    sys.stdout.write('')
    dosind = ['begin', 'send', 'check', 'end']
    dosstat = 0
    while True:
        try:
            sys.stdout.write('\r    ' + ' Voting...' + dosind[dosstat] )
            sys.stdout.flush()
            dosstat = (dosstat + 1)%4
            time.sleep(0.02)
        except KeyboardInterrupt:
            sys.exit('\nProcess aborted.')
