#ifndef LOGIC_LOGIC_IPARSER_H_
#define LOGIC_LOGIC_IPARSER_H_

#include <logic/global>

#include <logic/IInstance.hpp>

#include <iostream>

namespace logic
{
	class LOGIC_API IParser
	{
	protected:
		IParser &operator=(IParser &) { return *this; }

	public:
		virtual ~IParser() = 0;

		virtual IInstance *parse(std::istream *in) = 0;
		virtual IInstance *parse(std::istream *in, std::ostream *out) = 0;

	}; // class IParser

	inline IParser::~IParser() { }

} // namespace logic

#endif // LOGIC_LOGIC_IPARSER_H_
