#ifndef LOGIC_LOGIC_IQBFINSTANCEFACTORY_H_
#define LOGIC_LOGIC_IQBFINSTANCEFACTORY_H_

#include <logic/global>

#include <logic/IQbfInstance.hpp>

namespace logic
{
	class LOGIC_API IQbfInstanceFactory
	{
	protected:
		IQbfInstanceFactory &operator=(IQbfInstanceFactory &) { return *this; }

	public:
		virtual ~IQbfInstanceFactory() = 0;

		virtual IQbfInstance *create() const = 0;

	}; // class IQbfInstanceFactory

	inline IQbfInstanceFactory::~IQbfInstanceFactory() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFINSTANCEFACTORY_H_
