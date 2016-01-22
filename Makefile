.PHONY: run deps clean-deps

run:
	mkdir -p build
	cd build && cmake ../ && make -j4
	./build/runner

deps:
	C_FLAGS=-fPIC cd external/libstemmer && make -j4
	cd external/googletest/googletest && autoreconf -ifv && ./configure && make -j4

clean-deps:
	cd external/libstemmer && make clean

upload-python:
	python setup.py sdist upload -r pypi

unit-test:
	cd build && cmake ../ && make unit_test_runner -j4
	./build/unit_test_runner
