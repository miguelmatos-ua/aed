#
# makefile to compile all programs for the AED.P01 computer lab class
#

clean:
	rm -f a.out
	rm -f hello
	rm -f table
	rm -f sizes sizes_32 sizes_64
	rm -f fibonacci fibonacci_m
	rm -f factor solution_factor
	rm -f rational_approximation solution_rational_approximation solution_rational_approximation_p solution_rational_approximation_n

all:		hello table sizes fibonacci factor rational_approximation

run_all:	all
	@echo Run all demonstration programs
	./hello
	./table
	./sizes
	./fibonacci
	./fibonacci_m
	./factor 121 199 210 2147483647
	./rational_approximation
	@echo Done



hello:		hello.c
	cc -Wall -O2 hello.c -o hello



table:		table.c
	cc -Wall -O2 table.c -o table -lm



sizes:		main.c sizes.c sizes.h
	cc -Wall -O2 main.c sizes.c -o sizes

#
# on a 64-bit Ubuntu system, it may be necessary to do
#   sudo apt-get install gcc-multilib
# to install a version of the C compiler that recognizes the -m32 option
#
sizes_32:	main.c sizes.c sizes.h
	cc -m32 -Wall -O2 main.c sizes.c -o sizes_32

sizes_64:	main.c sizes.c sizes.h
	cc -m64 -Wall -O2 main.c sizes.c -o sizes_64



fibonacci:		fibonacci.c elapsed_time.h
	cc -Wall -O2 fibonacci.c -o fibonacci -lm

fibonacci_m:		fibonacci_with_a_macro.c elapsed_time.h
	cc -Wall -O2 fibonacci_with_a_macro.c -o fibonacci_m -lm



factor:		factor.c
	cc -Wall -O2 factor.c -o factor

solution_factor:		solution_factor.c elapsed_time.h
	cc -Wall -O2 solution_factor.c -o solution_factor



rational_approximation:		rational_approximation.c
	cc -Wall -O2 rational_approximation.c -o rational_approximation -lm

solution_rational_approximation:	solution_rational_approximation.c elapsed_time.h
	cc -Wall -O2 solution_rational_approximation.c -o solution_rational_approximation -lm

solution_rational_approximation_p:	solution_rational_approximation.c elapsed_time.h
	cc -Wall -O2 -DDEBUG=1 solution_rational_approximation.c -o solution_rational_approximation_p -lm

solution_rational_approximation_n:	solution_rational_approximation.c elapsed_time.h
	cc -Wall -O2 -DDEBUG=-1 solution_rational_approximation.c -o solution_rational_approximation_n -lm
