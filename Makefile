CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g -Iinclude
HEADERS  = $(wildcard include/*.h)

.PHONY: test clean

app: src/main.cc src/money.cc src/currency.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

run_tests: tests/test_money.cc src/money.cc src/currency.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

run_tlv_tests: tests/test_tlv.cc src/tlv.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

run_crc_tests: tests/test_crc.cc src/crc.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

run_ledger_tests: tests/test_ledger.cc src/ledger.cc src/money.cc src/currency.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

run_scheme_tests: tests/test_scheme.cc src/scheme.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) $(filter %.cc,$^) -o $@

test: run_tests run_tlv_tests run_crc_tests run_ledger_tests
	./run_tests
	./run_tlv_tests
	./run_crc_tests
	./run_ledger_tests

clean:
	rm -rf app run_tests run_tlv_tests run_crc_tests run_ledger_tests *.dSYM