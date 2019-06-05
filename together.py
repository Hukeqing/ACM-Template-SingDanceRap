import os
import platform

saver = open(os.path.join(os.path.abspath('.'), 'ACM-Template.txt'), 'w')
filelist = []
filelistpath = []
dirlist = []
for i, j, k in os.walk(os.path.abspath('.')):
    filelist.extend([x for x in k if x[-3:] == "cpp"])
    filelistpath.extend([i + ('\\' if platform.system() == 'Windows' else '/') + x for x in k if x[-3:] == "cpp"])
    dirlist.extend(j)
filelist.sort()
filelistpath.sort()
dirlist.sort()
curfile = 0
curdir = 0
while curdir < len(dirlist):
    if dirlist[curdir] < filelist[curfile]:
        saver.write('\t\t\t\t\t\t' + dirlist[curdir] + '\n')
        curdir += 1
    else:
        saver.write('\t\t\t\t\t\t' + filelist[curfile][:-4] + '\n\n\n')
        with open(filelistpath[curfile], 'r') as f:
            saver.write(f.read() + '\n')
        curfile += 1
while curfile < len(filelist):
    saver.write('\t\t\t\t\t\t' + filelist[curfile][:-4] + '\n\n\n')
    with open(filelistpath[curfile], 'r') as f:
        saver.write(f.read() + '\n')
    curfile += 1
