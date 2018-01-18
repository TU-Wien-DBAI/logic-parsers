#ifndef LOGIC_LOGIC_PROCEDURALQBFINSTANCEBUILDER_H_
#define LOGIC_LOGIC_PROCEDURALQBFINSTANCEBUILDER_H_

#include <logic/global>

#include <logic/IQbfInstance.hpp>
#include <logic/IQbfClause.hpp>
#include <logic/Id.hpp>
#include <logic/Clause.hpp>
#include <logic/QbfLiteral.hpp>
#include <logic/types.hpp>

#include <list>
#include <set>
#include <unordered_map>

namespace logic
{
    /**
     * @brief Allows to construct QBF clauses procedurally.
     */
    class LOGIC_API ProceduralQbfClauseBuilder
    {
      public:

        /**
         * @brief Adds a literal to the clause.
         * @param variable The variable to be used for the literal.
         * @param polarity The variable's polarity in the literal.
         */
        void addLiteral(variable_t variable, polarity_t polarity);

        /**
         * @brief Removes all occurrences of a variable.
         * @param variable The variable to be removed.
         */
        void removeLiterals(variable_t variable);

        /**
         * @brief Retrieves the clause constructed by the builder.
         * @return The clause constructed so far. The caller is
         * responsible for freeing the clause.
         */
        std::set<QbfLiteral> * toClause() const;

      private:
        
        std::set<QbfLiteral> m_literals;
    };

    /**
     * @brief Allows to construct QBF's procedurally.
     * Procedural QBF Builders allow to construct QBF's in successive
     * steps.
     */
    class LOGIC_API ProceduralQbfInstanceBuilder
    {
      public:
        
        /**
         * @brief Constructs a new procedural QBF instance builder.
         */
        ProceduralQbfInstanceBuilder();

        /**
         * @brief Destroys this instance builder.
         * This frees all resources allocated by the instance builder
         * during its construction.
         */
        ~ProceduralQbfInstanceBuilder();

        /**
         * @brief Terminates the construction of a QBF.
         * After this method is called it is not possible to perform
         * constructions on formula.
         * @returns The newly constructed QBF. The caller is
         * responsible for freeing the instance.
         */
        IQbfInstance * toInstance();

        /**
         * @brief Tells the builder to construct a CNF.
         */
        void setCnf();

        /**
         * @brief Tells the builder to construct a DNF.
         */
        void setDnf();

        /**
         * @brief Sets the quantifier level for a variable.
         * If the quantifier level is set twice for the same variable,
         * then its level is the level specified by the most recent
         * call.
         * @param variable The variable for which the quantifier level
         * is set.
         * @param level The quantifier level to be set for the given
         * variable.
         */

        void setQuantifierLevel(variable_t variable, quantifier_level_t level);

        /**
         * @brief Removes the given variables from the resulting qbf
         * formula.
         * Unless a removed variable is again added later on, the
         * resulting formula will not contain any of the removed
         * variable.
         * @param toRemove A set of variables that is removed from
         * the QBF under construction.
         */
        void remove(const std::unordered_set<variable_t> &toRemove);

        /**
         * @brief Adds a new clause to the QBF under construction.
         * @returns A builder that represents the newly added clause.
         */
        ProceduralQbfClauseBuilder & addClause(void);

      private:
        
        std::list<ProceduralQbfClauseBuilder *> m_clauses;
        
        std::unordered_map<variable_t, unsigned short> m_quantifierLevels;
        qbftype_t m_qbftype;
    };

} // namespace logic

#endif // LOGIC_LOGIC_PROCEDURALQBFINSTANCEBUILDER_H_
