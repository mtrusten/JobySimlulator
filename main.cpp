
#include "TransportFactory.hpp"
#include "Transport.hpp"
#include "Charger.hpp"
#include "TransportState.h"
#include "SimStats.hpp"
#include "SimTimer.hpp"

int main()
{
    bool doing_testing = false;
    if (doing_testing)
    {
        joby::TransportFactory::Test();
    }
    else
    {
        const double MAX_FRAME_TIME_SECONDS = 1.0;
        const double MIN_FRAME_TIME_SECONDS = 0.0001;
        joby::SimTimer timer(3.0 * 60.0,
            MIN_FRAME_TIME_SECONDS,
            MAX_FRAME_TIME_SECONDS);
        joby::SimStats stats(false);
        joby::TransportFactory factory(stats);
        std::array<joby::Transport*, 20> transport_array{};

        for (auto& transport : transport_array)
        {
            transport = factory.GetRandomTransport();
        }
        joby::Charger<3> chargers;

        double scaled_frame_time_seconds = 0.0001;
        double frame_time_seconds = 0.0001;
        const double TIME_SCALE = 60.0;

        bool is_running = true;
        timer.StartTimer();
        while (timer.IsRunning())
        {
            for (auto& transport : transport_array)
            {
                joby::TransportState state = transport->Update(scaled_frame_time_seconds);
                if (state == joby::TRANSPORT_STATE_ENTERING_WAIT_LIST)
                {
                    chargers.AddToWaitQueue(transport);

                }
                else if (state == joby::TRANSPORT_STATE_STARTING_FLIGHT)
                {
                    chargers.RemoveTransportFromCharging(transport);
                }
            }

            chargers.Update();

            frame_time_seconds = timer.MarkFrameEnd();

            scaled_frame_time_seconds = frame_time_seconds * TIME_SCALE;
        }

        stats.PrintStats();
    }
    return 0;
}
