OBJECTS= xmlReader.o GeometryHandler.o IdentificatorHandler.o VertexHandler.o EdgeHandler.o StartVertexHandler.o EndVertexHandler.o FaceHandler.o LoopHandler.o BoundaryEdgeHandler.o

all: xmlReader.exe

xmlReader.exe: $(OBJECTS)
	g++-mp-4.7 -std=c++11 $+ -o $@ -I/opt/local/include -L/opt/local/lib -lxerces-c

%.o:%.cpp
	g++-mp-4.7 -MMD -MP -std=c++11 -c $< -o $@ -I/opt/local/include

-include $(OBJECTS:%.o=%.d)
