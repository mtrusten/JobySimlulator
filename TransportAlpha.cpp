
#include "TransportAlpha.hpp"

#include <stdexcept>

#include "StatsGatherer.hpp"

joby::StatsGatherer* joby::TransportAlpha::sStats = nullptr;
double joby::TransportAlpha::sTotalSimulationTime = 0.0;
double joby::TransportAlpha::sTotalTimeInFlight = 0.0;
double joby::TransportAlpha::sTotalTimeWaitingToCharge = 0.0;
double joby::TransportAlpha::sTotalTimeCharging = 0.0;

void joby::TransportAlpha::AddStats(joby::StatsGatherer* stats)
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

void joby::TransportAlpha::AddTime(double delta_time_seconds)
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

joby::TransportAlpha::TransportAlpha() :
	Transport(TRANSPORT_TYPE_ALPHA, 120.0f, 320.0f, 0.6f, 1.6f, 4, 0.25f)
{

}
