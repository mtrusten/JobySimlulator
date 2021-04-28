
#include "TransportDelta.hpp"

#include <stdexcept>

#include "StatsGatherer.hpp"

joby::StatsGatherer* joby::TransportDelta::sStats = nullptr;
double joby::TransportDelta::sTotalSimulationTime = 0.0;
double joby::TransportDelta::sTotalTimeInFlight = 0.0;
double joby::TransportDelta::sTotalTimeWaitingToCharge = 0.0;
double joby::TransportDelta::sTotalTimeCharging = 0.0;

void joby::TransportDelta::AddStats(joby::StatsGatherer* stats)
{
    if (sStats)
    {
        throw std::runtime_error("Trying to create a stats object for TransportAlpha when it already has one");
    }
    else
    {
        sStats = stats;
    }
}

void joby::TransportDelta::AddTime(double delta_time_seconds)
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

joby::TransportDelta::TransportDelta() :
    Transport(TRANSPORT_TYPE_DELTA, 90.0f, 120.0f, 0.62f, 0.8f, 2, 0.22f)
{

}
