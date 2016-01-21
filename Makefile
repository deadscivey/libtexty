.PHONY: run deps clean-deps

run:
	mkdir -p build
	cd build && cmake ../ && make -j4
	./build/runner

deps:
	C_FLAGS=-fPIC cd external/libstemmer && make -j4

clean-deps:
	cd external/libstemmer && make clean
