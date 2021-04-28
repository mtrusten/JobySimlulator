
#ifndef TRANSPORT_BETA_HPP
#define TRANSPORT_BETA_HPP

#include "Transport.hpp"

namespace joby
{
	struct StatsGatherer;

	class TransportBeta final : public Transport
	{
	public:
		static void AddStats(StatsGatherer* stats);

		void AddTime(double delta_time_seconds) override;
	protected:
		friend TransportFactory;
	private:
		TransportBeta();

		static StatsGatherer* sStats;
		static double sTotalSimulationTime;
		static double sTotalTimeInFlight;
		static double sTotalTimeWaitingToCharge;
		static double sTotalTimeCharging;
	}; // TransportBeta class
} // joby namespace

#endif // TRANSPORT_BETA_HPP
