# -*-conding=utf-8-*-
import os
import platform
import re
import functools


def cmp(a, b):
    if a.id < b.id:
        return -1
    return 1


def getid(t):
    return t.split(' ', 1)[0]


class cppfile:
    addtype = 'cpp'
    def __init__(self, *args):
        if len(args) == 2:
            self.allname = args[0]
            self.path = args[1]
            self.id = getid(args[0])
            self.name = args[0][:-4]
            self.filecpp = self.read()

    def read(self):
        try:
            file = open(self.path, 'rb')
        except Exception:
            exit('File miss: ' + self.path)
            # return 'File miss: ' + self.path
        return file.read()

    def writecpp(self, writepath):
        writepath.write(bytes('#### ' + self.name.replace(' ', '&nbsp;') + '\n', encoding='utf-8'))
        writepath.write(bytes('```' + cppfile.addtype + '\n', encoding='utf-8'))
        writepath.write(self.filecpp)
        writepath.write(bytes('\n```\n', encoding='utf-8'))

    def writetoc(self, writepath):
        # writepath.write(bytes(str([' ' for i in range(len(self.id) - 1)]) + self.name + '\n', encoding='utf-8'))
        writepath.write(bytes('&nbsp;&nbsp;' * (len(self.id) - 1) + '[' + self.name.replace(' ', '&nbsp;') + '](#' + self.name.replace(' ', '&nbsp;') + ')<br>\n', encoding='utf-8'))


class dirs:
    def __init__(self, *args):
        if len(args) == 2:
            self.name = args[0]
            self.id = getid(args[0])
            self.path = args[1]
            tmp = [item for item in os.listdir(args[1]) if re.match(r'[0-9]', item)]
            self.childlist = list()
            for item in tmp:
                if item[-3:] == 'cpp':
                    self.childlist.append(cppfile(item, os.path.join(args[1], item)))
                else:
                    self.childlist.append(dirs(item, os.path.join(args[1], item)))

    def writetoc(self, writepath):
        if self.name == "ACM-Template":
            writepath.write(bytes('# ' + self.name.replace(' ', '&nbsp;') + ' 目录\n', encoding='utf-8'))
        else:
            self.childlist.sort(key=functools.cmp_to_key(cmp))
            writepath.write(bytes('&nbsp;&nbsp;' * (len(self.id) - 1) + '[' + self.name.replace(' ', '&nbsp;') + '](#' + self.name.replace(' ', '&nbsp;') + ')<br>\n', encoding='utf-8'))
        for item in self.childlist:
            item.writetoc(writepath)

    def writecpp(self, writepath):
        if self.name == "ACM-Template":
            writepath.write(bytes('# ' + self.name.replace(' ', '&nbsp;') + '\n', encoding='utf-8'))
        else:
            writepath.write(bytes('#' * ((len(self.id) + 1) // 2) + '# ' + self.name.replace(' ', '&nbsp;') + '\n', encoding='utf-8'))
        for item in self.childlist:
            item.writecpp(writepath)


if __name__ == '__main__':
    saver = open(os.path.join(os.getcwd(), "ACM-Template.md"), "wb")
    maindirs = dirs('ACM-Template', os.getcwd())
    maindirs.writetoc(saver)
    maindirs.writecpp(saver)
