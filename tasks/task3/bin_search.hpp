#pragma once
#include <iterator>
int* LowerBound(int* first, int* last, int value) {
	while (first != last) {
int* middle = first + std::distance(first, last) / 2;
if (*middle < value) {
first = middle + 1;
} else {
last = middle;
}
}
return last;
}
 