#ifndef LOGIC_PARSERS_QDIMACSLEXER_H_
#define LOGIC_PARSERS_QDIMACSLEXER_H_

#include <logic/global>

#include "QDIMACSBisonParser.hpp"

typedef logic::QDIMACSBisonParser::token token;
typedef logic::QDIMACSBisonParser::token_type token_type;
typedef logic::QDIMACSBisonParser::semantic_type semantic_type;
typedef logic::QDIMACSBisonParser::location_type location_type;

#ifndef YY_DECL
#define YY_DECL						\
	token_type						\
	logic::QDIMACSLexer::lex(		\
		semantic_type *yylval,		\
		location_type *yylloc		\
	)
#endif // YY_DECL

#ifndef __FLEX_LEXER_H
#undef yyFlexLexer
#define yyFlexLexer QDIMACSFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif // __FLEX_LEXER_H

namespace logic
{
	class LOGIC_LOCAL QDIMACSLexer : public QDIMACSFlexLexer
	{
	public:
		QDIMACSLexer(std::istream *in = nullptr, std::ostream *out = nullptr);
		virtual ~QDIMACSLexer();

		virtual token_type lex(semantic_type *yylval, location_type *yylloc);

		void set_debug(bool debug);

	}; // class QDIMACSLexer

} // namespace logic

#endif /* LOGIC_PARSERS_QDIMACSLEXER_H_ */
