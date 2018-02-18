#include "../preamble.h"

#include <logic/CompactQbfInstance.hpp>
#include <logic/parser.hpp>
#include <logic/types.hpp>

#include <set>
#include <unordered_map>
#include <stdexcept>

namespace logic
{
    using std::set;
    using std::unordered_map;
    using std::unordered_set;
    using std::vector;
    using std::list;

    using std::invalid_argument;
    using std::logic_error;
    
    CompactQbfInstance::CompactQbfInstance(
        qbftype_t qbftype,
        variable_t numberVariables,
        const std::unordered_map<variable_t, quantifier_level_t> * quantifierLevels,
        std::list<std::set<QbfLiteral>*> * clauses)
    {
        m_qbftype = qbftype;
        m_numberVariables = numberVariables;
        m_numberQuantifierLevels = computeInnermostQuantifierLevel(quantifierLevels) + 1;
        m_quantifierLevels = *quantifierLevels;
        for (set<QbfLiteral> * literals : *clauses) {
            m_clauses.push_back(new CompactQbfClause(this, literals));
        }
    }

    CompactQbfInstance::~CompactQbfInstance()
    {
        for(IQbfClause *clause : m_clauses)
            delete clause;
    }

    bool CompactQbfInstance::isExistential(variable_t variable) const
    {
        int parity = (innermostQuantifierLevel() + quantifierLevel(variable)) % 2;
        return (m_qbftype == QBF_CNF) ? parity == 0 : parity == 1;
    }

    bool CompactQbfInstance::isUniversal(variable_t variable) const
    {
        return !isExistential(variable);
    }

    short CompactQbfInstance::quantifierLevel(variable_t variable) const
    {
        return m_quantifierLevels.find(variable)->second;
    }

    short CompactQbfInstance::innermostQuantifierLevel() const
    {
        return m_numberQuantifierLevels - 1;
    }

    bool CompactQbfInstance::isCnf() const
    {
        return m_qbftype == QBF_CNF;
    }

    bool CompactQbfInstance::isDnf() const
    {
        return m_qbftype == QBF_DNF;
    }

    const unordered_set<variable_t> & CompactQbfInstance::variables(quantifier_level_t level) const
    {
        unordered_set<variable_t> * variables = new unordered_set<variable_t>();
        for (variable_t variable = 1; variable <= m_numberVariables; variable++) {
            if (quantifierLevel(variable) == level) {
                variables->insert(variable);
            }
        }
        return *variables;
    }

    variable_t CompactQbfInstance::variableCount() const
    {
        return m_numberVariables;
    }

    IQbfInstance::const_iterator CompactQbfInstance::begin() const
    {
        return IQbfInstance::const_iterator(
            new ConstEnum(
                m_clauses.begin(),
                m_clauses.end()));
    }

    IQbfInstance::const_iterator CompactQbfInstance::end() const
    {
        return IQbfInstance::const_iterator(new ConstEnum(m_clauses.end()));
    }

    quantifier_level_t CompactQbfInstance::computeInnermostQuantifierLevel(
        const std::unordered_map<variable_t, quantifier_level_t> * quantifierLevels)
    {
        quantifier_level_t innermostLevel = 0;
        for (auto it : *quantifierLevels) {
            innermostLevel = (innermostLevel < it.second) ? it.second : innermostLevel;
        }
        return innermostLevel;
    }


    // legacy methods
    
    bool CompactQbfInstance::isClause(id_t id) const
    {
        throw "Unsupported operation: isClause(id_t id)";
    }

    bool CompactQbfInstance::isVariable(id_t id) const
    {
        throw "Unsupported operation: isVariable(id_t)";
    }

    const IQbfClause & CompactQbfInstance::clause(clause_t clause) const
    {
        return *m_clauses[clause - m_numberVariables - 1];
    }

} // namespace logic
