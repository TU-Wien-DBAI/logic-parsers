#ifndef LOGIC_LOGIC_IQDIMACSPARSERFACTORY_H_
#define LOGIC_LOGIC_IQDIMACSPARSERFACTORY_H_

#include <logic/global>

#include <logic/IQDIMACSParser.hpp>

namespace logic
{
	class LOGIC_API IQDIMACSParserFactory
	{
	protected:
		IQDIMACSParserFactory &operator=(IQDIMACSParserFactory &)
		{ return *this; }

	public:
		virtual ~IQDIMACSParserFactory() = 0;

		virtual IQDIMACSParser *create() const = 0;

	}; // class IQDIMACSParserFactory

	inline IQDIMACSParserFactory::~IQDIMACSParserFactory() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQDIMACSPARSERFACTORY_H_
