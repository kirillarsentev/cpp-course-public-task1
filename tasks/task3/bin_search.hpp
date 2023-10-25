#pragma once
#include <iterator>
template <typename Itr, typename T>
Itr LowerBound(Itr first, Itr last, const T& value) {
	while (first != last) {
		int* middle = first + std::distance(first, last) / 2;
		if (*middle < value) {
			first = middle + 1;
		}
		else {
			last = middle;
		}
	}
	return last;
}