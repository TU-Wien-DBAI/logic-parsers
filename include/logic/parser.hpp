#ifndef LOGIC_LOGIC_PARSER_H_
#define LOGIC_LOGIC_PARSER_H_

#include <logic/global>

#include <logic/IQDIMACSParserFactory.hpp>
#include <logic/IQDIMACSParser.hpp>
#include <logic/IQbfInstanceFactory.hpp>
#include <logic/IQbfInstance.hpp>
#include <logic/IQbfClauseFactory.hpp>
#include <logic/IQbfClause.hpp>
#include <logic/ProceduralQbfInstanceBuilder.hpp>

namespace logic
{
	class LOGIC_API parser
	{
	public:

		static void set(IQDIMACSParserFactory *factory);
		static void set(IQbfInstanceFactory *factory);
		static void set(IQbfClauseFactory *factory);

		static IQDIMACSParser *qdimacsParser();

		static ProceduralQbfInstanceBuilder *qbfInstanceBuilder();
		
		static IQbfClause *qbfClause();
		
	private:
		parser();

	}; // class parser

} // namespace logic

#endif // LOGIC_LOGIC_PARSER_H_
