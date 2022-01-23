import argparse
from pathlib import Path
import clang.cindex

def parse_args():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', help='Input class directory to analyze')
    parser.add_argument('-o', help='Class info json output')
    parser.add_argument('--include_path', nargs='+', default=[], help='Include directories path compile options')

    return parser.parse_args()

args = parse_args()

for header in Path(args.i).rglob('*.h'):
    ccargs    = '-x c++ --std=c++11'.split() + [f'-I{path}' for path in args.include_path]
    
    index = clang.cindex.Index.create()
    translation_unit = index.parse(
        header,
        args=ccargs, 
        options=
            clang.cindex.TranslationUnit.PARSE_INCOMPLETE |
            clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES |
            0x4000  #https://clang.llvm.org/doxygen/group__CINDEX__TRANSLATION__UNIT.html#ggab1e4965c1ebe8e41d71e90203a723fe9a5493ee3e0dc0ee1ba0896fbf43938552
    )

    print(translation_unit)