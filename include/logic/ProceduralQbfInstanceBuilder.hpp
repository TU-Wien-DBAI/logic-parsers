#ifndef LOGIC_LOGIC_PROCEDURALQBFINSTANCEBUILDER_H_
#define LOGIC_LOGIC_PROCEDURALQBFINSTANCEBUILDER_H_

#include <logic/global>

#include <logic/IQbfInstance.hpp>
#include <logic/IQbfClause.hpp>
#include <logic/Id.hpp>
#include <logic/Clause.hpp>
#include <logic/QbfLiteral.hpp>
#include <logic/types.hpp>

#include <list>
#include <set>
#include <unordered_map>

namespace logic
{
    class LOGIC_API ProceduralQbfClauseBuilder
    {
      public:
        void addLiteral(variable_t variable, polarity_t polarity);
        void removeLiterals(variable_t variable);
        
        std::set<QbfLiteral> * toClause() const;

      private:
        std::set<QbfLiteral> m_literals;
    };

    class LOGIC_API ProceduralQbfInstanceBuilder
    {
      public:
        
        // Constructs a new procedural qbf instance builder and
        // allocates resources.
        ProceduralQbfInstanceBuilder();

        // Frees the resources allocated during construction.
        ~ProceduralQbfInstanceBuilder();

        // Terminates the construction of the qbf instance and returns
        // a pointer to the instance. The caller is responsible for
        // the deallocation of the qbf instance.
        IQbfInstance * toInstance();

        // Tells the builder to construct a cnf qbf instance.
        void setCnf();

        // Tells the builder to construct a dnf qbf instance.
        void setDnf();

        // Sets the quantifier level for a variable.
        //
        // If the quantifier level is set twice for the same variable,
        // then its level is the level specified by the most recent call.    
        void setQuantifierLevel(variable_t variable, quantifier_level_t level);

        // Removes the given variables from the resulting qbf formula.
        //
        // Unless a removed variable is again added later on, the
        // resulting formula will not contain any of the removed variable.
        void remove(const std::unordered_set<variable_t> &toRemove);

        ProceduralQbfClauseBuilder & addClause(void);

      private:
        std::list<ProceduralQbfClauseBuilder *> m_clauses;
        std::unordered_map<variable_t, unsigned short> m_quantifierLevels;
        qbftype_t m_qbftype;
    };

} // namespace logic

#endif // LOGIC_LOGIC_PROCEDURALQBFINSTANCEBUILDER_H_
