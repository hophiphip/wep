CC=gcc
EMCC=emcc

CPPFILES=main.cpp
CPPBINAY=main

MODULENAME=$(shell basename $(CURDIR))
MODULEDIST=dist
MODULEPAGE=page

CCFLAGS=-std=c++20 -O2 -Wall -Wextra
EMCCFLAGS=-std=c++20 -O2 -Wall -Wextra

CCLIBS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lglad -lstdc++
EMCCLIBS=-lglfw -lGL -lX11 -lpthread -ldl -lstdc++

EMCCOPTIONS=-s USE_GLFW=3 -s WASM=3 -s MAX_WEBGL_VERSION=3 -s MIN_WEBGL_VERSION=3 -s EXPORT_ES6=1 -s MODULARIZE=1 -s EXPORT_NAME=$(MODULENAME) -s INVOKE_RUN=0 -s EXPORTED_FUNCTIONS='["_main"]' -s EXPORTED_RUNTIME_METHODS='["callMain"]' -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 -s EXIT_RUNTIME=0
EMCCPAGEOPTIONS=-s USE_GLFW=3 -s WASM=3 -s MAX_WEBGL_VERSION=3 -s MIN_WEBGL_VERSION=3

.PHONY: dist clean

dist:
	mkdir -p $(MODULEDIST)

compile:
	$(CC) $(CPPFILES) $(CCFLAGS) $(CCLIBS) -o $(CPPBINAY)

module:
	mkdir -p $(MODULEDIST) && $(EMCC) $(CPPFILES) $(EMCCFLAGS) $(EMCCLIBS) $(EMCCOPTIONS) -o $(MODULEDIST)/$(MODULENAME).js

page:
	mkdir -p $(MODULEPAGE) && $(EMCC) $(CPPFILES) $(EMCCFLAGS) $(EMCCLIBS) $(EMCCPAGEOPTIONS) -o $(MODULEPAGE)/index.html

clean:
	rm -rf $(MODULEPAGE)/* && rm -rf $(MODULEDIST)/*
    