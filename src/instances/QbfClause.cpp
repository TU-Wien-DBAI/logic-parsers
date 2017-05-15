#include "../preamble.h"
#include "QbfClause.hpp"

#include <logic/IQbfInstance.hpp>

namespace logic
{
	using std::vector;

	QbfClause::~QbfClause() { }

	void QbfClause::setInstance(const IQbfInstance &instance)
	{
		instance_ = &instance;
	}

	void QbfClause::addVariable(variable_t variable)
	{
		addVariable(variable, false);
	}

	void QbfClause::addVariable(variable_t variable, bool negated)
	{
		variables_.insert(variable);
		if(negated)
			negated_.insert(variable);
	}

	void QbfClause::adjustVariables(const num_vector &adjustment)
	{
		variable_vector temp;
		temp.reserve(variables_.size());
		for(variable_t var : variables_)
			temp.push_back(var + adjustment[var]);
		variables_.clear();
		variables_.insert(temp.begin(), temp.end());
		temp.clear();

		temp.reserve(negated_.size());
		for(variable_t var : negated_)
			temp.push_back(var + adjustment[var]);
		negated_.clear();
		negated_.insert(temp.begin(), temp.end());
	}

	const IQbfInstance &QbfClause::instance() const
	{
		return *instance_;
	}

	bool QbfClause::contains(variable_t variable) const
	{
		return variables_.find(variable) != variables_.end();
	}

	bool QbfClause::isNegated(variable_t variable) const
	{
		return negated_.find(variable) != negated_.end();
	}

	bool QbfClause::checkSatisfaction(
			const variable_vector &trueVariables,
			const variable_vector &falseVariables) const
	{
		if(instance_->isCnf())
		{
			for(const variable_t variable : falseVariables)
				if(isNegated(variable))
					return true;

			for(const variable_t variable : trueVariables)
				if(contains(variable) && !isNegated(variable))
					return true;

			return false;
		}
		else
		{
			for(const variable_t variable : trueVariables)
				if(isNegated(variable))
					return false;

			for(const variable_t variable : falseVariables)
				if(contains(variable) && !isNegated(variable))
					return false;

			return true;
		}
	}

	IQbfClause::const_iterator QbfClause::begin() const
	{
		return IQbfClause::const_iterator(new ConstEnum(
					variables_.begin(),
					variables_.end()));
	}

	IQbfClause::const_iterator QbfClause::end() const
	{
		return IQbfClause::const_iterator(new ConstEnum(
					variables_.end()));
	}

} // namespace logic
