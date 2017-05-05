#include "../preamble.h"
#include "QDIMACSParser.hpp"

#include "QDIMACSBisonParser.hpp"
#include "QDIMACSLexer.hpp"

#include <logic/parser.hpp>

#include <iostream>

namespace logic
{
	using std::istream;
	using std::ostream;

	QDIMACSParser::QDIMACSParser() { }

	QDIMACSParser::~QDIMACSParser() { }

	IQbfInstance *QDIMACSParser::parse(istream *in)
	{
		return this->parse(in, nullptr);
	}

	IQbfInstance *QDIMACSParser::parse(istream *in, ostream *out)
	{
		IQbfInstance *result = parser::qbfInstance();

		//TODO: proper error handling
		//if(!result) return nullptr;

		QDIMACSLexer *lexer = new QDIMACSLexer(in, out);
		QDIMACSBisonParser *parser = new QDIMACSBisonParser(*lexer, *result);

		bool error = parser->parse();

		delete parser;
		delete lexer;

		//TODO: proper error handling
		if(error)
		{
			delete result;
			return nullptr;
		}

		return result;
	}

} // namespace logic
