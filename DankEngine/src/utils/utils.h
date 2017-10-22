#pragma once
namespace dank {
#	define MOFFSET(struct, member) (&((struct*)0)->member)

	unsigned int hash_string(const char* str);
	unsigned long long mikrotime();
}