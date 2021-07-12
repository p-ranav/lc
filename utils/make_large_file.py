import os

size = 1*1024*1024*1024 # 1 GB
with open('large_file_1GB', 'wb') as fout:
    fout.write(os.urandom(size)) 
