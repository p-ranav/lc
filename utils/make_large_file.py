import os

size = 100*1024*1024*1024 # 100GB
with open('large_file_25GB', 'wb') as fout:
    fout.write(os.urandom(size)) 
