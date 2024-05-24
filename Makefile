OS := $(shell uname)

# Default target
all: sender receiver

# Detect platform and set platform-specific flags and commands
ifeq ($(OS), Linux)
    PLATFORM := linux
    CXX := g++
    CXXFLAGS := -pthread
    LDFLAGS := -lrt
    EXEC_EXT := 
    CLEAN := rm -f sender receiver
else
    PLATFORM := windows
    CXX := g++
    CXXFLAGS := -lshlwapi
    LDFLAGS := 
    EXEC_EXT := .exe
    CLEAN := del sender.exe receiver.exe
endif

# Rules for building the sender and receiver
sender: sender.cpp
	$(CXX) sender.cpp -o sender$(EXEC_EXT) $(CXXFLAGS) $(LDFLAGS)

receiver: receiver.cpp
	$(CXX) receiver.cpp -o receiver$(EXEC_EXT) $(CXXFLAGS) $(LDFLAGS)

clean:
	$(CLEAN)
