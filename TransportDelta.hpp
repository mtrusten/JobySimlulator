
#ifndef TRANSPORT_DELTA_HPP
#define TRANSPORT_DELTA_HPP

#include "Transport.hpp"

namespace joby
{
	struct StatsGatherer;

	class TransportDelta final : public Transport
	{
	public:
		static void AddStats(StatsGatherer* stats);

		void AddTime(double delta_time_seconds) override;
	protected:
		friend TransportFactory;
	private:
		TransportDelta();

		static StatsGatherer* sStats;
		static double sTotalSimulationTime;
		static double sTotalTimeInFlight;
		static double sTotalTimeWaitingToCharge;
		static double sTotalTimeCharging;
	}; // TransportDelta class
} // joby namespace

#endif // TRANSPORT_DELTA_HPP
