#ifndef LOGIC_PARSERS_QDIMACSPARSER_H_
#define LOGIC_PARSERS_QDIMACSPARSER_H_

#include <logic/global>

#include <logic/IQDIMACSParser.hpp>

namespace logic
{
	class LOGIC_LOCAL QDIMACSParser : public IQDIMACSParser
	{
	public:
		QDIMACSParser();
		virtual ~QDIMACSParser();

		virtual IQbfInstance *parse(std::istream *in) override;
		virtual IQbfInstance *parse(
				std::istream *in,
				std::ostream *out) override;

	}; // class QDIMACSParser

} // namespace logic

#endif // LOGIC_PARSERS_QDIMACSPARSER_H_
