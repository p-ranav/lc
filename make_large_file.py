import os

size = 5*1024*1024*1024 # 5GB
with open('large_file', 'wb') as fout:
    fout.write(os.urandom(size)) 
