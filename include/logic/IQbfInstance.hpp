/**
 * @file 
 */

#ifndef LOGIC_LOGIC_IQBFINSTANCE_H_
#define LOGIC_LOGIC_IQBFINSTANCE_H_

#include <logic/global>

#include <logic/IInstance.hpp>
#include <logic/IQbfClause.hpp>
#include <logic/Id.hpp>
#include <logic/Clause.hpp>

#include <logic/helpers>

#include <unordered_set>

namespace logic
{
    /**
     * @brief An interface for quantified boolean formulas.
     */
    class LOGIC_API IQbfInstance : public IInstance
    {
      protected:
        
        IQbfInstance &operator=(IQbfInstance &) { return *this; }

      public:
        
        typedef IConstEnumerator<IQbfClause>::Iterator const_iterator;

        virtual ~IQbfInstance() = 0;

        /** 
         * @brief Tests whether a given identifier is a clause.
         * @param id The identifier to be checked.
         * @return Returns `true` if the given identifier is
         * represents a clause in this QBF, `false` otherwise.
         */
        virtual bool isClause(id_t id) const = 0;

        /** 
         * @brief Tests whether a given identifier is a variable.
         * @param id The identifier to be checked.
         * @return Returns `true` if the given identifier is
         * represents a variable in this QBF, `false` otherwise.
         */
        virtual bool isVariable(id_t id) const = 0;

        /**
         * @brief Tests whether a variable is existentially
         * quantified.
         * @param variable The variable to be checked.
         * @return Returns `true` if the given variable is
         * existentially quantified in this QBF, `false` otherwise.
         */
        virtual bool isExistential(variable_t variable) const = 0;

        /**
         * @brief Tests whether a variable is universally
         * quantified.
         * @param variable The variable to be checked.
         * @return Returns `true` if the given variable is
         * universally quantified in this QBF, `false` otherwise.
         */
        virtual bool isUniversal(variable_t variable) const = 0;

        /**
         * @brief Retrieves the quantifier level of a given variable.
         * @param variable The variable whose quantifier level is
         * looked up.
         * @return The quantifier level of the given variable.
         */
        virtual short quantifierLevel(variable_t variable) const = 0;

        /**
         * @brief Retrieves the innermost quantifier level.
         */
        virtual short innermostQuantifierLevel() const = 0;

        /**
         * @brief Retrieves all variables in a given quantifier level.
         * @param The quantifier level for which the corresponding
         * variables are to be looked up.
         * @return The set of all variables that are bound by a
         * quantifier in the given level.
         */
        virtual const std::unordered_set<variable_t> &variables(
            unsigned short level) const = 0;

        /**
         * @brief Retrieves the number of variables used by this QBF.
         */
        virtual variable_t variableCount() const = 0;

        /**
         * @brief Tests whether a QBF is in CNF.
         * @return Returns `true` if the QBF is a CNF, `false` otherwise.
         */
        virtual bool isCnf() const = 0;

        /**
         * @brief Tests whether a QBF is in DNF.
         * @return Returns `true` if the QBF is a DNF, `false` otherwise.
         */
        virtual bool isDnf() const = 0;

        /**
         * @brief Retrieves clauses by index. 
         * @param clause An index representing a clause in this QBF.
         * @return The clause object associated to the given index.
         */
        virtual const IQbfClause &clause(clause_t clause) const = 0;

        virtual const_iterator begin() const = 0;

        virtual const_iterator end() const = 0;

    }; // class IQbfInstance

    inline IQbfInstance::~IQbfInstance() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFINSTANCE_H_
