
#include "TransportCharlie.hpp"

#include <stdexcept>

#include "StatsGatherer.hpp"

joby::StatsGatherer* joby::TransportCharlie::sStats = nullptr;
double joby::TransportCharlie::sTotalSimulationTime = 0.0;
double joby::TransportCharlie::sTotalTimeInFlight = 0.0;
double joby::TransportCharlie::sTotalTimeWaitingToCharge = 0.0;
double joby::TransportCharlie::sTotalTimeCharging = 0.0;

void joby::TransportCharlie::AddStats(joby::StatsGatherer* stats)
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

void joby::TransportCharlie::AddTime(double delta_time_seconds)
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

joby::TransportCharlie::TransportCharlie() :
    Transport(TRANSPORT_TYPE_CHARLIE, 160.0f, 220.0f, 0.8f, 2.2f, 3, 0.05f)
{

}
