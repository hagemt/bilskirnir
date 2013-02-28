#!/usr/bin/env python
# -*- coding: us-ascii -*-

# TODO can denote version info?
# Uses python 2.6.5

# Imports
import csv

# Constants
STATES_CSV_FILE = 'f.csv'
NUM_STATES = 50
N_MIN = 3

# Read from CSV file
def csv_from_file(filename):
	"""Load the csv data from a file and return a dictionary."""
	dictionary = dict()
	with open(filename, 'rb') as csvfile:
		fr = csv.reader(csvfile)
		for key, value in fr:
			num = int(value)
			assert num >= N_MIN
			dictionary[key] = num
	return dictionary

f = csv_from_file(STATES_CSV_FILE)
assert len(f) == NUM_STATES
N_DC = min(f.itervalues())
N_TOTAL = sum(f.itervalues()) + N_DC

for (state, amount) in f.iteritems():
	print state,'has',amount,'electoral votes'

print 'For DC:',N_DC
print 'Total:',N_TOTAL
