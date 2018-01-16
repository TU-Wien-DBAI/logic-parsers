#include "preamble.h"
#include <logic/parser.hpp>

#include <logic/ProceduralQbfInstanceBuilder.hpp>

#include "parsers/QDIMACSParser.hpp"
#include "instances/QbfClause.hpp"

#include <memory>
#include <stdexcept>

namespace logic
{
	namespace
	{
		IQDIMACSParserFactory *qdimacsParserFactory_ = nullptr;
		IQbfClauseFactory *qbfClauseFactory_ = nullptr;
		IQbfInstanceFactory *qbfInstanceFactory_ = nullptr;
	}

	void parser::set(IQDIMACSParserFactory *factory)
	{
		if(qdimacsParserFactory_)
			delete qdimacsParserFactory_;
		qdimacsParserFactory_ = factory;
	}

	void parser::set(IQbfClauseFactory *factory)
	{
		if(qbfClauseFactory_)
			delete qbfClauseFactory_;
		qbfClauseFactory_ = factory;
	}

	void parser::set(IQbfInstanceFactory *factory)
	{
		if(qbfInstanceFactory_)
			delete qbfInstanceFactory_;
		qbfInstanceFactory_ = factory;
	}

	IQDIMACSParser *parser::qdimacsParser()
	{
		if(qdimacsParserFactory_)
			return qdimacsParserFactory_->create();
		return new QDIMACSParser();
	}
	
	IQbfClause *parser::qbfClause()
	{
		if(qbfClauseFactory_)
			return qbfClauseFactory_->create();
		return new QbfClause();
	}

    ProceduralQbfInstanceBuilder * parser::qbfInstanceBuilder()
	{
		if(qbfInstanceFactory_)
			return qbfInstanceFactory_->create();
		return new ProceduralQbfInstanceBuilder();
	}

} // namespace logic

