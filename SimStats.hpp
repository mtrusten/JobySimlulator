
#ifndef SIM_STATS_HPP
#define SIM_STATS_HPP

#include <list>

namespace joby
{
	struct StatsGatherer;

	class SimStats
	{
	public:
		SimStats(bool print_each_update);
		~SimStats();
		StatsGatherer* CreateStatsGatherer();
		void PrintStats() const;
	private:
		std::list<StatsGatherer*> mStatsGathererList;

		bool mPrintEachUpdate;
	};
}

#endif // SIM_STATS_HPP
