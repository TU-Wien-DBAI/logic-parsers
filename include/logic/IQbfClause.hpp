/**
 * @file
 */

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
        /** @brief Represents an iterator over variable occurrences. */
        typedef IConstEnumerator<variable_t>::Iterator const_iterator;

        /** @brief Represents an iterator over literal occurrences. */
        typedef IConstEnumerator<QbfLiteral>::Iterator const_literal_iterator;
        
      public:
        virtual ~IQbfClause() = 0;

        virtual const_literal_iterator beginLiterals() const = 0;
                
        virtual const_literal_iterator endLiterals() const = 0;
        
        /** 
         * @brief Retrieves the size of the clause.
         * @return The number of literals contained in the clause.
         */ 
        virtual size_t size() const = 0;

        virtual void setInstance(const IQbfInstance &instance) = 0;
                
        virtual void addVariable(variable_t variable) = 0;
                
        virtual void addVariable(variable_t variable, bool negated) = 0;
                
        virtual void adjustVariables(const num_vector &adjustment) = 0;

        virtual const IQbfInstance &instance() const = 0;

        /**
         * @brief Tests whether the given variable is contained in the
         * clause.
         * @param variable The variable that is to be tested.
         * @return Returns `true` if the given variable is contained
         * in the clause (negated or unnegated), `false` otherwise.
         */
        virtual bool contains(variable_t variable) const = 0;

        /**
         * @brief Tests whether a given variable occurs negated in a
         * clause.
         * @param variable The variable to be checked.
         * @return Returns `true` if the variable is negated in the
         * given clause.
         */
        virtual bool isNegated(variable_t variable) const = 0;

        virtual const_iterator begin() const = 0;
                
        virtual const_iterator end() const = 0;

        virtual bool checkSatisfaction(
            const variable_vector &trueVariables,
            const variable_vector &falseVariables) const = 0;

    }; // class IQbfClause

    inline IQbfClause::~IQbfClause() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFCLAUSE_H_
