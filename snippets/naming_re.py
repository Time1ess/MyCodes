import re


s = '''
David male 22 80
Sam male 19 76
Cindy female 17 90
'''

pat = re.compile(r'''
    \s*
    (?P<name>.*?)  # name
    \s+  # space
    (?P<gender>.*?)  # gender
    \s+  # space
    (?P<age>\d+)  # age
    \s+  # sapce
    (?P<score>\d+)  # score''', re.X | re.M)


for name, gender, age, score in (x.groups() for x in pat.finditer(s)):
    print('Name={}, Gender={}, Age={}, Score={}'.format(
        name, gender, age, score))
