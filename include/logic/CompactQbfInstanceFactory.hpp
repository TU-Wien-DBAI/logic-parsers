#ifndef LOGIC_LOGIC_COMPACTQBFINSTANCEFACTORY_H_
#define LOGIC_LOGIC_COMPACTQBFINSTANCEFACTORY_H_

#include <logic/CompactQbfInstance.hpp>
#include <logic/types.hpp>

#include <unordered_map>
#include <set>

namespace logic
{
    /**
     * @brief Factory for compact QBF's.
     */
    class CompactQbfInstanceFactory
    {
    public:

        /**
         * @brief Constructs a new compact QBF.
         * @param qbftype The new QBF's type (CNF or DNF).
         * @param variables The set of variables that is used by the
         * given clauses and the given quantifier levels.
         * @param quantifierLevels Associates some of the given
         * variables to a quantifier level.
         * @param clauses The clauses for the new QBF. The clause must
         * be constructed from the given variables.
         * @return A new compact QBF instance based on the given type,
         * variables, levels and clauses. If necessary the variables of the
         * returned QBF instance will be compacted by renaming. This
         * renaming can be reversed.
         */
        CompactQbfInstance * create(
            qbftype_t qbftype,
            std::set<variable_t> * variables,
            std::unordered_map<variable_t, quantifier_level_t> * quantifierLevels,
            std::list<std::set<QbfLiteral> *> * clauses) const;
    
    private:
        void renameVariable(
            variable_t oldVariable,
            variable_t newVariable,
            std::unordered_map<variable_t, quantifier_level_t> * quantifierPrefix,
            std::list<std::set<QbfLiteral> *> * clauses) const;

        void completeQuantifierPrefix(
            const std::set<variable_t> * variables,
            std::unordered_map<variable_t, quantifier_level_t> * quantifierPrefix) const;

        void compressVariables(
            std::set<variable_t> * variables,
            std::unordered_map<variable_t, quantifier_level_t> * quantifierPrefix,
            std::list<std::set<QbfLiteral> *> * clauses) const;
    };
}

#endif // LOGIC_LOGIC_COMPACTQBFINSTANCEFACTORY_H_
