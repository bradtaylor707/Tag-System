ts.out : ts.cpp
	g++ -o ts.out ts.cpp

clean :
	rm -rf *.out *~ *.dSYM output.csv console.txt taylorTS*

rar :
	rm -rf *~ *.out taylorTS*
	mkdir taylorTS
	cp *.* taylorTS/
	cp makefile taylorTS/
	rar a -m5 -r -s taylorTS.rar taylorTS/