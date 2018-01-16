
#include <logic/CompactQbfInstanceFactory.hpp>

#include <unordered_map>
#include <list>
#include <set>

namespace logic
{
    using std::unordered_map;
    using std::list;
    using std::set;
    
    CompactQbfInstance * CompactQbfInstanceFactory::create(
        qbftype_t qbftype,
        set<variable_t> * variables,
        unordered_map<variable_t, quantifier_level_t> * quantifierPrefix,
        list<set<QbfLiteral> *> * clauses) const
    {
        completeQuantifierPrefix(variables, quantifierPrefix);
        compressVariables(variables, quantifierPrefix, clauses);
        
        return new CompactQbfInstance(qbftype, variables->size(), quantifierPrefix, clauses);
    }

    void CompactQbfInstanceFactory::compressVariables(
        std::set<variable_t> * variables,
        std::unordered_map<variable_t, quantifier_level_t> * quantifierPrefix,
        std::list<set<QbfLiteral> *> * clauses) const
    {
        variable_t freeVariable = 1;
        for (variable_t currentVariable : * variables) {
            if (freeVariable != currentVariable) {
                renameVariable(currentVariable, freeVariable, quantifierPrefix, clauses);
            }
            freeVariable++;
        }
    }

    void CompactQbfInstanceFactory::completeQuantifierPrefix(
        const std::set<variable_t> * variables,
        std::unordered_map<variable_t, quantifier_level_t> * quantifierPrefix) const
    {
        for (variable_t variable : * variables) {
            if (quantifierPrefix->find(variable) == quantifierPrefix->end()) {
                quantifierPrefix->emplace(variable, 0);
            }
        }
    }

    void CompactQbfInstanceFactory::renameVariable(
        variable_t oldVariable,
        variable_t newVariable,
        std::unordered_map<variable_t, quantifier_level_t> * quantifierPrefix,
        std::list<std::set<QbfLiteral> *> * clauses) const
    {
        quantifier_level_t variableQuantifierLevel = quantifierPrefix->find(oldVariable)->second;
        quantifierPrefix->erase(oldVariable);
        quantifierPrefix->emplace(newVariable, variableQuantifierLevel);
        for (std::set<QbfLiteral> * clause : *clauses) {
            if (clause->find(QbfLiteral(oldVariable, POLARITY_POSITIVE)) != clause->end()) {
                clause->erase(QbfLiteral(oldVariable, POLARITY_POSITIVE));
                clause->insert(QbfLiteral(newVariable, POLARITY_POSITIVE));
            }
            if (clause->find(QbfLiteral(oldVariable, POLARITY_NEGATIVE)) != clause->end()) {
                clause->erase(QbfLiteral(oldVariable, POLARITY_NEGATIVE));
                clause->insert(QbfLiteral(newVariable, POLARITY_NEGATIVE));
            }
        }
    }
}
