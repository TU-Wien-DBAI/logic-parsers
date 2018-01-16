#ifndef LOGIC_LOGIC_TYPES_H_
#define LOGIC_LOGIC_TYPES_H_

#include <logic/Id.hpp>

namespace logic {
    typedef bool polarity_t;

    const polarity_t POLARITY_POSITIVE(false);
    const polarity_t POLARITY_NEGATIVE(true);

    typedef bool qbftype_t;

    const qbftype_t QBF_CNF(true);
    const qbftype_t QBF_DNF(false);

    typedef unsigned short quantifier_level_t;
    typedef id_t variable_t;
}

#endif // LOGIC_LOGIC_TYPES_H
