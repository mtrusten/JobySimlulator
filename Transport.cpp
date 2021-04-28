
#include "Transport.hpp"

#include <stdexcept>

int joby::Transport::sNumCreated = 0;

std::string joby::GetTransportStateName(TransportState state)
{
    std::string name;
    switch (state)
    {
        case TRANSPORT_STATE_IN_FLIGHT:
            {
                name = "InFlight";
            }
            break;
        case TRANSPORT_STATE_ENTERING_WAIT_LIST:
            {
                name = "EnteringWaitList";
            }
            break;
        case TRANSPORT_STATE_WAITING_TO_CHARGE:
            {
                name = "WaitingToCharge";
            }
            break;
        case TRANSPORT_STATE_CHARGING:
            {
                name = "Charging";
            }
            break;
        case TRANSPORT_STATE_STARTING_FLIGHT:
            {
                name = "StartingFlight";
            }
            break;
        default:
            {
                name = "Invalid State " + state;
            }
            break;
    }
    return name;
}

std::string joby::GetTypeName(joby::TransportType type)
{
    std::string name;
    switch (type)
    {
    case joby::TRANSPORT_TYPE_ALPHA:
    {
        name = "Alpha_eVTOL";
    }
    break;
    case TRANSPORT_TYPE_BETA:
    {
        name = "Beta_eVTOL";
    }
    break;
    case TRANSPORT_TYPE_CHARLIE:
    {
        name = "Charlie_eVTOL";
    }
    break;
    case TRANSPORT_TYPE_DELTA:
    {
        name = "Delta_eVTOL";
    }
    break;
    case TRANSPORT_TYPE_ECHO:
    {
        name = "Echo_eVTOL";
    }
    break;
    default:
    {
        name = "invalid type " + type;
    }
    break;
    }
    return name;
}


joby::TransportState joby::Transport::Update(double delta_time_seconds)
{
    float convert_hours_to_seconds = 1.0f * 60.0f * 60.0f;
    AddTime(delta_time_seconds);
    switch (mState)
    {
        case TRANSPORT_STATE_IN_FLIGHT:
            {
                float cruise_speed_miles_per_second = mCruiseSpeedMPH / convert_hours_to_seconds;
                float distance_this_iteration_miles = cruise_speed_miles_per_second * static_cast<float>(delta_time_seconds);

                float energy_usage_this_iteration_kwh = mEnergyUseAtCruiseKWHPerMile * distance_this_iteration_miles;

                mCurrentBatteryCapacityKWH -= energy_usage_this_iteration_kwh;
                if (mCurrentBatteryCapacityKWH <= 0.0f)
                {
                    SetAsEnteringWaitList();
                }
            }
            break;
        case TRANSPORT_STATE_ENTERING_WAIT_LIST:
            {
                throw std::runtime_error("should never hit update for this state: ENTERING_WAIT_LIST");
            }
            break;
        case TRANSPORT_STATE_WAITING_TO_CHARGE:
            {
                // Do nothing. This is not dependent on this object. It will be told when it can start charging.
            }
            break;
        case TRANSPORT_STATE_CHARGING:
            {
                float time_to_charge_seconds = mTimeToChargeHours * convert_hours_to_seconds;
                mCurrentTimeLeftChargingSeconds -= time_to_charge_seconds;

                if (mCurrentTimeLeftChargingSeconds <= 0.0f)
                {
                    SetAsStartingFlight();;
                }
            }
            break;
        case TRANSPORT_STATE_STARTING_FLIGHT:
            {
                throw std::runtime_error("should never hit update for this state: STARTING_FLIGHT");
            }
            break;
        default:
            {
                throw std::runtime_error("invalid value used for transport state: " + GetTransportStateName(mState));
            }
            break;
    }
    return mState;
}

void joby::Transport::UpdateTime(double delta_time_seconds,
                                 TransportType type,
                                 double& total_simulation_time,
                                 double& total_time_in_flight,
                                 double& total_time_waiting_to_charge,
                                 double& total_time_charging) const
{
    total_simulation_time += delta_time_seconds;
    switch (mState)
    {
    case TRANSPORT_STATE_IN_FLIGHT:
    {
        total_time_in_flight += delta_time_seconds;
    }
    break;
    case TRANSPORT_STATE_ENTERING_WAIT_LIST:
    {
    }
    break;
    case TRANSPORT_STATE_WAITING_TO_CHARGE:
    {
        total_time_waiting_to_charge += delta_time_seconds;
    }
    break;
    case TRANSPORT_STATE_CHARGING:
    {
        total_time_charging += delta_time_seconds;
    }
    break;
    case TRANSPORT_STATE_STARTING_FLIGHT:
    {
    }
    break;
    default:
    {
        throw std::runtime_error("invalid value used for adding time for " + GetTypeName(type) + ": " + GetTransportStateName(mState));
    }
    break;
    }
}

void joby::Transport::SetAsInFlight()
{
    mState = TRANSPORT_STATE_IN_FLIGHT;
    mCurrentBatteryCapacityKWH = mBatteryCapacityKWH;
}

void joby::Transport::SetAsEnteringWaitList()
{
    mState = TRANSPORT_STATE_ENTERING_WAIT_LIST;
}

void joby::Transport::SetAsWaitingToCharge()
{
    mState = TRANSPORT_STATE_WAITING_TO_CHARGE;
}

void joby::Transport::SetAsCharging()
{
    mState = TRANSPORT_STATE_CHARGING;
    float convert_hours_to_seconds = 1.0f * 60.0f * 60.0f;
    mCurrentTimeLeftChargingSeconds = mTimeToChargeHours * convert_hours_to_seconds;
}

void joby::Transport::SetAsStartingFlight()
{
    mState = TRANSPORT_STATE_STARTING_FLIGHT;
}

bool joby::Transport::operator==(const Transport& rhs) const
{
    return mId == rhs.mId;
}

bool joby::Transport::operator!=(const Transport& rhs) const
{
    return mId != rhs.mId;
}

std::string joby::Transport::GetName() const
{
    return joby::GetTypeName(mType);
}

joby::Transport::Transport(TransportType type,
                           float cruise_speed_mph,
                           float battery_capacity_kwh,
                           float time_to_charge_hours,
                           float energy_use_cruising_kwh_per_mile,
                           int max_passenger_count,
                           float fault_probability_per_hour)
{
    mId = sNumCreated;
    ++sNumCreated;

    mType = type;

    mCruiseSpeedMPH = cruise_speed_mph;
    mBatteryCapacityKWH = battery_capacity_kwh;
    mTimeToChargeHours = time_to_charge_hours;
    mEnergyUseAtCruiseKWHPerMile = energy_use_cruising_kwh_per_mile;
    mPassengerCount = max_passenger_count;
    mFaultProbabilityPerHour = fault_probability_per_hour;

    SetAsInFlight();
    float convert_hours_to_seconds = 1.0f * 60.0f * 60.0f;
    mCurrentBatteryCapacityKWH = mBatteryCapacityKWH;
    mCurrentTimeLeftChargingSeconds = mTimeToChargeHours * convert_hours_to_seconds;
}
