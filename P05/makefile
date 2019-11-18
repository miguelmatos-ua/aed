#
# makefile to compile all programs for the AED.P05 computer lab class
#

clean:
	rm -f a.out
	rm -f sList_test
	rm -f aStack_demo
	rm -f lQueue_demo

all:		aStack_demo sList_test

run_all:	all
	./sList_test
	./aStack_demo


sList_test:	sList_test.cpp sList.h
	c++ -Wall -O2 -std=c++0x sList_test.cpp -o $@

aStack_demo:	aStack_demo.cpp aStack.h
	c++ -Wall -O2 aStack_demo.cpp -o $@

lQueue_demo:	lQueue_demo.cpp lQueue.h
	c++ -Wall -O2 lQueue_demo.cpp -o $@
