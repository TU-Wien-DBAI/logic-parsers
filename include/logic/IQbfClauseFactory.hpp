#ifndef LOGIC_LOGIC_IQBFCLAUSEFACTORY_H_
#define LOGIC_LOGIC_IQBFCLAUSEFACTORY_H_

#include <logic/global>

#include <logic/IQbfClause.hpp>

namespace logic
{
	class LOGIC_API IQbfClauseFactory
	{
	protected:
		IQbfClauseFactory &operator=(IQbfClauseFactory &) { return *this; }

	public:
		virtual ~IQbfClauseFactory() = 0;

		virtual IQbfClause *create() const = 0;

	}; // class IQbfClauseFactory

	inline IQbfClauseFactory::~IQbfClauseFactory() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFCLAUSEFACTORY_H_
