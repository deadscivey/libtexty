.PHONY: run run2

run:
	mkdir -p build
	cd build && cmake ../ && make -j4
	./build/runner

run2:
	