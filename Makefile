# OSX Makefile, needs to know where the main src root is

build=build

CXXFLAGS=\
-Isrc/libmodplug \
-Isrc \
-DMODPLUG_BASIC_SUPPORT \

CFLAGS=$(CXXFLAGS)

objects   = $(patsubst src/%,build/%, $(patsubst %.cpp,%.bc, $(wildcard src/libmodplug/*.cpp)))
objects   += $(patsubst src/%,build/%, $(patsubst %.cpp,%.bc, $(wildcard src/*.cpp)))

sdlaudio: $(build) $(objects)
	EMCC_DEBUG=1 $(CXX) $(objects) -o $(build)/sdlaudio.bc
	EMCC_DEBUG=1 $(CXX) --closure 0 $(build)/sdlaudio.bc -o $(build)/sdlaudio.js

$(build)/%.bc: src/%.cpp
	EMCC_DEBUG=1 $(CXX) $(CXXFLAGS) -c $< -o $@

$(build)/%.bc: src/%.c
	EMCC_DEBUG=1 $(CC) $(CFLAGS) -c $< -o $@

$(build):
	mkdir -p $(build)
	mkdir -p $(build)/libmodplug

clean:
	rm -R /tmp/emscripten_temp
	rm a.out
	rm -Rf $(build)

install:
	ruby cache_manifest.rb assets > public/index.appcache
	cp -R assets public
	touch public/favicon.ico
	install -C index.html public
	install -C $(build)/sdlaudio.js public
