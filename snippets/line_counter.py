import os
import re
import os.path as osp


included_exts = set(['.c', '.cpp', '.py', '.jsp', '.java', '.cs'])
excluded_path = ['lib', 'migrations', 'Django_Projects', 'Native']
excluded_path_pat = re.compile(r'|'.join(excluded_path))
excluded_fnames = ['agents.py', 'workflow.py']
excluded_fnames_pat = re.compile(r'|'.join(excluded_fnames))

lines = 0

logs = []
exts = set()

for base, dirs, files in os.walk('.'):
    if excluded_path_pat.search(base):
        continue
    for f in files:
        if excluded_fnames_pat.search(f):
            continue
        fname, ext = osp.splitext(f)
        if ext not in exts:
            exts.add(ext)
        if ext in included_exts:
            path = osp.join(base, f)
            with open(path, 'rb') as fp:
                line_count = len(fp.readlines())
                logs.append((path, line_count))
                lines += line_count

logs.sort(key=lambda x: x[1], reverse=True)
print(logs[:50])
print(lines)
