import argparse

def parse_args():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', help='Inout class directory to analyze')
    parser.add_argument('-o', help='Class info json output')

    return parser.parse_args()

args = parse_args()
print(args)