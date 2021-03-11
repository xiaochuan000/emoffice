triConv: TriConverter.o
	g++ -o triConv TriConverter.o
	mv triConv $(EMoffice_HOME)/bin
TriConverter.o: TriConverter.cc
	g++ -c $<
clean:
	rm *.o *~ -f
