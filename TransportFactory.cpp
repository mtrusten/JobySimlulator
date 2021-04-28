
#include "TransportFactory.hpp"

#include <stdexcept> // std::runtime_error
#include <cstdlib> // rand
#include <cassert>

#include "Transport.hpp"
#include "TransportAlpha.hpp"
#include "TransportBeta.hpp"
#include "TransportCharlie.hpp"
#include "TransportDelta.hpp"
#include "TransportEcho.hpp"
#include "SimStats.hpp"

void joby::TransportFactory::Test()
{
    SimStats stats(false);
    TransportFactory factory(stats);

    Transport* transport = factory.GetTransport(TRANSPORT_TYPE_ALPHA);
    assert(transport->GetName() == GetTypeName(TRANSPORT_TYPE_ALPHA));
    assert(factory.mAllocatedTransportList.size() == 1);
    factory.DestroyTransport(transport);
    assert(factory.mAllocatedTransportList.size() == 0);

    transport = factory.GetTransport(TRANSPORT_TYPE_BETA);
    assert(transport->GetName() == GetTypeName(TRANSPORT_TYPE_BETA));

    transport = factory.GetTransport(TRANSPORT_TYPE_CHARLIE);
    assert(transport->GetName() == GetTypeName(TRANSPORT_TYPE_CHARLIE));

    transport = factory.GetTransport(TRANSPORT_TYPE_DELTA);
    assert(transport->GetName() == GetTypeName(TRANSPORT_TYPE_DELTA));

    transport = factory.GetTransport(TRANSPORT_TYPE_ECHO);
    assert(transport->GetName() == GetTypeName(TRANSPORT_TYPE_ECHO));

    try
    {
        factory.GetTransport(MAX_TRANSPORT_TYPES);
        assert(false);
    }
    catch (std::runtime_error& /*e*/)
    {
        // We don't need to do anything with this assert. If this assert was thrown, we know we are good.
    }
}

joby::TransportFactory::TransportFactory(joby::SimStats& stats) : mStatsManager(stats)
{
    TransportAlpha::AddStats(stats.CreateStatsGatherer());
    TransportBeta::AddStats(stats.CreateStatsGatherer());
    TransportCharlie::AddStats(stats.CreateStatsGatherer());
    TransportDelta::AddStats(stats.CreateStatsGatherer());
    TransportEcho::AddStats(stats.CreateStatsGatherer());
}

joby::TransportFactory::~TransportFactory()
{
    for (auto& transport : mAllocatedTransportList)
    {
        DeleteTransport(transport);
    }
    mAllocatedTransportList.clear();
}

joby::Transport* joby::TransportFactory::GetTransport(joby::TransportType type)
{
    Transport* transport;
    switch (type)
    {
        case TRANSPORT_TYPE_ALPHA:
            {
                transport = new TransportAlpha();
            }
            break;
        case TRANSPORT_TYPE_BETA:
            {
                transport = new TransportBeta();
            }
            break;
        case TRANSPORT_TYPE_CHARLIE:
            {
                transport = new TransportCharlie();
            }
            break;
        case TRANSPORT_TYPE_DELTA:
            {
                transport = new TransportDelta();
            }
            break;
        case TRANSPORT_TYPE_ECHO:
            {
                transport = new TransportEcho();
            }
            break;
        default:
            {
                throw std::runtime_error("invalid value used to create transport: " + GetTypeName(type));
            }
            break;
    }
    mAllocatedTransportList.push_back(transport);
    return transport;
}

joby::Transport* joby::TransportFactory::GetRandomTransport()
{
    int type = rand() % joby::MAX_TRANSPORT_TYPES;
    return GetTransport(static_cast<TransportType>(type));
}

void joby::TransportFactory::DestroyTransport(Transport* transport)
{
    auto iter = mAllocatedTransportList.cbegin();
    while (iter != mAllocatedTransportList.cend() &&
        (*iter) != transport)
    {
        ++iter;
    }
    if (iter != mAllocatedTransportList.cend())
    {
        mAllocatedTransportList.erase(iter);
    }
    else
    {
        throw std::runtime_error("trying to delete a transport that we cannot find");
    }
    DeleteTransport(transport);
}

void joby::TransportFactory::DeleteTransport(Transport* transport)
{
    delete transport;
}
