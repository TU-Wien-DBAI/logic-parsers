#include "../preamble.h"
#include "QbfInstance.hpp"

#include <logic/parser.hpp>

#include <stdexcept>

namespace logic
{
	using std::unordered_map;
	using std::unordered_set;
	using std::vector;

	using std::invalid_argument;
	using std::logic_error;

	QbfInstance::~QbfInstance()
	{
		for(IQbfClause *clause : clauses_)
			delete clause;
	}

	IQbfInstance *QbfInstance::toInstance()
	{
		completeConstruction();
		return this;
	}

	void QbfInstance::setCnf()
	{
		throwIfCompleted();
		dnf_ = false;
	}

	void QbfInstance::setDnf()
	{
		throwIfCompleted();
		dnf_ = true;
	}

	void QbfInstance::setVariableCount(variable_t variableCount)
	{
		throwIfCompleted();

		if(clauses_.size() > 0)
			throw logic_error("Instance already has clauses.");

		unquantified_.clear();
		variables_.clear();
		quantifierLevels_.clear();
		variableCount_ = variableCount;

		unquantified_.reserve(variableCount_);
		for(variable_t var = 1; var <= variableCount; ++var)
			unquantified_.insert(var);
	}

	void QbfInstance::setQuantifierLevel(variable_t variable, short level)
	{
		throwIfCompleted();

		if(variable > variableCount_)
			throw invalid_argument("Argument 'variable' is not a variable.");
		if(unquantified_.find(variable) == unquantified_.end())
			throw invalid_argument("Argument 'variable' already has a level.");
		if(level < 0)
			throw invalid_argument("Argument 'level' cannot be negative.");

		unquantified_.erase(variable);
		setQuantifierLevelInternal(variable, level);
	}

	void QbfInstance::remove(const unordered_set<variable_t> &toRemove)
	{
		throwIfCompleted();

		// erase unused variables
		for(variable_t var : toRemove)
		{
			unquantified_.erase(var);

			auto it = quantifierLevels_.find(var);
			short level = -1;
			if(it != quantifierLevels_.end())
			{
				level = it->second;
				quantifierLevels_.erase(it);
			}

			if(level != -1)
				variables_[level].erase(var);
		}

		// compress the instance
		unsigned int substract = 0;
		num_vector adjustment;
		adjustment.reserve(variableCount_ + 1);
		adjustment.push_back(-substract);
		for(variable_t var = 1; var <= variableCount_; ++var)
		{
			adjustment.push_back(-substract);
			if(unquantified_.count(var) || quantifierLevels_.count(var))
			{
				if(!substract) continue;

				auto it = quantifierLevels_.find(var);
				if(it != quantifierLevels_.end())
				{
					quantifierLevels_[var - substract] = it->second;
					quantifierLevels_.erase(var);
					continue;
				}
	
				if(unquantified_.erase(var))
					unquantified_.insert(var - substract);
				continue;
			}

			++substract;
		}
		variableCount_ -= substract;

		// adjust clauses
		for(IQbfClause *clause : clauses_)
			clause->adjustVariables(adjustment);
	}

	IQbfClause &QbfInstance::addClause()
	{
		throwIfCompleted();

		IQbfClause *clause = parser::qbfClause();
		clause->setInstance(*this);
		clauses_.push_back(clause);
		return *clause;
	}

	bool QbfInstance::isClause(id_t id) const
	{
		return id > variableCount_
			&& id <= variableCount_ + clauses_.size();
	}

	bool QbfInstance::isVariable(id_t id) const
	{
		return id <= variableCount_;
	}

	bool QbfInstance::isExistential(variable_t variable) const
	{
		// if the quantifier level is even, and we are a cnf, return true
		// if the quantifier level is odd, and we are a dnf, return true
		return quantifierLevel(variable) % 2 == 0 ? !dnf_ : dnf_;
	}

	bool QbfInstance::isUniversal(variable_t variable) const
	{
		// if the quantifier level is odd, and we are a cnf, return true
		// if the quantifier level is even, and we are a dnf, return true
		return quantifierLevel(variable) % 2 == 0 ? dnf_ : !dnf_;
	}

	short QbfInstance::quantifierLevel(variable_t variable) const
	{
		auto it = quantifierLevels_.find(variable);
		if(it == quantifierLevels_.end())
		{
			return innermostQuantifierLevel();
		}
		return it->second + quantifierLevelModifier_;
	}

	short QbfInstance::innermostQuantifierLevel() const
	{
		return innermostQuantifierLevel_ + quantifierLevelModifier_;
	}

	const unordered_set<variable_t> &QbfInstance::variables(short level) const
	{
		if(level > innermostQuantifierLevel())
			throw invalid_argument("Argument 'level' is too high.");

		level -= quantifierLevelModifier_;

		auto it = variables_.find(level);
		if(it == variables_.end())
			throw logic_error("BUG: Instance incorrectly initialized.");

		return it->second;
	}

	variable_t QbfInstance::variableCount() const
	{
		return variableCount_;
	}

	bool QbfInstance::isCnf() const
	{
		return !dnf_;
	}

	bool QbfInstance::isDnf() const
	{
		return dnf_;
	}

	const IQbfClause &QbfInstance::clause(clause_t clause) const
	{
		if(!isClause(clause))
			throw std::invalid_argument("Argument 'clause' is not a clause.");

		return *clauses_[clause - variableCount_ - 1];
	}

	IQbfInstance::const_iterator QbfInstance::begin() const
	{
		return IQbfInstance::const_iterator(new ConstEnum(
					clauses_.begin(),
					clauses_.end()));
	}

	IQbfInstance::const_iterator QbfInstance::end() const
	{
		return IQbfInstance::const_iterator(new ConstEnum(clauses_.end()));
	}

	void QbfInstance::completeConstruction()
	{
		if(completed_) return;

		// check if we have something to do
		if(unquantified_.size() > 0)
		{
			short levelToSet;
			// check if the outermost quantifier is of the corret form
			// that is: exists for CNF, forall for DNF
			if(innermostQuantifierLevel_ % 2 == 0)
			{
				// if yes, simply set level 0 for unquantified_
				levelToSet = 0;
				quantifierLevelModifier_ = 0;
			}
			else // we need to introduce a new outermost quantifier
			{
				// set level -1, and set a +1 modifier
				levelToSet = -1;
				quantifierLevelModifier_ = 1;
			}

			for(variable_t var : unquantified_)
				setQuantifierLevelInternal(var, levelToSet);
			unquantified_.clear();
		}
		
		completed_ = true;
	}

	void QbfInstance::throwIfCompleted()
	{
		if(completed_)
			throw logic_error("Instance completed, can not be modified.");
	}

	void QbfInstance::setQuantifierLevelInternal(
			variable_t variable,
			short level)
	{
		quantifierLevels_[variable] = level;
		variables_[level].insert(variable);

		if(innermostQuantifierLevel_ < level)
			innermostQuantifierLevel_ = level;
	}


}// namespace logic
