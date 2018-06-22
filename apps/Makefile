CXX = g++
CXXFLAGS = -O4 -std=c++14 -W -Wall
LIBFLGAS = -L .. -l griday

all: griday make_visit

make_visit: main.cpp ../libgriday.a
	$(CXX) $(CXXFLAGS) main.cpp $(LIBFLGAS) -o $(@)

griday:
	cd ..; make; cd apps

clean:
	rm make_visit; cd ..; make clean; cd apps
