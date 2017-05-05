#ifndef LOGIC_LOGIC_IQBFCLAUSE_H_
#define LOGIC_LOGIC_IQBFCLAUSE_H_

#include <logic/global>

#include <logic/QbfVariable.hpp>

#include <logic/helpers>

namespace logic
{
	class IQbfInstance;

	class LOGIC_API IQbfClause
	{
	protected:
		IQbfClause &operator=(IQbfClause &) { return *this; }

	public:
		typedef IConstEnumerator<variable_t>::Iterator const_iterator;

		virtual ~IQbfClause() = 0;

		virtual void addVariable(variable_t variable) = 0;
		virtual void addVariable(variable_t variable, bool negated) = 0;

		virtual const IQbfInstance &instance() const = 0;
		
		virtual bool contains(variable_t variable) const = 0;
		virtual bool isNegated(variable_t variable) const = 0;

		virtual bool checkSatisfaction(
				const variable_vector &trueVariables,
				const variable_vector &falseVariables) const = 0;

		virtual const_iterator begin() const = 0;
		virtual const_iterator end() const = 0;

	}; // class IQbfClause

	inline IQbfClause::~IQbfClause() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFCLAUSE_H_
