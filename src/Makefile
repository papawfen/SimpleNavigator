ifeq ($(shell uname), Linux)
	CHKFLAGS=-lgtest -lgtest_main -pthread -lrt -lm -lsubunit
else
	CHKFLAGS=-lgtest -lgtest_main
endif

PF=maze/
DISTDIR=build
ZIPNAME=A2_SimpleNavigator

all: install

s21_graph_algorithms.a: clean
	g++ -c s21*.cc salesman.cc ants/*.cc
	ar rcs s21_graph_algorithms.a *.o
	ranlib $@

install:
	@g++ -g *.cc ants/*.cc salesman.cc menu.cc -o build -lstdc++fs -std=c++17

clean:
	@rm -rf *.o
	@rm -rf *.a
	@rm -rf test
	@rm -rf build

tests:
	@g++ -g *.cc ants/*.cc salesman.cc tests.cc -o test $(CHKFLAGS) -lstdc++fs -std=c++17
	./test

style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cc ants/*.cc
	clang-format -i *.h ants/*.h
	clang-format -n *.cc ants/*.cc
	clang-format -n *.h ants/*.h
	rm .clang-format

.PHONY: style tests
