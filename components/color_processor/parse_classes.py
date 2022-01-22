import argparse
from pathlib import Path

def parse_args():
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', help='Input class directory to analyze')
    parser.add_argument('-o', help='Class info json output')

    return parser.parse_args()

args = parse_args()

for header in Path(args.i).rglob('*.h'):
    print(f'Header {header}')