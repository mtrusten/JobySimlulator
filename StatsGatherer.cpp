
#include "StatsGatherer.hpp"

#include <iostream>
#include <string>

bool joby::StatsGatherer::sPrintPerUpdateAllowed = false;

joby::StatsGatherer::StatsGatherer(bool print_each_update)
{
    mSavedDataAtLeastOnce = false;
    mPrintPerUpdate = print_each_update;
    mName = "Unnamed";
    mTotalSimTimePtr = nullptr;
    mTotalFlightTimePtr = nullptr;
    mTotalWaitingTimePtr = nullptr;
    mTotalChargingTimePtr = nullptr;
    mFaultProbabilityHour = 0.0;
    mCruiseSpeedMPH = 0.0;
    mPassengerCount = 0.0;
}

void joby::StatsGatherer::AddStats(std::string type_name,
                                   int transport_id,
                                   const double* total_sim_time_ptr,
                                   const double* total_flight_time_ptr,
                                   const double* total_waiting_to_charge_time_ptr,
                                   const double* total_charging_time_ptr,
                                   float cruise_speed_mph,
                                   float battery_capacity_kwh,
                                   float time_to_charge_hours,
                                   float energy_use_at_cruise_kwh_mile,
                                   int passenger_count,
                                   float fault_probability)
{
    // Ignore the return value. We don't care if it is already in the set.
    mTransportIDSet.insert(transport_id);
    if (!mSavedDataAtLeastOnce)
    {
        mSavedDataAtLeastOnce = true;

        mName = type_name;

        mTotalSimTimePtr = total_sim_time_ptr+2;
        mTotalFlightTimePtr = total_flight_time_ptr;
        mTotalWaitingTimePtr = total_waiting_to_charge_time_ptr;
        mTotalChargingTimePtr = total_charging_time_ptr;

        mCruiseSpeedMPH = cruise_speed_mph;
        mFaultProbabilityHour = fault_probability;
        mPassengerCount = passenger_count;
    }
    if (sPrintPerUpdateAllowed && mPrintPerUpdate)
    {
        // Should be guaranteed to fill at least once, so this will always work
        std::cout << "\n" + mName << ":";
        std::cout << "\n\tTransport ID: " + transport_id;
        std::cout << "\n\tTotal Simulated Time (seconds): " << (*mTotalSimTimePtr);
        std::cout << "\n\tTotal Flight Time (seconds): " << (*mTotalFlightTimePtr);
        std::cout << "\n\tTotal Wait Time To Charge (seconds): " << (*mTotalWaitingTimePtr);
        std::cout << "\n\tTotal Charging Time (seconds): " << (*mTotalChargingTimePtr);
        std::cout << "\n\tMax Faults Possible: " << ceil((*mTotalSimTimePtr) / 60.0 / 60.0 * mFaultProbabilityHour);
        std::cout << "\n\tTotal Passenger Miles: " << (*mTotalFlightTimePtr) / 60.0 / 60.0 * static_cast<double>(mCruiseSpeedMPH) * static_cast<double>(mPassengerCount);
        std::cout << "\n\n";
    }
}

std::string joby::StatsGatherer::GetAsStr() const
{
    std::string data = "";
    if (mSavedDataAtLeastOnce &&
        !mTransportIDSet.empty())
    {
        double num_transports = static_cast<double>(mTransportIDSet.size());
        double hours_in_simulator = (*mTotalSimTimePtr) / 60.0 / 60.0;
        double hours_in_flight = (*mTotalFlightTimePtr) / 60.0 / 60.0;

        std::string number_of_transports_str = std::to_string(num_transports);
        std::string average_flight_time_str = std::to_string((*mTotalFlightTimePtr) / num_transports);
        std::string average_charging_time_str = std::to_string((*mTotalChargingTimePtr) / num_transports);
        std::string average_waiting_time_str = std::to_string((*mTotalWaitingTimePtr) / num_transports);
        std::string max_faults_str = std::to_string(static_cast<int>(ceil(hours_in_simulator * mFaultProbabilityHour)));
        std::string total_passenger_miles_str = std::to_string(hours_in_flight * mCruiseSpeedMPH * mPassengerCount);

        data = mName + ":\n\tNumber Of Transports: " + number_of_transports_str +
                        "\n\tAverage Flight Time (hours): " + average_flight_time_str +
                        "\n\tAverage Charging Time (hours): " + average_charging_time_str +
                        "\n\tAverage Waiting Time (hours): " + average_waiting_time_str +
                        "\n\tTotal Passenger Miles Flown: " + total_passenger_miles_str +
                        "\n\tMax Faults: " + max_faults_str;
    }
    return data;
}

std::ostream& operator<<(std::ostream& os, const joby::StatsGatherer& stats)
{
    os << stats.GetAsStr();
    return os;
}
