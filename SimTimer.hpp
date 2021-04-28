#ifndef SIM_TIMER_HPP
#define SIM_TIMER_HPP

#include <chrono> // high_resolution_clock, potential issue with non-intel machines?

namespace joby
{
	class SimTimer
	{
	public:
		SimTimer(double time_to_run,
			     double min_time_per_frame,
			     double max_time_per_frame);

		void StartTimer();
		double MarkFrameEnd();
		bool IsRunning() const;
	private:
		bool mIsStarted;
		double mCurrentRunningTime;
		double mLengthToRunSeconds;
		double mMinFrameLength;
		double mMaxFrameLength;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> mStartMoment;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> mPrevMoment;
	};
} // joby namespace

#endif // SIM_TIMER_HPP
