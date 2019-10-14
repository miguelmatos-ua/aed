#
# makefile to compile all programs for the AED.P03 computer lab class
#

clean:
	rm -f a.out
	rm -f functions solution_functions
	rm -f find_pairs solution_find_pairs

all:			functions functions_extra find_pairs

solutions:		solution_functions


run_all:		all
	@echo Run all demonstration programs
	-./find_pairs 10000
	@echo Done


functions:		functions.c
	cc -Wall -O2 functions.c -o $@

functions_extra:	functions_extra.c
	cc -Wall -O2 functions_extra.c -o $@

solution_functions:	solution_functions.c
	cc -Wall -O2 solution_functions.c -o $@


find_pairs:		find_pairs.c
	cc -Wall -O2 find_pairs.c -o $@
