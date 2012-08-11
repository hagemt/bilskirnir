#!/usr/bin/python

import string

whitelist = ['htm', 'html', 'php']
blacklist = ['zip', 'ppt', 'pptx']

def crawlURL(URL):
	byte_count = 0
	harvested_URLs = []
	freq = {}
	return byte_count, harvested_URLs, freq

def crawlSite(rootURL):
	pass

def analyzeStats(byte_count, harvested_URLs, freq):
	pass
