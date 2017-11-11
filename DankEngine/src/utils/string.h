#pragma once
#include <stdio.h>
#include "list.h"
#include "utils.h"

#include "utils/memory/memory.h"

namespace dank {

	class String {
	private:
		template<typename T>
		friend class List;
	public:
		char* str;
		size_t length;

		bool noDelete;

	public:
		String() { str = nullptr; length = 0; }
		String(const char* string);
		String(char* string, size_t length, bool noCopy = false);
		String(const String& string);
		String(const String* string);
		String(String&& string);
		~String();

		String& operator=(const String& string);
		String& operator=(String&& string);

		String& Append(const char character);
		String& Append(const String& string);
		inline String& operator<<(const String& string) { return Append(string); }
		inline String& operator<<(const char character) { return Append(character); }

		String& Insert(const String& string, size_t offset = 0);

		String& RemoveChars(const String& chars, bool iterate);
		String& Remove(const String& string);
		String& Remove(size_t start, size_t end);
		String& RemoveBlankspace();

		String  SubString(size_t start, size_t end) const;

		size_t Count(const String& string, size_t offset = 0) const;

		inline bool IsNull() const { return (str == nullptr || length == 0); }

		char operator[](size_t index) const;

		bool operator==(const String& string) const;
		bool operator!=(const String& string) const;
		String operator+(const String& string) const;
		inline void operator+=(const String& string) { Append(string); }
		inline void operator+=(const char character) { Append(character); }

		bool StartsWith(const String& string) const;
		bool EndsWith(const String& string) const;
		size_t Find(const String& string, size_t offset = 0) const;
		size_t Find(const char c, size_t offset = 0) const;

		List<String*> Split(const char delimiter) const;
		void Split(const char delimiter, List<String*>& list) const;

		inline char* operator*() const { return str; }

		inline void SetNoDelete(bool nodelete) { this->noDelete = nodelete; }

	};

}