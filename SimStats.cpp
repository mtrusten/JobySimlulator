
#include "SimStats.hpp"

#include <iostream>

#include "StatsGatherer.hpp"

joby::SimStats::SimStats(bool print_each_update)
{
	mPrintEachUpdate = print_each_update;
}

joby::SimStats::~SimStats()
{
	for (auto& stat_obj : mStatsGathererList)
	{
		delete stat_obj;
	}
	mStatsGathererList.clear();
}

joby::StatsGatherer* joby::SimStats::CreateStatsGatherer()
{
	StatsGatherer* stats = new StatsGatherer(mPrintEachUpdate);
	mStatsGathererList.push_back(stats);
	return stats;
}

void joby::SimStats::PrintStats() const 
{
	std::cout << "\n\nRESULTS:";
	for (auto& stat_obj : mStatsGathererList)
	{
		size_t num_objs = stat_obj->mTransportIDSet.size();
		if (num_objs)
		{
			std::cout << "\n\n" << (*stat_obj);
		}
	}
	std::cout << std::endl;
}
