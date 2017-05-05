#ifndef LOGIC_LOGIC_CLAUSE_H_
#define LOGIC_LOGIC_CLAUSE_H_

#include <logic/global>

#include <logic/Id.hpp>

#include <vector>

namespace logic
{
	typedef id_t clause_t;
	typedef std::vector<clause_t> clause_vector;

	struct Clause
	{
	private:
		Clause();
	};

} // namespace logic

#endif // LOGIC_LOGIC_CLAUSE_H_
