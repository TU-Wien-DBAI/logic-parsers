#ifndef LOGIC_INSTANCES_QBFINSTANCE_H_
#define LOGIC_INSTANCES_QBFINSTANCE_H_

#include <logic/global>

#include <logic/IQbfInstance.hpp>
#include <logic/IQbfInstanceBuilder.hpp>
#include <logic/types.hpp>
#include <logic/QbfLiteral.hpp>

#include <set>
#include <unordered_map>
#include <vector>
#include <list>

namespace logic
{   
    class LOGIC_LOCAL CompactQbfInstance : public IQbfInstance {

      public:

        CompactQbfInstance(
            qbftype_t qbftype,
            variable_t numberVariables,
            const std::unordered_map<variable_t, quantifier_level_t> * quantifierLevels,
            std::list<std::set<QbfLiteral>*> * clauses);

        virtual ~CompactQbfInstance();

        // These methods are somewhat implementation dependent, it is
        // not clear whether we should keep them in the interface
        virtual bool isClause(id_t id) const override;
        virtual bool isVariable(id_t id) const override;

        // Can we abstract this by a single method? getQuantifier() : qbf_quantifier_t?
        virtual bool isExistential(variable_t variable) const override;
        virtual bool isUniversal(variable_t variable) const override;

        
        virtual short quantifierLevel(variable_t variable) const override;
        
        virtual short innermostQuantifierLevel() const override;
        
        virtual const std::unordered_set<variable_t> &variables(
            unsigned short level) const override;
        
        virtual variable_t variableCount() const override;
        
        virtual bool isCnf() const override;
        virtual bool isDnf() const override;

        // somehow deprecated (from the perspective of the
        // IQbfInstance interface)
        virtual const IQbfClause &clause(clause_t clause) const override;

        virtual const_iterator begin() const override;
        virtual const_iterator end() const override;

      private:

        typedef ConstEnumerator<
            IQbfClause, 
            std::vector<IQbfClause *>::const_iterator
          > ConstEnum;

        class CompactQbfClause : public IQbfClause
        {
        public:
            CompactQbfClause(CompactQbfInstance * instance, std::set<QbfLiteral> * literals);
            ~CompactQbfClause();

            size_t size() const;

            const CompactQbfInstance & instance() const;

            bool contains(variable_t variable) const;
            
            bool isNegated(variable_t variable) const;

            const_literal_iterator beginLiterals() const;
            const_literal_iterator endLiterals() const;

            const_iterator begin() const;
            const_iterator end() const;
            
            // legacy (throw exceptions)
            void setInstance(const IQbfInstance &instance);
            void addVariable(variable_t variable);
            void addVariable(variable_t variable, bool negated);
            void adjustVariables(const num_vector &adjustment);
            bool checkSatisfaction(
                const variable_vector &trueVariables,
                const variable_vector &falseVariables) const;


        private:
            typedef ConstEnumerator<
                variable_t, 
            std::vector<variable_t>::const_iterator
                > ConstEnum;
            
            typedef ConstEnumerator<
                QbfLiteral,
                std::vector<QbfLiteral>::const_iterator
                > ConstLiteralEnum;
            
        private:
            CompactQbfInstance * m_instance;
            std::vector<QbfLiteral> m_literals;
            std::vector<variable_t> m_variables;
        };

      private:
        
        logic::quantifier_level_t computeInnermostQuantifierLevel(
            const std::unordered_map<logic::variable_t, logic::quantifier_level_t> * quantifierLevels);

        
      private:

        qbftype_t m_qbftype = QBF_CNF;
        variable_t m_numberVariables = 0;
        quantifier_level_t m_numberQuantifierLevels = 0;
        unsigned int m_numberClauses = 0;

        std::unordered_map<variable_t, quantifier_level_t> m_quantifierLevels;
        std::vector<IQbfClause *> m_clauses;
        
    }; // class QbfInstance

} // namespace logic

#endif // LOGIC_INSTANCES_QBFINSTANCE_H_
