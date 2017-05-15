#ifndef LOGIC_INSTANCES_QBFCLAUSE_H_
#define LOGIC_INSTANCES_QBFCLAUSE_H_

#include <logic/global>

#include <logic/IQbfClause.hpp>

#include <unordered_set>

namespace logic
{
	class LOGIC_LOCAL QbfClause : public IQbfClause
	{
	public:
		virtual ~QbfClause();

		virtual void setInstance(const IQbfInstance &instance) override;
		virtual void addVariable(variable_t variable) override;
		virtual void addVariable(variable_t variable, bool negated) override;
		virtual void adjustVariables(const num_vector &adjustment) override;

		virtual const IQbfInstance &instance() const override;
		
		virtual bool contains(variable_t variable) const override;
		virtual bool isNegated(variable_t variable) const override;

		virtual bool checkSatisfaction(
				const variable_vector &trueVariables,
				const variable_vector &falseVariables) const override;

		virtual const_iterator begin() const override;
		virtual const_iterator end() const override;

	private:
		const IQbfInstance *instance_;
		std::unordered_set<variable_t> variables_;
		std::unordered_set<variable_t> negated_;

		typedef ConstEnumerator<
			variable_t,
			std::unordered_set<variable_t>::const_iterator> ConstEnum;

	}; // class QbfClause

} // namespace logic

#endif // LOGIC_INSTANCES_QBFCLAUSE_H_
