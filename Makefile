CXX = g++
CXXFLAGS = -Wall -std=c++17 
SRC = $(SOURCE_SERVER) $(SOURCE_CLIENT) $(SOURCE_MYSOCKET) $(SOURCE_FILES) 
SERVER = server client
SOURCE_SERVER = source/server.cpp
SOURCE_CLIENT = source/client.cpp
SOURCE_MYSOCKET = source/mysocket.cpp
SOURCE_FILES = source/files.cpp
SOURCE_SEARCHIP = source/searchip.cpp
SOURCE_CHECKER = source/checker.cpp
SERVER_SRC = $(SOURCE_SERVER) $(SOURCE_MYSOCKET) $(SOURCE_FILES) $(SOURCE_SEARCHIP) $(SOURCE_CHECKER)
CLIENT_SRC = $(SOURCE_CLIENT) $(SOURCE_MYSOCKET) $(SOURCE_FILES) $(SOURCE_SEARCHIP) $(SOURCE_CHECKER)
INCLUDE = include/mysocket.hpp include/searchip.hpp include/checker.hpp

all: $(SERVER)

clean:
	$(RM) $(OBJ) $(SERVER)

client: $(SRC)
	$(CXX) $(CFLAGS) $(CLIENT_SRC) -o client

server: $(SRC)
	$(CXX) $(CFLAGS) $(SERVER_SRC) -o server
