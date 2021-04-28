
#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include "TransportType.h"
#include "TransportState.h"
#include "TransportFactory.hpp"

#include <iostream>

namespace joby
{
    std::string GetTransportStateName(TransportState state);
    std::string GetTypeName(joby::TransportType type);

    class Transport
    {
    public:
        virtual ~Transport() = default;
        virtual TransportState Update(double delta_time_seconds);

        virtual void AddTime(double delta_time_seconds) = 0;
        void UpdateTime(double delta_time_seconds,
                        TransportType type,
                        double& total_simulation_time,
                        double& total_time_in_flight,
                        double& total_time_waiting_to_charge,
                        double& total_time_charging) const;

        void SetAsInFlight();
        void SetAsEnteringWaitList();
        void SetAsWaitingToCharge();
        void SetAsCharging();
        void SetAsStartingFlight();

        bool operator==(const Transport& rhs) const;
        bool operator!=(const Transport& rhs) const;
        std::string GetName() const;
    protected:
        friend TransportFactory;
    
        TransportType mType;
    
        TransportState mState;
        float mCurrentBatteryCapacityKWH;
        float mCurrentTimeLeftChargingSeconds;
    
        int mId;
    
        float mCruiseSpeedMPH;
        float mBatteryCapacityKWH;
        float mTimeToChargeHours;
        float mEnergyUseAtCruiseKWHPerMile;
        int mPassengerCount;
        float mFaultProbabilityPerHour;
    
        Transport(TransportType type,
                  float cruise_speed_mph,
                  float battery_capacity_khw,
                  float time_to_charge_hours,
                  float energy_use_cruising_khw_per_mile,
                  int max_passenger_count,
                  float fault_probability_per_hour);
    private:
        static int sNumCreated;
    
    }; // Transport Class

} // joby namespace

#endif // TRANSPORT_HPP
