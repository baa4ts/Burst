# Variables
CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2 -static -static-libgcc -static-libstdc++
# INCLUDES := -Ihelpers -Icore 
INCLUDES := -Iinclude
# LDFLAGS := -lssl -lcrypto -lws2_32 -lwsock32 -lcrypt32 -lWtsapi32
LDFLAGS := -ladvapi32

SRC := src/main.cpp
OUT := bin/server

# Compilar
$(OUT): $(SRC)
	clear
	@mkdir -p $(dir $(OUT))
	$(CXX) $(CXXFLAGS) -municode $(INCLUDES) $(SRC) -o $(OUT) $(LDFLAGS)

# Limpiar
clean:
	rm -rf bin/

.PHONY: clean
