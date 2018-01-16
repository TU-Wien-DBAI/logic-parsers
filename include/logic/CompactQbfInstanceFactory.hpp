#ifndef LOGIC_LOGIC_COMPACTQBFINSTANCEFACTORY_H_
#define LOGIC_LOGIC_COMPACTQBFINSTANCEFACTORY_H_

#include <logic/CompactQbfInstance.hpp>
#include <logic/types.hpp>

#include <unordered_map>
#include <set>

namespace logic
{
    class CompactQbfInstanceFactory
    {
    public:
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
