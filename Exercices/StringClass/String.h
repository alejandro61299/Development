#ifndef STRING_H
#define STRING_H

typedef unsigned int uint;

class String
{

private:
	char*       data;
	uint        alloc_memory;

public:
	String()
	{
		data = nullptr;
		alloc_memory = 0u;
	}

	String(const String &str)
	{
		data = new char[alloc_memory = str.alloc_memory];

		for (uint i = 0u; i < alloc_memory; i++)
		{
			data[i] = str.data[i];
		}
	}

	String(const char *str)
	{
		uint str_length = 0;

		while (str[str_length] != '\0')
		{
			str_length++;
		}

		data = new char[alloc_memory = str_length];

		for (uint i = 0; i < alloc_memory; i++)
		{
			data[i] = str[i];
		}
	}

	~String()
	{
		delete[] data;
	}

	String operator += (const String &str)
	{
		uint    new_length = alloc_memory + str.alloc_memory;
		char*   new_str = new char[new_length];

		for (uint i = 0; i < alloc_memory; i++) {
			new_str[i] = data[i];
		}
		for (uint i = 0; i < str.alloc_memory; i++) {
			new_str[alloc_memory + i] = str.data[i];
		}

		delete data;
		alloc_memory = new_length;
		data = new_str;

		return *this;
	}

	String operator + (const String &str)
	{
		return (*this += str);
	}

	String operator = (const String &str)
	{
		delete data;
		alloc_memory = str.alloc_memory;
		data = new char[alloc_memory];

		for (uint i = 0; i < alloc_memory; i++) {
			data[i] = str.data[i];
		}
		return *this;
	}

	bool operator == (const String &str) const
	{
		if (alloc_memory == str.alloc_memory) return false;
		uint n = 0;
		while (data[n] == str.data[n] && n < alloc_memory) n++;

		return (n == alloc_memory);
	}

	String operator += (const char *str)
	{
		String new_str(str);
		return (*this += new_str);
	}

	String operator + (const char *str)
	{
		String new_str(str);
		return (*this + new_str);
	}

	String operator = (const char *str)
	{
		return *this;
	}

	bool operator == (const char *str) const
	{
		String new_str(str);
		return (*this == new_str);
	}

};

#endif // !STRING_H

