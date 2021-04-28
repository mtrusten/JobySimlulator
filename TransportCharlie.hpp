
#ifndef TRANSPORT_CHARLIE_HPP
#define TRANSPORT_CHARLIE_HPP

#include "Transport.hpp"

namespace joby
{
	struct StatsGatherer;

	class TransportCharlie final : public Transport
	{
	public:
		static void AddStats(StatsGatherer* stats);

		void AddTime(double delta_time_seconds) override;
	protected:
		friend TransportFactory;
	private:
		TransportCharlie();

		static StatsGatherer* sStats;
		static double sTotalSimulationTime;
		static double sTotalTimeInFlight;
		static double sTotalTimeWaitingToCharge;
		static double sTotalTimeCharging;
	}; // TransportCharlie class
} // joby namespace

#endif // TRANSPORT_CHARLIE_HPP
