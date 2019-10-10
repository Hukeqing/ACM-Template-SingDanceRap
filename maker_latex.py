import json
import re
from pathlib import Path
from typing import Optional, List, Tuple
import platform


def str2utf(s):
    return bytes(s, encoding='utf-8')


class LatexJson:
    def __init__(self,
                 main_title: str,
                 subtitle: str,
                 author: str,
                 padding: Tuple[int, int, int, int],
                 direction_path: str = '',
                 decode_mode: str = 'utf-8',
                 logo_path: Optional[str] = '',
                 main_font: str = '',
                 code_font: str = '',
                 should_match: Optional[List[str]] = '',
                 ignore_list: Optional[List[str]] = '',
                 save_file: Optional[str] = ''):
        self.main_title = main_title
        self.subtitle = subtitle
        self.author = author
        self.padding = padding
        self.direction_path = '.' if direction_path == '' else direction_path
        self.decode_mode = 'utf-8' if decode_mode == '' else decode_mode
        self.logo_path = None if logo_path == '' else logo_path
        self.main_font = 'Microsoft YaHei' if main_font == '' else main_font
        self.code_font = 'Consolas' if code_font == '' else code_font
        self.should_match = [r'.+'] if should_match == '' else should_match if isinstance(should_match, list) else [should_match]
        self.ignore_list = [] if ignore_list == '' else ignore_list if isinstance(ignore_list, list) else [ignore_list]
        self.saver_file = 'Latex.tex' if save_file == '' else save_file


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
            self.main_font: str = notation['main_font']
            self.code_font: str = notation['code_font']
            self.should_match: List[str] = notation['should_match']
            self.ignore_list: List[str] = notation['ignore_list']
            self.saver_file = open(notation['saver_file'], 'wb')
        except:
            print('样式表(JSON)出错，请新建样式表')
            exit(-1)
        self.saver_file.write(str2utf(r'''
\documentclass{article}

\usepackage{listings}
\usepackage{fontspec, xunicode, xltxtra}
\usepackage{ctex}
'''))
        self.saver_file.write(str2utf(r'\setmainfont{' + self.main_font + '}\n'))
        self.saver_file.write(str2utf(r'\newfontfamily\codefont{' + self.code_font + '}\n'))
        self.saver_file.write(str2utf('''
\lstset{
    language    = c++,
    breaklines  = true,
    captionpos  = b,
    tabsize     = 4,
    numbers     = left,
    columns     = fullflexible,
    keepspaces  = true,
    basicstyle  = \small\codefont,
    showstringspaces = false,
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
            self.saver_file.write(str2utf(LatexCodeMaker.make_title(path_object.name, is_file=True, n=n)))
            self.saver_file.write(str2utf(r'\begin{lstlisting}' + '\n'))
            self.saver_file.write(LatexCodeMaker.read_file(path_object, self.decode_mode))
            self.saver_file.write(str2utf(r'\end{lstlisting}' + '\n'))
            return False
        elif path_object.is_dir():
            self.saver_file.write(str2utf(LatexCodeMaker.make_title(path_object.name, is_file=False, n=n)))
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

    @staticmethod
    def make_title(title, is_file, n=0):
        title = title.split(' ', 1)[-1].replace('%', '\%').replace('&', '\&').replace('~', '\~').replace('_', '\_').replace('^', '\^')
        if is_file:
            title = title[::-1].split('.', 1)[1][::-1]
        if n == 0:
            return '\section{' + title + '}\n'
        elif n == 1:
            return '\subsection{' + title + '}\n'
        else:
            return '\subsubsection{' + title + '}\n'

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
                               decode_mode=input('请输入文件编码格式("utf-8" or "gb2312"，默认为utf-8): '),
                               logo_path=input('请输入封面logo文件位置(可以使用相对位置，留空则无): '),
                               main_font=input('请输入文档目录等字体(留空为"Microsoft YaHei"): '),
                               code_font=input('请输入代码字体(留空为"Consolas"): '),
                               should_match=input('请输入需要处理的文件(文件夹)的文件名通用样式(留空则为全部文件，正则表达式全匹配模式，多种模式则用单个空格隔开): '),
                               ignore_list=input('请输入免处理的文件(文件夹)的文件名通用样式(留空则为全部文件，正则表达式全匹配模式，多种模式则用单个空格隔开): '),
                               save_file=input('请输入最终保存的文件名(默认为Latex.tex): '))
        self.data = json_class.__dict__
        op = input('完成设置(样式表/JSON文件: setting.json)！是否保存的设置？[Y/N]: ')
        if op not in ['n', 'N', 'no', 'No', 'NO']:
            with open(r'setting.json', 'w') as f:
                f.write(json.dumps(self.data))

    def get_data(self):
        return self.data


if __name__ == '__main__':
    LatexCodeMaker(LatexSetting().get_data())
