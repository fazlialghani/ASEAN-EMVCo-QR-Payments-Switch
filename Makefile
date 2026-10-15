CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g -Iinclude
HEADERS  = $(wildcard include/*.h)

.PHONY: test clean

app: src/main.cc src/money.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

run_tests: tests/test_money.cc src/money.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

test: run_tests
	./run_tests

clean:
	rm -f app run_tests