import os
import platform

saver = open(os.path.join(os.path.abspath('.'), 'ACM-Template.txt'), 'w')
if platform.system() == 'Windows':
    minlist = len(os.path.abspath('.').split(r'\\'))
else:
    minlist = len(os.path.abspath('.').split(r'/'))
for i, j, k in os.walk(os.path.abspath('.')):
    if platform.system() == 'Windows':
        tmp = i.split(r'\\')
    else:
        tmp = i.split(r'/')
    saver.write('\t\t\t\t' + str(tmp[-1]) + '\n')
    k.sort()
    for item in k:
        if item[-3:] == 'cpp':
            saver.write("\n\n\t\t\t\t" + item[:-4] + '\n\n\n')
            with open(os.path.join(i, item), 'r') as f:
                saver.write(f.read())
