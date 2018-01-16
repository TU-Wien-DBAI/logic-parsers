#ifndef LOGIC_LOGIC_IQBFCLAUSE_H_
#define LOGIC_LOGIC_IQBFCLAUSE_H_

#include <logic/global>

#include <logic/Variable.hpp>
#include <logic/QbfLiteral.hpp>

#include <logic/helpers>

namespace logic
{
	class IQbfInstance;

	class LOGIC_API IQbfClause
	{
	protected:
		IQbfClause &operator=(IQbfClause &) { return *this; }

	public:
                // new stuff
                typedef IConstEnumerator<QbfLiteral>::Iterator const_literal_iterator;

                virtual const_literal_iterator beginLiterals() const = 0;
                virtual const_literal_iterator endLiterals() const = 0;

                virtual size_t size() const = 0;

                // old stuff
		typedef IConstEnumerator<variable_t>::Iterator const_iterator;

		virtual ~IQbfClause() = 0;

                // todo do we really need these here
		virtual void setInstance(const IQbfInstance &instance) = 0;
		virtual void addVariable(variable_t variable) = 0;
		virtual void addVariable(variable_t variable, bool negated) = 0;
		virtual void adjustVariables(const num_vector &adjustment) = 0;

                
		virtual const IQbfInstance &instance() const = 0;
		
		virtual bool contains(variable_t variable) const = 0;
		virtual bool isNegated(variable_t variable) const = 0;

                virtual const_iterator begin() const = 0;
                virtual const_iterator end() const = 0;

                // todo this is not really the responsibility of the clause
		virtual bool checkSatisfaction(
				const variable_vector &trueVariables,
				const variable_vector &falseVariables) const = 0;

	}; // class IQbfClause

	inline IQbfClause::~IQbfClause() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFCLAUSE_H_
