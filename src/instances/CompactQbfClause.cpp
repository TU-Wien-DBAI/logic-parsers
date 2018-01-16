#include "../preamble.h"

#include <logic/CompactQbfInstance.hpp>

#include <logic/parser.hpp>
#include <logic/types.hpp>

#include <set>

namespace logic
{
    using std::set;
    
    CompactQbfInstance::CompactQbfClause::CompactQbfClause(
        CompactQbfInstance * instance, std::set<QbfLiteral> * literals)
    {
        m_instance = instance;
        for (QbfLiteral literal : *literals) {
            m_literals.push_back(literal);
        }
        // extract clause variables
        set<variable_t> variableBuffer;
        for (QbfLiteral literal : *literals) {
            variableBuffer.insert(literal.variable());
        }
        for (variable_t variable : variableBuffer) {
            m_variables.push_back(variable);
        }
    }

    CompactQbfInstance::CompactQbfClause::~CompactQbfClause() { }

    size_t CompactQbfInstance::CompactQbfClause::size() const
    {
        return m_literals.size();
    }

    bool CompactQbfInstance::CompactQbfClause::contains(variable_t variable) const
    {
        for (QbfLiteral literal : m_literals) {
            if (literal.variable() == variable) {
                return true;
            }
        }
        return false;
    }

    bool CompactQbfInstance::CompactQbfClause::isNegated(variable_t variable) const
    {
        for (QbfLiteral literal : m_literals) {
            if (literal.variable() == variable && literal.polarity() == POLARITY_NEGATIVE) {
                return true;
            }
        }
        return false;
    }

    IQbfClause::const_literal_iterator
    CompactQbfInstance::CompactQbfClause::beginLiterals() const
    {
        return IQbfClause::const_literal_iterator(
            new ConstLiteralEnum(
                m_literals.begin(),
                m_literals.end()));

    }

    IQbfClause::const_literal_iterator
    CompactQbfInstance::CompactQbfClause::endLiterals() const
    {
        return IQbfClause::const_literal_iterator(new ConstLiteralEnum(m_literals.end()));
    }

    IQbfClause::const_iterator
    CompactQbfInstance::CompactQbfClause::begin() const
    {
        return IQbfClause::const_iterator(new ConstEnum(m_variables.begin(), m_variables.end()));
    }

    IQbfClause::const_iterator
    CompactQbfInstance::CompactQbfClause::end() const
    {
        return IQbfClause::const_iterator(new ConstEnum(m_variables.end()));
    }

    const CompactQbfInstance & CompactQbfInstance::CompactQbfClause::instance() const
    {
        return *m_instance;
    }

    // legacy methods

    void CompactQbfInstance::CompactQbfClause::setInstance(const IQbfInstance &instance)
    {
        throw "Unsupported operation: setInstance";
    }

    void CompactQbfInstance::CompactQbfClause::addVariable(variable_t variable)
    {
        throw "Unsupported operation: addVariable";
    }

    void CompactQbfInstance::CompactQbfClause::addVariable(variable_t variable, bool negated)
    {
        throw "Unsupported operation: addVariable";
    }

    void CompactQbfInstance::CompactQbfClause::adjustVariables(const num_vector & adjustment)
    {
        throw "Unsupported operation: adjustVariables";
    }

    bool CompactQbfInstance::CompactQbfClause::checkSatisfaction(
        const variable_vector &trueVariables,
        const variable_vector &falseVariables) const
    {
        throw "Unsupported operation: checkSatisfaction()";
    }

} // namespace logic
