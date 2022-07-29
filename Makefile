CXX = g++
CXXFLAGS = -Wall -std=c++17 
SRC = $(SOURCE_SERVER) $(SOURCE_CLIENT) $(SOURCE_MYSOCKET) $(SOURCE_FILES) 
SERVER = server client
SOURCE_SERVER = source/server.cpp
SOURCE_CLIENT = source/client.cpp
SOURCE_MYSOCKET = source/mysocket.cpp
SOURCE_FILES = source/files.cpp
SERVER_SRC = $(SOURCE_SERVER) $(SOURCE_MYSOCKET) $(SOURCE_FILES)
CLIENT_SRC = $(SOURCE_CLIENT) $(SOURCE_MYSOCKET) $(SOURCE_FILES) 
OBJ = object/server.o object/client.o object/errproc.o
INCLUDE = include/errproc.hpp

all: $(SERVER)

clean:
	$(RM) $(OBJ) $(SERVER)

client: $(SRC)
	$(CXX) $(CFLAGS) $(CLIENT_SRC) -o client

server: $(SRC)
	$(CXX) $(CFLAGS) $(SERVER_SRC) -o server
