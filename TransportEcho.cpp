
#include "TransportEcho.hpp"

#include <stdexcept>

#include "StatsGatherer.hpp"

joby::StatsGatherer* joby::TransportEcho::sStats = nullptr;
double joby::TransportEcho::sTotalSimulationTime = 0.0;
double joby::TransportEcho::sTotalTimeInFlight = 0.0;
double joby::TransportEcho::sTotalTimeWaitingToCharge = 0.0;
double joby::TransportEcho::sTotalTimeCharging = 0.0;

void joby::TransportEcho::AddStats(joby::StatsGatherer* stats)
{
    if (sStats)
    {
        throw std::runtime_error("Trying to create a stats object for TransportEcho when it already has one");
    }
    else
    {
        sStats = stats;
    }
}

void joby::TransportEcho::AddTime(double delta_time_seconds)
{
    UpdateTime(delta_time_seconds,
               mType,
               sTotalSimulationTime,
               sTotalTimeInFlight,
               sTotalTimeWaitingToCharge,
               sTotalTimeCharging);
    sStats->AddStats(GetTypeName(mType),
                     mId,
                     &sTotalSimulationTime,
                     &sTotalTimeInFlight,
                     &sTotalTimeWaitingToCharge,
                     &sTotalTimeCharging,
                     mCruiseSpeedMPH,
                     mBatteryCapacityKWH,
                     mTimeToChargeHours,
                     mEnergyUseAtCruiseKWHPerMile,
                     mPassengerCount,
                     mFaultProbabilityPerHour);
}

joby::TransportEcho::TransportEcho() :
    Transport(TRANSPORT_TYPE_ECHO, 30.0f, 150.0f, 0.3f, 5.8f, 2, 0.61f)
{
}
