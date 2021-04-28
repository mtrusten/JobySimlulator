
#include "SimTimer.hpp"

joby::SimTimer::SimTimer(double time_to_run_seconds,
                         double min_frame_time,
                         double max_frame_time)
{
    mCurrentRunningTime = 0.0;
    mLengthToRunSeconds = time_to_run_seconds;
    mMinFrameLength = min_frame_time;
    mMaxFrameLength = max_frame_time;
    mIsStarted = false;
}

void joby::SimTimer::StartTimer()
{
    mStartMoment = std::chrono::high_resolution_clock::now();
    mPrevMoment = mStartMoment;
    mIsStarted = true;
}

double joby::SimTimer::MarkFrameEnd()
{
    double frame_seconds = 0.0;
    if (mIsStarted)
    {
        auto end = std::chrono::high_resolution_clock::now();
        frame_seconds = std::chrono::duration<double>(end - mPrevMoment).count();
        mPrevMoment = end;
    }
    if (frame_seconds < mMinFrameLength)
    {
        frame_seconds = mMinFrameLength;
    }
    else if (frame_seconds > mMaxFrameLength)
    {
        frame_seconds = mMaxFrameLength;
    }
    mCurrentRunningTime += frame_seconds;
    return frame_seconds;
}

bool joby::SimTimer::IsRunning() const
{
    return (mIsStarted &&
            (mLengthToRunSeconds > mCurrentRunningTime)) ? true : false;
}
