
#ifndef TRANSPORT_ECHO_HPP
#define TRANSPORT_ECHO_HPP

#include "Transport.hpp"

namespace joby
{
	struct StatsGatherer;

	class TransportEcho final : public Transport
	{
	public:
		static void AddStats(StatsGatherer* stats);

		void AddTime(double delta_time_seconds) override;
	protected:
		friend TransportFactory;
	private:
		TransportEcho();

		static StatsGatherer* sStats;
		static double sTotalSimulationTime;
		static double sTotalTimeInFlight;
		static double sTotalTimeWaitingToCharge;
		static double sTotalTimeCharging;
	}; // TransportEcho class
} // joby namespace

#endif // TRANSPORT_ECHO_HPP
