CXX = g++

CXXFLAGS = -Wall -g -pthread

cen: main.o Djikstra.o Bellman.o Floyds.o 
	$(CXX) $(CXXFLAGS) main.o Djikstra.o Bellman.o Floyds.o -o $@

main.o: ./Code/main.cpp ./Code/centralrouting.h
	$(CXX) $(CXXFLAGS) ./Code/main.cpp -c

Djikstra.o: ./Code/Djikstra.cpp ./Code/centralrouting.h
	$(CXX) $(CXXFLAGS) ./Code/Djikstra.cpp -c

Bellman.o: ./Code/Bellman.cpp ./Code/centralrouting.h
	$(CXX) $(CXXFLAGS) ./Code/Bellman.cpp -c

Floyds.o: ./Code/Floyds.cpp ./Code/centralrouting.h
	$(CXX) $(CXXFLAGS) ./Code/Floyds.cpp -c

seq: dist-vect-seq.o
	$(CXX) $(CXXFLAGS) ./Code/dist-vect-seq.o -o $@

dist-vect-seq.o: ./Code/dist-vect-seq.cpp
	$(CXX) $(CXXFLAGS) ./Code/dist-vect-seq.cpp -c

th: dist-vect-thread.o
	$(CXX) $(CXXFLAGS) dist-vect-thread.o -o $@

dist-vect-seq.o: ./Code/dist-vect-thread.cpp
	$(CXX) $(CXXFLAGS) ./Code/dist-vect-thread.cpp -c

clean:
	rm cen th seq
	rm *.o

trial_run:
	./cen < ./Input/500nodes.txt
	echo "threaded distance vector"
	./th ./Input/500nodes.txt
	echo "iterative distance vector"
	./seq ./Input/500nodes.txt	
