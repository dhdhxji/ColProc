import argparse
from pathlib import Path
import typing
import clang.cindex
import json



def parse_args():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', help='Input class directory to analyze')
    parser.add_argument('-o', default = '', help='Class info json output')
    parser.add_argument('--include_path', nargs='+', default=[], help='Include directories path compile options')
    parser.add_argument('--root_class', nargs='+', help='Root class names to search derived classes for')

    return parser.parse_args()



def class_get_base_class_names(
    c_class: clang.cindex.Cursor,
) -> typing.Iterable[str]:
    c_base_classes = filter_node_list_by_node_kind(
        c_class.get_children(), 
        [clang.cindex.CursorKind.CXX_BASE_SPECIFIER]
    )

    res = list([base.spelling.split()[-1] for base in c_base_classes])

    return res



def class_method_get_args_decl(
    c_method: clang.cindex.Cursor,
) -> typing.Iterable[dict]:
    """ 
    (
        {
            "type": "Variable<uint32_t>*",
            "name": "length"
        }
    )
    """ 
    return (
        {
            'type': ' '.join(t.spelling for t in param.get_tokens() if t.spelling != param.displayname),
            'name': param.displayname
        }
        for param in c_method.get_arguments()
    )



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
        c_base_classes = class_get_base_class_names(c)
        for base in c_base_classes:
            if base in base_classes:
                result.append(c)
                break

    return result



def filter_class_node_by_root_class(
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



def filter_class_non_abstract_class(
    nodes: typing.Iterable[clang.cindex.Cursor]
) -> typing.Iterable[clang.cindex.Cursor]:
    result = []
    for c in nodes: 
        if c.is_abstract_record() == False:
            result.append(c)

    return result        



def find_classes_by_root(
    directory, 
    root_classes,
    include_path=''
) -> typing.Iterable[clang.cindex.Cursor]:
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
            [clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.CLASS_TEMPLATE, clang.cindex.CursorKind.STRUCT_DECL]
        )

        root_classes_c = list(c for c in classes if c.displayname in root_classes)

        root_inherited_classes = filter_class_node_by_root_class (
            classes,
            root_classes
        )

        result = root_classes_c + result + root_inherited_classes

    return filter_class_unique_names(result)



def class_info_dict(
    c_class: clang.cindex.Cursor,
    root_class: str=''
) -> dict:
    """
    Output:
    {
        "className": "GeneratorRainbow",
        "rootClass": "ColProc",
        "baseClass": ["Generator"],
        "isAbstract": True,
        "constructors": [
            {
                "arguments": (
                    {
                        "type": "Variable<uint32_t>*",
                        "name": "length"
                    },
                    {
                        "type": "Variable<uint32_t>*",
                        "name": "angle"
                    },
                    {
                        "type": "Variable<uint32_t>*",
                        "name": "cycle_period_ms"
                    }
                )
            }
        ],
        "methods": [
            {
                "name": "someMethod",
                "returnType": "void",
                "arguments": (
                    {
                        "type": "Variable<uint32_t>*",
                        "name": "length"
                    },
                    {
                        "type": "Variable<uint32_t>*",
                        "name": "angle"
                    },
                    {
                        "type": "Variable<uint32_t>*",
                        "name": "cycle_period_ms"
                    }
                )
            }
        ],
        "fields": [
            {
                "name": "variable",
                "type": "int",
                "access": "public"
            }
        ]
    }
    """
    
    c_constructors = filter_node_list_by_node_kind(
        c_class.get_children(), [clang.cindex.CursorKind.CONSTRUCTOR]
    )

    c_methods = filter_node_list_by_node_kind(
        c_class.get_children(), [clang.cindex.CursorKind.CXX_METHOD]
    )

    c_fields = filter_node_list_by_node_kind(
        c_class.get_children(), [clang.cindex.CursorKind.FIELD_DECL]
    )

    constructors = tuple(
        {
            'access': c.access_specifier.name.lower(),
            'arguments': tuple(class_method_get_args_decl(c))
        }
        for c in c_constructors
    )

    methods = tuple(
        {
            'name': c.spelling,
            'returnType': c.result_type.spelling,
            'access': c.access_specifier.name.lower(),
            'arguments': tuple(class_method_get_args_decl(c))
        }
        for c in c_methods
    )

    fields = tuple(
        {
            'name': c.spelling,
            'type': c.type.spelling,
            'access': c.access_specifier.name.lower()
        }
        for c in c_fields
    )



    if root_class != c_class.displayname:
        return {
            'className': c_class.displayname,
            'headerPath': c_class.location.file.name,
            'rootClass': root_class,
            'baseClass': list(class_get_base_class_names(c_class)),
            'isAbstract': c_class.is_abstract_record(),
            'constructors': constructors,
            'methods': methods,
            'fields': fields
        }
    else:
        return {
            'className': c_class.displayname,
            'headerPath': c_class.location.file.name,
            'isAbstract': c_class.is_abstract_record(),
            'constructors': constructors,
            'methods': methods,
            'fields': fields
        }


###########################################################
# STAGE 1: Parse sources to find class to be serializable #
###########################################################
args = parse_args()

parsed_class_info = []
for root in args.root_class:
    #classes = filter_class_non_abstract_class(
    #    find_classes_by_root(args.i, (root, ), args.include_path)
    #)

    classes = find_classes_by_root(args.i, (root, ), args.include_path)

    parsed_class_info = parsed_class_info + list([class_info_dict(c, root_class=root) for c in classes])

###############################################################
# STAGE 2: Save class information for code generation utility #
###############################################################
json_output = json.dumps(
    parsed_class_info,
    indent=2
)

if(args.o != ''):
    with open(args.o, 'w') as f:
        f.write(json_output) 
else:
    print(json_output)
    
