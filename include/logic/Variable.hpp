#ifndef LOGIC_LOGIC_VARIABLE_H_
#define LOGIC_LOGIC_VARIABLE_H_

#include <logic/global>

#include <logic/Id.hpp>

#include <vector>

namespace logic
{
	typedef id_t variable_t;
	typedef std::vector<variable_t> variable_vector;

	struct Variable
	{
	private:
		Variable();
	};

} // namespace logic

#endif // LOGIC_LOGIC_VARIABLE_H_
