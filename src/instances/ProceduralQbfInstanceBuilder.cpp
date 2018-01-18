#include "../preamble.h"

#include <logic/ProceduralQbfInstanceBuilder.hpp>

#include <logic/CompactQbfInstance.hpp>
#include <logic/CompactQbfInstanceFactory.hpp>
#include <logic/parser.hpp>
#include <logic/types.hpp>

#include <vector>
#include <set>
#include <list>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

namespace logic
{
    using std::unordered_set;
    using std::vector;
    using std::list;
    using std::set;
    using std::unordered_map;

    using std::invalid_argument;
    using std::logic_error;

    ProceduralQbfInstanceBuilder::ProceduralQbfInstanceBuilder()
    {
        m_qbftype = QBF_CNF;
    }

    ProceduralQbfInstanceBuilder::~ProceduralQbfInstanceBuilder()
    {
        for (ProceduralQbfClauseBuilder * clause: m_clauses) {
            delete(clause);
        }
    }

    void ProceduralQbfInstanceBuilder::setCnf()
    {
        m_qbftype = QBF_CNF;
    }

    void ProceduralQbfInstanceBuilder::setDnf()
    {
        m_qbftype = QBF_DNF;
    }

    void findInstanceVariables(
        set<variable_t> * variables,
        const list<set<QbfLiteral> *> & clauses,
        const unordered_map<variable_t, quantifier_level_t> & quantifierPrefix)
    {
        for (auto clause : clauses) {
            for (auto literal : *clause) {
                variables->insert(literal.variable());
            }
        }
        for (auto kv : quantifierPrefix) {
            variables->insert(kv.first);
        }
    }
    
    IQbfInstance * ProceduralQbfInstanceBuilder::toInstance()
    {
        list<set<QbfLiteral> *> clauses;
        for (auto clause : m_clauses) {
            clauses.push_back(clause->toClause());
        }
        set<variable_t> variables;
        findInstanceVariables(&variables, clauses, m_quantifierLevels);
        CompactQbfInstance * instance = CompactQbfInstanceFactory().create(
            m_qbftype,
            &variables,
            &m_quantifierLevels,
            &clauses);

        for (auto clause : clauses) {
            free(clause);
        }
        
        return instance;
    }

    void ProceduralQbfInstanceBuilder::setQuantifierLevel(variable_t variable, quantifier_level_t level)
    {
        m_quantifierLevels.emplace(variable, level);
    }

    void ProceduralQbfInstanceBuilder::remove(const unordered_set<variable_t> &toRemove)
    {
        // remove variables from quantifier levels.
        for (variable_t variable : toRemove) {
            m_quantifierLevels.erase(variable);
        }
        // remove literals with the given variables from the clauses.
        for (ProceduralQbfClauseBuilder * clause : m_clauses) {
            for (variable_t variable : toRemove) {
                clause->removeLiterals(variable);
            }
        }
    }

    void ProceduralQbfClauseBuilder::removeLiterals(variable_t variable)
    {
        m_literals.erase(QbfLiteral(variable, POLARITY_POSITIVE));
        m_literals.erase(QbfLiteral(variable, POLARITY_NEGATIVE));
    }

    void ProceduralQbfClauseBuilder::addLiteral(variable_t variable, polarity_t polarity)
    {
        m_literals.insert(QbfLiteral(variable, polarity));
    }

    std::set<QbfLiteral> * ProceduralQbfClauseBuilder::toClause() const
    {
        return new set<QbfLiteral>(m_literals);
    }

    ProceduralQbfClauseBuilder & ProceduralQbfInstanceBuilder::addClause(void)
    {
        ProceduralQbfClauseBuilder * clause = new ProceduralQbfClauseBuilder();
        
        m_clauses.push_back(clause);
        
        return *clause;
    }
    
} // namespace logic
