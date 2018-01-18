#ifndef LOGIC_LOGIC_IQBFINSTANCEFACTORY_H_
#define LOGIC_LOGIC_IQBFINSTANCEFACTORY_H_

#include <logic/global>

#include <logic/ProceduralQbfInstanceBuilder.hpp>

namespace logic
{
    /**
     * @brief Factory class for objects related to QBF's.
     */
    class LOGIC_API IQbfInstanceFactory
    {
      protected:
        IQbfInstanceFactory &operator=(IQbfInstanceFactory &) { return *this; }

      public:
        virtual ~IQbfInstanceFactory() = 0;

        /**
         * @brief Constructs a new procedural QBF builder.
         * @return A fresh QBF builder. The caller is responsible for
         * freeing the returned builder.
         */
        virtual ProceduralQbfInstanceBuilder * create() const = 0;

    }; // class IQbfInstanceFactory

    inline IQbfInstanceFactory::~IQbfInstanceFactory() { }

} // namespace logic

#endif // LOGIC_LOGIC_IQBFINSTANCEFACTORY_H_
