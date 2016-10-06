NAME=geograph3d

all:
	arm-linux-androideabi-g++ -c --sysroot=/Users/Alexander/Library/Android/sdk/ndk-bundle/platforms/android-18/arch-arm ../../node.cpp ../../edge.cpp ../../graph.cpp ../../roads.cpp ../../search.cpp ../../dijkstra.cpp	
	arm-linux-androideabi-ar -crs static/armeabi/$(NAME).a node.o edge.o graph.o roads.o search.o dijkstra.o
	rm -f *.o
	i686-linux-android-g++ -c --sysroot=/Users/Alexander/Library/Android/sdk/ndk-bundle/platforms/android-18/arch-arm ../../node.cpp ../../edge.cpp ../../graph.cpp ../../roads.cpp ../../search.cpp ../../dijkstra.cpp
	i686-linux-android-ar -crs static/x86/$(NAME).a node.o edge.o graph.o roads.o search.o dijkstra.o
	rm -f *.o
		