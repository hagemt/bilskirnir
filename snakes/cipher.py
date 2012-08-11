#!/usr/bin/python

import array, random, re, string
non_letters = re.compile('[^a-z]*')

### Encryption/Decryption functions

def subCipherEncrypt(s, key):
	# Require exactly 26 unique characters for the alphabet
	if len(set(key)) != 26: return
	# Make encryption function (a dictionary mapping of key-value pairs)
	e = dict(zip(string.ascii_letters, key.lower() + key.upper()))
	# Fold into a ciphertext string using an adjudicated compression list
	c = ''.join([e[s[i]] if s[i] in e else s[i] for i in range(len(s))])
	print c

def subCipherDecrypt(s, key):
	# Require exactly 26 unique characters for the alphabet
	if len(set(key)) != 26: return
	# Make decryption function (a dictionary mapping of key-value pairs)
	d = dict(zip(key.lower() + key.upper(), string.ascii_letters))
	# Fold into a plaintext string using an adjudicated compression list
	p = ''.join([d[s[i]] if s[i] in d else s[i] for i in range(len(s))])
	print p

### Key Generation

def generateCipherKey(passcode = ''):
	# Construct the dichotomized alphabets
	uniq = set(passcode.lower())
	diff = set(string.ascii_lowercase) - uniq
	# Produce a prefix string and randomly premuted remainder
	prefix = ''.join(uniq)
	remainder = ''.join(random.sample(diff, len(diff)))
	print prefix + remainder

### Simple (2-adic) Transposition

def transposeEvenOdd(s):
	# Use compression lists to pick the even and odd indices
	seq = range(len(s))
	evens = ''.join([s[i] for i in seq if i % 2 == 0])
	odds = ''.join([s[i] for i in seq if i % 2 == 1])
	print evens + odds

def untransposeEvenOdd(s):
	# Find the string's splice point
	size = len(s) / 2
	# Make sure the string is of even length
	if size % 2 == 1:
		s += ' '
		size += 1
	# Splice the string there, zip together the halves, and accumulate
	acc = ''
	for e, o in zip(s[:size], s[size:]):
		acc += e
		acc += o
	print acc

### n-adic Transposition

def transpose(s, n=2):
	seq = range(len(s))
	# Basically accumulate the indices equal to k (mod n) for k in [1,n)
	acc = ''
	for k in range(n):
		acc += ''.join([s[i] for i in seq if i % n == k])
	print acc

print 'Transpose "The_quick_brown_fox_jumps_over_the_lazy_dog" using [2,6]:'
transpose('The_quick_brown_fox_jumps_over_the_lazy_dog', 2)
transpose('The_quick_brown_fox_jumps_over_the_lazy_dog', 3)
transpose('The_quick_brown_fox_jumps_over_the_lazy_dog', 4)
transpose('The_quick_brown_fox_jumps_over_the_lazy_dog', 5)
transpose('The_quick_brown_fox_jumps_over_the_lazy_dog', 6)

def untranspose(s, n=2):
	# Calculate the length and number of periods to skip before injecting
	l = len(s)
	p = l % n
	if p == 0:
		# Simply copy the string if its length is a multiple of n
		new_size = l
		arr = s
	else:
		# Otherwise, we need to inject some spaces after p periods
		period = l / n + 1
		# Use the modulus to make sure we have a multiple of n
		new_size = l + n - p
		# Make a scratch space to capture the modifications
		arr = array.array('c', '*' * new_size)
		# Iteratively fill the scratch (over i) refer to s (over j)
		i, j = 0, 0
		while i < new_size:
			arr[i] = s[j]
			i += 1
			j += 1
			# Modification rule:
			# Inject a space if the next index is periodically zero
			if (i + 1) % period == 0:
				# But skip this the first p times
				if p > 0:
					p -= 1
				else:
					arr[i] = ' '
					i += 1
	# Now our period is simply the length of each sub-sequence
	period = new_size / n
	# Accumulate these slices (see transpose)
	acc = ''
	for k in range(period):
		acc += ''.join([arr[k + i * period] for i in range(n)])
	print acc

print 'Recovering the original string (using untranspose on each):'
untranspose('Teqikbonfxjmsoe_h_aydgh_uc_rw_o_up_vrtelz_o', 2)
untranspose('T_i_o_xusv_ea_ghqcbwf_m_et_zdeukrnojporhlyo', 3)
untranspose('Tqkofjsehadhu_wou_rezoeibnxmo__yg_cr__pvtl_', 4)
untranspose('Tub_j__ldhirfuotaoecoomvhzg_kwxpeeyq_n_sr__', 5)
untranspose('Tioxs_aghcw__tzeknjohy___uve_qbfme_duroprlo', 6)

### Frequency Analysis

def setFrequency(s, p, n):
	# Require a non-zero normalization constant [usually len(set(s))]
	if n != 0:
		# Initialize a dictionary to store the element counts
		freq = dict([(l, 0) for l in set(p)])
		for e in s:
			if e in freq:
				freq[e] += 1
		# Print normalized frequencies in increasing (key) order
		for k in sorted(freq.keys()):
			print k, ':', float(freq[k]) / n

def letterFrequency(s):
	# Uses set frequency on the set of letters
	size = len(set(s))
	print 'total letters:', size
	setFrequency(s.lower(), string.ascii_lowercase, size)

def wordFrequency(s):
	# Uses set frequency on the set of words
	words = non_letters.split(s.lower())
	size = len(words)
	print 'total words:', size
	setFrequency(words, words, size)

### Testing

p = 'The quick brown fox'
c = 'Zit jxoea wkgvf ygb'
k = 'qwertyuiopasdfghjklzxcvbnm'
s = 'CheckItOut'
t = 'Teqikbonfxh uc rw o'
q = 'The brown fox jumps over the dog,gone!gone888gone'

print 'Encrypting "', p, '" with "', k, '" :'
subCipherEncrypt(p, k)
print 'Decrypting "', c, '" with "', k, '" :'
subCipherDecrypt(c, k)

print 'Generating key using "', s, '" :'
generateCipherKey(s)

print 'Transposing "', p, '" :'
transposeEvenOdd(p)
print 'Transposing "', t, '" :'
untransposeEvenOdd(t)

print 'Printing frequency analysis (letters/words):'
letterFrequency(p)
wordFrequency(q)

###############################################################################

import types

def isTuple(x): return type(x) == types.TupleType

def flatten(t):
	if not isTuple(t): return (t,)
	elif len(t) == 0: return ()
	else: return flatten(t[0]) + flatten(t[1:])

def untranspose_old(s, key=2):
	'This is shenanigans!'
	size = len(s)
	mod = size % key + key
	# Pull the data into a list of chunks
	start = end = 0
	chunks = []
	while start < size:
		end += (size / key)
		if mod > 0:
			end += 1
			mod -= 1
			sslice = s[start:end]
		else:
			sslice = s[start:end] + ' '
		chunks.append(list(sslice))
		start = end
	# Zip together the chunks and print in order
	for chunk in chunks:
		print '"', chunk, '"'
	for t in map(flatten, reduce(zip, chunks)):
		print t

print 'Using crazy transposition:'
untranspose_old('Teqikbonfxjmsoe_h_aydgh_uc_rw_o_up_vrtelz_o', 2)
untranspose_old('T_i_o_xusv_ea_ghqcbwf_m_et_zdeukrnojporhlyo', 3)
untranspose_old('Tqkofjsehadhu_wou_rezoeibnxmo__yg_cr__pvtl_', 4)
untranspose_old('Tub_j__ldhirfuotaoecoomvhzg_kwxpeeyq_n_sr__', 5)
untranspose_old('Tioxs_aghcw__tzeknjohy___uve_qbfme_duroprlo', 6)
