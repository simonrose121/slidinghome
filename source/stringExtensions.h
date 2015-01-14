#include <string>
#include <sstream>

class StringExtensions
{
public:
	StringExtensions() {};
	~StringExtensions() {};

	template <typename T>
	std::string to_string(T value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}
};