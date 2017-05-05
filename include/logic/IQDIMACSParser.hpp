#ifndef LOGIC_LOGIC_IQDIMACSPARSER_H_
#define LOGIC_LOGIC_IQDIMACSPARSER_H_

#include <logic/global>

#include <logic/IParser.hpp>
#include <logic/IQbfInstance.hpp>

namespace logic
{
	class LOGIC_API IQDIMACSParser : public IParser
	{
	protected:
		IQDIMACSParser &operator=(IQDIMACSParser &) { return *this; }

	public:
		virtual ~IQDIMACSParser() = 0;

		virtual IQbfInstance *parse(std::istream *in) override = 0;
		virtual IQbfInstance *parse(
				std::istream *in,
				std::ostream *out) override = 0;

	}; // class IQDIMACSParser

	inline IQDIMACSParser::~IQDIMACSParser() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQDIMACSPARSER_H_
