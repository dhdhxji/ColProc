import argparse
from pathlib import Path
import typing
import clang.cindex



def parse_args():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', help='Input class directory to analyze')
    parser.add_argument('-o', help='Class info json output')
    parser.add_argument('--include_path', nargs='+', default=[], help='Include directories path compile options')

    return parser.parse_args()



def filter_node_list_by_node_kind(
    nodes: typing.Iterable[clang.cindex.Cursor],
    kinds: list
) -> typing.Iterable[clang.cindex.Cursor]:
    result = []

    for i in nodes:
        if i.kind in kinds:
            result.append(i)

    return result



def filter_class_node_by_base_class(
    nodes: typing.Iterable[clang.cindex.Cursor],
    base_classes: typing.Iterable[str]
) -> typing.Iterable[clang.cindex.Cursor]:
    result = []
    for c in nodes:    
        c_base_classes = filter_node_list_by_node_kind(
            c.get_children(), 
            [clang.cindex.CursorKind.CXX_BASE_SPECIFIER]
        )

        for base_class in c_base_classes:
            if base_class.displayname.split()[1] in base_classes:
                result.append(c)

    return result



def filter_class_node_by_base_class_tree(
    nodes: typing.Iterable[clang.cindex.Cursor],
    base_class_names: typing.Iterable[str]
) -> typing.Iterable[clang.cindex.Cursor]:
    result = []

    while True:
        child_classes = filter_class_node_by_base_class(
            nodes, base_class_names
        )

        if len(child_classes) == 0:
            break

        result = result + child_classes
        base_class_names = list( (c.displayname for c in child_classes) )

    return result



def filter_class_unique_names(
    nodes: typing.Iterable[clang.cindex.Cursor]
) -> typing.Iterable[clang.cindex.Cursor]:
    class_names = set()
    result = []

    for c in nodes:
        if c.displayname not in class_names:
            class_names.add(c.displayname)
            result.append(c)

    return result



def find_colproc_classes(directory, include_path='') -> typing.Iterable[clang.cindex.Cursor]:
    result = []
    ccargs    = '-x c++ --std=c++11'.split() + [f'-I{path}' for path in include_path]
    for header in Path(directory).rglob('*.h'):
        index = clang.cindex.Index.create()
        translation_unit = index.parse(
            header,
            args=ccargs, 
            options=
                clang.cindex.TranslationUnit.PARSE_INCOMPLETE |
                clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES |
                0x4000  #https://clang.llvm.org/doxygen/group__CINDEX__TRANSLATION__UNIT.html#ggab1e4965c1ebe8e41d71e90203a723fe9a5493ee3e0dc0ee1ba0896fbf43938552
        )

        root_node = list(translation_unit.cursor.get_children())

        classes = filter_node_list_by_node_kind(
            root_node, 
            [clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL]
        )

        colproc_variable_classes = filter_class_node_by_base_class_tree (
            classes,
            ['ColProc', 'Variable']
        )

        result = result + colproc_variable_classes

    return filter_class_unique_names(result)



args = parse_args()
colproc_classes = find_colproc_classes(args.i, args.include_path)