#ifndef STRING_H
#define STRING_H

typedef unsigned int uint;

class String
{
public:
	char*    data;
	uint     length;

	String()
	{
		data = new char[0];
		length = 0;
	}

	String(const String &str)
	{
		data = new char[length = str.length];

		for (uint i = 0; i < length; i++)
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

		data = new char[length = str_length];

		for (uint i = 0; i < length; i++)
		{
			data[i] = str[i];
		}
	}

	~String()
	{
		delete(data);
	}

	String operator += (const String &str)
	{
		uint    new_length = length + str.length;
		char*   new_str = new char[new_length];

		for (uint i = 0; i < length; i++) {
			new_str[i] = data[i];
		}
		for (uint i = 0; i < str.length; i++) {
			new_str[length + i] = str.data[i];
		}

		delete data;
		length = new_length;
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
		length = str.length;
		data = new char[length];

		for (uint i = 0; i < length; i++) {
			data[i] = str.data[i];
		}
		return *this;
	}

	bool operator == (const String &str) const
	{
		if (length == str.length) return false;
		uint n = 0;
		while (data[n] == str.data[n] && n < length) n++;

		return (n == length);
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

