#!/bin/python3

import argparse

hp = {
		"filters" 	: [],
		"source"	: None,
		"target"	: None
	}

parser = argparse.ArgumentParser(description='Applies text normalization filters in the order in which filters are specified to the target text file.')

parser.add_argument('-rmcc', nargs='?', default=-1, help='Replace unicode control characters [ \\t\\n\\r\\f\\v] with a single white space.')
parser.add_argument('-rmpc', nargs='?', default=-1, help='Replace punctuation characters [!"#$%%&\'()*+, -./:;<=>?@[\]^_`{|}~]')
parser.add_argument('-rmnc', nargs='?', default=-1, help='Remove numeric characters [0-9]')
parser.add_argument('-rmsc', nargs='?', default=-1, help='Remove special characters except: a-zA-Z0-9 áéíóúÁÉÍÓÚâêîôÂÊÎÔãõÃÕçÇ:')
parser.add_argument('-ttlc', nargs='?', default=-1, help='Transform strings to lower case')
parser.add_argument('-regex', nargs='?', default=-1, help='Label string patterns that match regular expressions')

args = vars(parser.parse_args())

# sort the switches in increasing order of values
args = {k:v for k, v in sorted(args.items(), key=lambda v: int(v[1]) if isinstance(v[1],str) else v[1])}

# create the list of filters to apply
for key, value in args.items():
	if value != -1:
		hp["filters"].append(key)


