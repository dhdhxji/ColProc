import sys

print(f"hello, i am class parser! arg is {sys.argv[1]}")

with open(sys.argv[4], "w") as f:
    f.write('{}')