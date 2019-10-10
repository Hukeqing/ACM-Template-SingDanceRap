# -*-conding=utf-8-*-
import os
import platform
import re

saver = open(os.path.join(os.path.abspath("."), "ACM-Template.txt"), "wb")
filelist = []
filelistpath = []
dirlist = []
for i, j, k in os.walk(os.path.abspath(".")):
    curdir = i.split("\\" if platform.system() == "Windows" else "/")
    if re.match(r'[0-9]', str(curdir[-1])):
        filelist.extend([x for x in k if x[-3:] == "cpp"])
        filelistpath.extend(
            [
                i + ("\\" if platform.system() == "Windows" else "/") + x
                for x in k
                if x[-3:] == "cpp"
            ]
        )
        dirlist.extend(j)
filelist.sort()
filelistpath.sort()
dirlist.sort()
curfile = 0
curdir = 0
while curdir < len(dirlist):
    if dirlist[curdir] < filelist[curfile]:
        saver.write(bytes("\t\t\t\t\t\t" + dirlist[curdir] + "\n", encoding="utf-8"))
        curdir += 1
    else:
        saver.write(
            bytes("\t\t\t\t\t\t" + filelist[curfile][:-4] + "\n\n\n", encoding="utf-8")
        )
        with open(filelistpath[curfile], "rb") as f:
            saver.write(f.read())
            saver.write(bytes("\n", encoding="utf-8"))
        curfile += 1
while curfile < len(filelist):
    saver.write(
        bytes("\t\t\t\t\t\t" + filelist[curfile][:-4] + "\n\n\n", encoding="utf-8")
    )
    with open(filelistpath[curfile], "rb") as f:
        saver.write(f.read())
        saver.write(bytes("\n", encoding="utf-8"))
    curfile += 1
