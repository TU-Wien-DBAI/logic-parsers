#ifndef LOGIC_LOGIC_IQBFINSTANCE_H_
#define LOGIC_LOGIC_IQBFINSTANCE_H_

#include <logic/global>

#include <logic/IInstance.hpp>
#include <logic/IQbfClause.hpp>
#include <logic/Id.hpp>
#include <logic/Clause.hpp>

#include <logic/helpers>

#include <unordered_set>

namespace logic
{

	class LOGIC_API IQbfInstance : public IInstance
	{
	protected:
		IQbfInstance &operator=(IQbfInstance &) { return *this; }

	public:
		typedef IConstEnumerator<IQbfClause>::Iterator const_iterator;

		virtual ~IQbfInstance() = 0;

		virtual void setCnf() = 0;
		virtual void setDnf() = 0;
		virtual void setVariableCount(variable_t variableCount) = 0;

		virtual void setQuantifierLevel(variable_t variable, short level) = 0;
		virtual IQbfClause &newClause() = 0;

		virtual bool isClause(id_t id) const = 0;
		virtual bool isVariable(id_t id) const = 0;
		virtual bool isExistential(variable_t variable) const = 0;
		virtual bool isUniversal(variable_t variable) const = 0;
		virtual short quantifierLevel(variable_t variable) const = 0;
		virtual short outermostQuantifierLevel() const = 0;
		virtual const std::unordered_set<variable_t> &variables(
				short level) const = 0;
		virtual variable_t variableCount() const = 0;
		virtual bool isCnf() const = 0;
		virtual bool isDnf() const = 0;

		virtual const IQbfClause &clause(clause_t clause) const = 0;

		virtual const_iterator begin() const = 0;
		virtual const_iterator end() const = 0;

	}; // class IQbfInstance

	inline IQbfInstance::~IQbfInstance() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFINSTANCE_H_
