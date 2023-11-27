# python3
"""
> 此 python 代码将会帮你打包一个文件夹内的所有代码文件，并生成一个 Latex 文件

args 额外命令参数说明：

原则：出现相同/相同功能的参数时，后者参数会覆盖前者的参数，参数非法不会报错，但也不会生效。按照优先级小的先执行

命令列表：

1: -h           无参数，将文件和文件夹的名称第一段空格前面的所有内容不加入 Latex，可以改用 -fh, -dh 来只针对文件/文件夹生效，优先级：1

2: -e           无参数，将文件和文件夹的名称扩展名不加入 Latex，可以改用 -fe, -de 来只针对文件/文件夹生效，优先级：2
"""
import json
import re
from pathlib import Path
from typing import Optional, List, Tuple
import platform
import functools
import sys

str2utf = functools.partial(bytes, encoding='utf-8')


class Args:
    title_universal_args = {'-e': False, '-h': False,}
    title_detail_args = {'-de': False, '-dh': False,
                         '-fe': False, '-fh': False}

    def __init__(self, args):
        self.dict_args = dict()
        self.set_args = set()
        self.args_opt(args=args)

    def args_opt(self, args):
        argv = args.split()
        index = 0
        while index < len(argv):
            if argv[index] in Args.title_universal_args:
                if Args.title_universal_args[argv[index]]:
                    self.dict_args['-d' + argv[index][1:]] = argv[index + 1]
                    self.dict_args['-f' + argv[index][1:]] = argv[index + 1]
                    index += 1
                else:
                    self.set_args.add('-d' + argv[index][1:])
                    self.set_args.add('-f' + argv[index][1:])
            elif argv[index] in Args.title_detail_args:
                if Args.title_detail_args[argv[index]]:
                    self.dict_args[argv[index]] = argv[index + 1]
                    index += 1
                else:
                    self.set_args.add(argv[index])
            index += 1

    def in_set_args(self, arg):
        return arg in self.set_args

    def in_dict_args(self, arg):
        if arg in self.dict_args:
            return self.dict_args[arg]
        return None


class LatexJson:
    def __init__(self,
                 main_title: str,
                 subtitle: str,
                 author: str,
                 padding: Tuple[int, int, int, int],
                 direction_path: str = '',
                 decode_mode: str = 'utf-8',
                 logo_path: Optional[str] = '',
                 should_match: Optional[List[str]] = '',
                 ignore_list: Optional[List[str]] = '',
                 save_file: Optional[str] = '',
                 args: Optional[str] = ''):
        self.main_title = main_title
        self.subtitle = subtitle
        self.author = author
        self.padding = padding
        self.direction_path = '.' if direction_path == '' else direction_path
        self.decode_mode = 'utf-8' if decode_mode == '' else decode_mode
        self.logo_path = None if logo_path == '' else logo_path
        self.should_match = [r'.+'] if should_match == '' else should_match.split(' ')
        self.ignore_list = [] if ignore_list == '' else ignore_list.split(' ')
        self.saver_file = 'Latex.tex' if save_file == '' else save_file
        self.args = args


class LatexCodeMaker:
    def __init__(self, notation: dict):
        try:
            self.owner: Path = Path(notation['direction_path'])
            self.main_title: str = notation['main_title']
            self.subtitle: str = notation['subtitle']
            self.author: str = notation['author']
            self.padding: Tuple[int, int, int, int] = notation['padding']
            self.decode_mode: str = notation['decode_mode']
            self.logo_path: Optional[str] = notation['logo_path']
            self.should_match: List[str] = notation['should_match']
            self.ignore_list: List[str] = notation['ignore_list']
            self.saver_file = open(notation['saver_file'], 'wb')

            self.args = Args(notation['args'])
        except:
            print('样式表(JSON)出错，请新建样式表')
            exit(-1)
        self.saver_file.write(str2utf(r'''\documentclass{article}

\usepackage{listings, fontspec, xunicode, xltxtra, xcolor, ctex, xeCJK}

\setmainfont{NotoSans}[
    Path            = .fonts/,
    Extension       = .ttf,
    UprightFont     = *-Light,
    BoldFont        = *-Bold,
    ItalicFont      = *-LightItalic,
    BoldItalicFont  = *-BoldItalic
]

\setmonofont{RobotoMono}[
    Path            = .fonts/,
    Extension       = .ttf,
    UprightFont     = *-Light,
    BoldFont        = *-Bold,
    ItalicFont      = *-LightItalic,
    BoldItalicFont  = *-BoldItalic
]

\setCJKmainfont{NotoSansCJKsc}[
    Path            = .fonts/,
    Extension       = .otf,
    UprightFont     = *-Light,
    BoldFont        = *-Bold
]

\setCJKmonofont{NotoSansCJKsc}[
    Path            = .fonts/,
    Extension       = .otf,
    UprightFont     = *-Light,
    BoldFont        = *-Bold
]

\lstset{
    language            = c++,
    breaklines          = true,
    captionpos          = b,
    tabsize             = 4,
    numbers             = left,
    columns             = fixed,
    keepspaces          = true,
    keywordstyle        = \color{red}\bfseries,
    basicstyle          = \small\ttfamily,
    commentstyle        = \it\color[RGB]{100,100,100},
    showstringspaces    = false,
}
'''))
        self.init_tex()

    def init_tex(self):
        self.saver_file.write(
            str2utf(r'\usepackage[a4paper, left = ' + str(self.padding[0]) + 'mm, right = ' + str(self.padding[1]) + 'mm, top = ' + str(
                self.padding[2]) + 'mm, bottom = ' + str(self.padding[3]) + 'mm]{geometry}\n'))
        self.saver_file.write(str2utf(r'''
\begin{document}
\begin{titlepage}
\begin{center}
'''))

        # Title page and constant
        if self.logo_path is not None:
            self.saver_file.write(str2utf(r'\vspace*{0.5cm}\includegraphics[width=0.75\textwidth]{' + self.logo_path + r'} \\ [4cm]' + '\n'))
        self.saver_file.write(str2utf(r'\textbf{\Huge{' + self.main_title + r'}} \\ [1cm]' + '\n'))
        self.saver_file.write(str2utf(r'\LARGE{' + self.subtitle + r'} \\ [0.5cm]' + '\n'))
        self.saver_file.write(str2utf(r'\Large{' + self.author + '}\n'))
        self.saver_file.write(str2utf(r'''
\vfill
\large{\today}
\clearpage
\end{center}
\end{titlepage}

\small
\tableofcontents
\clearpage

\setcounter{section}{-1}
\setcounter{page}{1}

\clearpage
'''))

        self.direction_ergodic(self.owner)

        self.saver_file.write(str2utf(r'\end{document}'))
        self.saver_file.close()

    def add_tex(self, path_object: Path, n=0):
        if path_object.is_file():
            self.saver_file.write(str2utf(self.make_title(path_object.name, file_or_dir='f', n=n)))
            self.saver_file.write(str2utf(r'\begin{lstlisting}' + '\n'))
            self.saver_file.write(LatexCodeMaker.read_file(path_object, self.decode_mode))
            self.saver_file.write(str2utf(r'\end{lstlisting}' + '\n'))
            return False
        elif path_object.is_dir():
            self.saver_file.write(str2utf(self.make_title(path_object.name, file_or_dir='d', n=n)))
            return True

    def judge(self, name: str):
        for should_item in self.should_match:
            if re.fullmatch(should_item, name):
                for ignore_item in self.ignore_list:
                    if re.fullmatch(ignore_item, name):
                        return False
                return True
        return False

    def direction_ergodic(self, path_object: Path, n=0):
        dir_file: list = list(path_object.iterdir())
        dir_file.sort(key=lambda x: x.name.lower())
        for item in dir_file:
            if self.judge(item.name):
                if self.add_tex(item, n):
                    self.direction_ergodic(item, n + 1)

    def make_title(self, title, file_or_dir, n=0):
        title: str = title.replace('%', r'\%').replace('&', r'\&').replace('~', r'\~').replace('_', r'\_').replace('^', r'\^')
        if self.args.in_set_args('-' + file_or_dir + 'h'):
            title: str = title.split(maxsplit=1)[1]
        if self.args.in_set_args('-' + file_or_dir + 'e'):
            title: str = title[::-1].split('.', maxsplit=1)[1][::-1]
        if n == 0:
            return r'\section{' + title + '}\n'
        elif n == 1:
            return r'\subsection{' + title + '}\n'
        elif n == 2:
            return r'\subsubsection{' + title + '}\n'
        elif n == 3:
            return r'\paragraph{' + title + '}\n'
        else:
            return r'\subparagraph{' + title + '}\n'

    @staticmethod
    def read_file(path_object: Path, decode_mode):
        with path_object.open(mode='rb') as file:
            data = file.read().decode(decode_mode).encode('utf-8')
        if len(data) == 0 or data is None:
            return str2utf("")
        if data[-1] != '\n':
            data += str2utf('\n')
        # return data.replace(str2utf('%'), str2utf('\%')).replace(str2utf('&'), str2utf('\&')).replace(str2utf('~'), str2utf('\~')).replace(
        #     str2utf('_'), str2utf('\_')).replace(str2utf('^'), str2utf('\^'))
        return data


class LatexSetting:
    def __init__(self):
        self.data: dict = None
        try:
            with open(r'setting.json', 'r') as f:
                data = f.read()
            self.data = json.loads(data)
            if sys.argv[1] == 'Y':
                return
            op = input('读取到本地设置(样式表/JSON文件: setting.json)，是否使用已保存的设置？[Y/N]: ')
            if op in ['n', 'N', 'no', 'No', 'NO']:
                self.new_setting()
        except:
            print('本地设置(样式表/JSON文件: setting.json)未找到，将自动新建样式表')
            self.new_setting()

    def new_setting(self):
        json_class = LatexJson(main_title=input('请输入主标题: '),
                               subtitle=input('请输入副标题: '),
                               author=input('请输入作者: '),
                               padding=tuple([int(t) for t in input('请输入纸面边距(顺序: 左右上下，单位: mm，单个空格隔开): ').split(' ')]),
                               direction_path=input('请输入目录文件夹位置(可以使用相对位置，留空则为当前目录): '),
                               decode_mode=input('请输入你的文件(非输出文件，输出的tex文件默认为utf-8)编码格式("utf-8" or "gb2312"，默认为utf-8): '),
                               logo_path=input('请输入封面logo文件位置(可以使用相对位置，留空则无): '),
                               should_match=input('请输入需要处理的文件(文件夹)的文件名通用样式(留空则为全部文件，正则表达式全匹配模式，多种模式则用单个空格隔开): '),
                               ignore_list=input('请输入免处理的文件(文件夹)的文件名通用样式(留空则为全部文件，正则表达式全匹配模式，多种模式则用单个空格隔开): '),
                               save_file=input('请输入最终保存的文件名(默认为Latex.tex): '),
                               args=input('请输入额外参数(具体请参考python代码最上方的说明): '))
        self.data = json_class.__dict__
        op = input('完成设置(样式表/JSON文件: setting.json)！是否保存的设置？[Y/N]: ')
        if op not in ['n', 'N', 'no', 'No', 'NO']:
            with open(r'setting.json', 'w') as f:
                f.write(json.dumps(self.data))

    def get_data(self):
        return self.data


if __name__ == '__main__':
    LatexCodeMaker(LatexSetting().get_data())
