import argparse

parser = argparse.ArgumenParser(description='Creates an inverted index of tokens given a set of TXT files stored in a directory tree')
parser.add_argument('string', metavar='t', type=string, nargs=1,
	help='a character used for tokenizing a text stream')
parser.add_argument('string', metavar='o', type=string, nargs=1,
	help='the destination file')

