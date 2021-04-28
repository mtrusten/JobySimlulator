
#include "TransportBeta.hpp"

#include <stdexcept>

#include "StatsGatherer.hpp"

joby::StatsGatherer* joby::TransportBeta::sStats = nullptr;
double joby::TransportBeta::sTotalSimulationTime = 0.0;
double joby::TransportBeta::sTotalTimeInFlight = 0.0;
double joby::TransportBeta::sTotalTimeWaitingToCharge = 0.0;
double joby::TransportBeta::sTotalTimeCharging = 0.0;

void joby::TransportBeta::AddStats(joby::StatsGatherer* stats)
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

void joby::TransportBeta::AddTime(double delta_time_seconds)
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

joby::TransportBeta::TransportBeta() :
	Transport(TRANSPORT_TYPE_BETA, 100.0f, 100.0f, 0.2f, 1.5f, 5, 0.10f)
{

}
