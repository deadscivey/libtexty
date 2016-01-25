.PHONY: run deps clean-deps build-python upload-python copy-data

run:
	mkdir -p build
	cd build && cmake ../ && make -j4
	./build/runner

deps:
	C_FLAGS=-fPIC cd external/libstemmer && make -j4
	cd external/googletest/googletest && autoreconf -ifv && ./configure && make -j4

clean-deps:
	cd external/libstemmer && make clean

copy-data:
	rm -rf textypy/data
	cp -r data textypy

build-python: copy-data
	python setup.py sdist

upload-python: copy-data
	python setup.py sdist upload -r pypi

unit-test:
	cd build && cmake ../ && make unit_test_runner -j4
	./build/unit_test_runner

func-test:
	cd build && cmake ../ && make func_test_runner -j4
	./build/func_test_runner
