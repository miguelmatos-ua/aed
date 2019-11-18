#
# makefile to compile all programs for the AED.P04 computer lab class
#

clean:
	rm -f examples tsp a.out pt.svg assignment histograma*

all:		examples

run_all:	all
	./examples 2


examples:	examples.c
	cc -Wall -O2 examples.c -o $@ -lm

tsp:		tsp.c cities.h
	cc -Wall -O3 tsp.c -o tsp -lm

.PHONY:		extra
extra:		solution_tsp.c cities.h
	cc -Wall -O3 -march=native solution_tsp.c -lm

assignment:	assignment.c
	cc -Wall -O2 assignment.c -o $@ -lm

run: assignment
	./assignment -e
