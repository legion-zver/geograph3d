CFLAGS=-O2 -DNDEBUG -Wl --icf=safe -fexceptions -frtti
LDFLAGS=
NAME=geograph3d

all:	
	$(CXX) ../../node.cpp ../../edge.cpp ../../graph.cpp ../../roads.cpp ../../search.cpp ../../dijkstra.cpp main.cpp -o obj/$(NAME).o
	$(AR) rvs lib/lib$(NAME).a obj/$(NAME).o
	cp ../../node.hpp include/node.hpp
	cp ../../edge.hpp include/edge.hpp
	cp ../../graph.hpp include/graph.hpp
	cp ../../roads.hpp include/roads.hpp
	cp ../../search.hpp include/search.hpp
	cp ../../dijkstra.hpp include/dijkstra.hpp	