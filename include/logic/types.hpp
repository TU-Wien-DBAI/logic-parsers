/**
 * @file
 */

#ifndef LOGIC_LOGIC_TYPES_H_
#define LOGIC_LOGIC_TYPES_H_

#include <logic/Id.hpp>

namespace logic {

    /** @brief Represents polarities in quantified boolean formulas.
     * The polarity of a symbol indicates whether the symbol is in the
     * scope of an even or odd number of negations. A positive
     * polarity indicates that the symbol is in the scope of an even
     * number of negations, whereas a negative polarity indicates an
     * odd number of enclosing negations.
     */
    typedef bool polarity_t;

    /** @brief Represents positive polarity. */
    const polarity_t POLARITY_POSITIVE(false);

    /** @brief Represents negative polarity. */
    const polarity_t POLARITY_NEGATIVE(true);

    /** @brief Represents the type of a QBF. 
     * A quantified boolean formula can either be in disjunctive
     * normal form (DNF) or in conjunctive normal form (CNF).
     */
    typedef bool qbftype_t;

    /** @brief Indicates that a formula is in conjunctive normal form. */
    const qbftype_t QBF_CNF(true);

    /** @brief Indicates a disjunctive normal form. */
    const qbftype_t QBF_DNF(false);

    /** @brief Represents quantifier levels. */
    typedef unsigned short quantifier_level_t;

    /** @brief Represents propositional variables. */
    typedef id_t variable_t;
}

#endif // LOGIC_LOGIC_TYPES_H
