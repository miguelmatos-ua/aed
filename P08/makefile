#
# makefile to compile all programs for the AED.P08 computer lab class
#

clean:
	rm -f a.out
	rm -f binary_search
	rm -f count_words
	rm -f primes
	rm -f hash_count_words

.PHONY:		all
all:		binary_search count_words primes hash_count_words

binary_search:	binary_search.c
	cc -Wall -g binary_search.c -o binary_search

count_words:	count_words.cpp
	cc -Wall -g count_words.c -o count_words

primes:		primes.c
	cc -Wall -g primes.c -o primes

hash_count_words:	hash_count_words.c
	cc -Wall -g hash_count_words.c -o hash_count_words
