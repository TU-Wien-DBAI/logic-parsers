#ifndef LOGIC_LOGIC_IINSTANCE_H_
#define LOGIC_LOGIC_IINSTANCE_H_

#include <logic/global>

namespace logic
{
	class LOGIC_API IInstance
	{
	protected:
		IInstance &operator=(IInstance &) { return *this; }

	public:
		virtual ~IInstance() = 0;

	}; // class IInstance

	inline IInstance::~IInstance() { }
} // namespace logic

#endif // LOGIC_LOGIC_IINSTANCE_H_
