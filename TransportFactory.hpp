
#ifndef TRANSPORT_FACTORY_HPP
#define TRANSPORT_FACTORY_HPP

#include <string>
#include <list>
#include "TransportType.h"

namespace joby
{

    class Transport;
    class SimStats;

    class TransportFactory
    {
    public:
        static void Test();

        TransportFactory(SimStats& stats);
        ~TransportFactory();
        Transport* GetTransport(TransportType type);
        Transport* GetRandomTransport();
        void DestroyTransport(Transport* transport);
    private:
        void DeleteTransport(Transport* transport);

        SimStats& mStatsManager;
        std::list<Transport*> mAllocatedTransportList;
    }; // TransportFactory class

} // joby namespace

#endif // TRANSPORT_FACTORY_HPP
