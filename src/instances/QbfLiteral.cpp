
#include <logic/QbfLiteral.hpp>

namespace logic {
    
    QbfLiteral::QbfLiteral(variable_t variable, bool polarity)
    {
        this->variable_ = variable;
        this->polarity_ = polarity;
    }

    variable_t QbfLiteral::variable(void) const
    {
        return this->variable_;
    }

    bool QbfLiteral::polarity(void) const
    {
        return this->polarity_;
    }

    bool QbfLiteral::operator==(const QbfLiteral & other) const
    {
        return this->variable() == other.variable() && this->polarity() == other.polarity();
    }

    bool QbfLiteral::operator<(const QbfLiteral & other)
    {
        return this->polarity() < other.polarity() || this->variable() < other.variable();
    }

    bool operator<(QbfLiteral that, QbfLiteral other)
    {
        return that.operator<(other);
    }
    
}
