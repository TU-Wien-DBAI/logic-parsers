#include "preamble.h"
#include <logic/parser.hpp>

#include "parsers/QDIMACSParser.hpp"
#include "instances/QbfClause.hpp"
#include "instances/QbfInstance.hpp"

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

	IQDIMACSParser *parser::qbfParser()
	{
		if(qbfParserFactory_)
			return qbfParserFactory_->create();
		return new QDIMACSParser();
	}
	
	IQbfClause *parser::qbfClause(const IQbfInstance &instance)
	{
		if(qbfClauseFactory_)
			return qbfClauseFactory_->create(instance);
		return new QbfClause(instance);
	}

	IQbfInstance *parser::qbfInstance()
	{
		if(qbfInstanceFactory_)
			return qbfInstanceFactory_->create();
		return new QbfInstance();
	}

} // namespace logic

