
#ifndef STATS_GATHERER_HPP
#define STATS_GATHERER_HPP

#include <string>
#include <set>

namespace joby
{
	struct StatsGatherer
	{
        StatsGatherer(bool print_each_update);

		void AddStats(std::string type_name,
                      int transport_id,
                      const double* total_sim_time,
                      const double* total_flight_time,
                      const double* total_waiting_to_charge,
                      const double* total_charging,
                      float cruise_speed_mph,
                      float battery_capacity_kwh,
                      float time_to_charge_hours,
                      float energy_use_at_cruise_kwh_mile,
                      int passenger_count,
                      float fault_probability);
        std::string GetAsStr() const;

        std::set<int> mTransportIDSet;

        std::string mName;
        const double* mTotalSimTimePtr;
        const double* mTotalFlightTimePtr;
        const double* mTotalWaitingTimePtr;
        const double* mTotalChargingTimePtr;
        double mFaultProbabilityHour;
        double mCruiseSpeedMPH;
        double mPassengerCount;

        bool mSavedDataAtLeastOnce;

        static bool sPrintPerUpdateAllowed;
        bool mPrintPerUpdate;
	}; // StatsGatherer struct

} // joby namespace

std::ostream& operator<<(std::ostream& os, const joby::StatsGatherer& stats);

#endif // STATS_GATHERER_HPP
