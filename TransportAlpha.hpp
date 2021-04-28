
#ifndef TRANSPORT_ALPHA_HPP
#define TRANSPORT_ALPHA_HPP

#include "Transport.hpp"

namespace joby
{
	struct StatsGatherer;

	class TransportAlpha final : public Transport
	{
	public:
		static void AddStats(StatsGatherer* stats);

		void AddTime(double delta_time_seconds) override;
	protected:
		friend TransportFactory;
	private:
		TransportAlpha();

		static StatsGatherer* sStats;
		static double sTotalSimulationTime;
		static double sTotalTimeInFlight;
		static double sTotalTimeWaitingToCharge;
		static double sTotalTimeCharging;
	}; // TransportAlpha class
} // joby namespace

#endif // TRANSPORT_ALPHA_HPP
