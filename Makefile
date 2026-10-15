CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g -Iinclude
HEADERS  = $(wildcard include/*.h)

.PHONY: test clean

app: src/main.cpp src/money.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

run_tests: tests/test_money.cpp src/money.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

test: run_tests
	./run_tests

clean:
	rm -f app run_tests