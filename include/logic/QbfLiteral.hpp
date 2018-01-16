#ifndef LOGIC_LOGIC_QBFLITERAL_H_
#define LOGIC_LOGIC_QBFLITERAL_H_

#include <logic/global>
#include <logic/Variable.hpp>

namespace logic {
    
    class QbfLiteral
    {
    private:
        bool polarity_;
        variable_t variable_;
    
    public:
        QbfLiteral(variable_t variable, bool polarity);
        variable_t variable(void) const;
        bool polarity(void) const;
        bool operator==(const QbfLiteral & other) const;
        bool operator<(const QbfLiteral & other);
    };

    bool operator<(QbfLiteral that, QbfLiteral other);
    
}
#endif // LOGIC_LOGIC_QBFLITERAL_H_H
