#ifndef LOGIC_LOGIC_IQBFINSTANCEBUILDER_H_
#define LOGIC_LOGIC_IQBFINSTANCEBUILDER_H_

#include <logic/global>

#include <logic/IQbfInstance.hpp>
#include <logic/IQbfClause.hpp>
#include <logic/Id.hpp>
#include <logic/Clause.hpp>

namespace logic
{

	class LOGIC_API IQbfInstanceBuilder
	{
	protected:
		IQbfInstanceBuilder &operator=(IQbfInstanceBuilder &) { return *this; }

	public:
		virtual ~IQbfInstanceBuilder() = 0;

		virtual IQbfInstance *toInstance() = 0;

		virtual void setCnf() = 0;
		virtual void setDnf() = 0;
		virtual void setVariableCount(variable_t variableCount) = 0;
		virtual void setQuantifierLevel(variable_t variable, short level) = 0;
		virtual IQbfClause &addClause() = 0;

	}; // class IQbfInstanceBuilder

	inline IQbfInstanceBuilder::~IQbfInstanceBuilder() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFINSTANCEBUILDER_H_
