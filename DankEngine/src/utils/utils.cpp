#include "utils.h"
#include <time.h>

namespace dank {
	unsigned int hash_string(const char* str) {
		unsigned int hash = 5381;
		int c;

		while (c = *str++) {
			hash = ((hash << 5) + hash) + c;
		}

		return hash;
	}

	unsigned long long mikrotime() {
		timeval val;
		gettimeofday(&val, 0);
		return (val.tv_sec * 1000000) + val.tv_usec;
	}
}