CXX = g++
CXXFLAGS = -Wall -std=c++17 
SRC = source/server.cpp source/client.cpp source/errproc.cpp
SERVER = server client
SERVER_OBJ = object/server.o
CLIENT_OBJ = object/client.o 
OBJ = object/server.o object/client.o object/errproc.o
INCLUDE = include/errproc.hpp

all: $(SERVER)

clean:
	$(RM) $(OBJ) $(SERVER)

client: $(SRC)
	$(CXX) $(CFLAGS) source/client.cpp source/errproc.cpp -o client

server: $(SRC)
	$(CXX) $(CFLAGS) source/server.cpp source/errproc.cpp -o server
