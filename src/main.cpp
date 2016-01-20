#include <iostream>
#include <tuple>
#include <string>
#include "integer_sequence.hpp"

// A class template that just a list of types:
template <class... T> struct typelist {};


int main(int argc, const char * argv[]) {
	make_integer_sequence<int, 3>();
	return 0;
}
