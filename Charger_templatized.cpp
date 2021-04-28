
//#include "Charger.hpp"

#include "Transport.hpp"
template <int MaxArraySize>
void joby::Charger<MaxArraySize>::Update()
{
	for (int i = 0; i < MaxArraySize; ++i)
	{
		if (!mChargingTransportsArray[i] &&
			!mTransportsWaitQueue.empty())
		{
			Transport* waiting_transport = mTransportsWaitQueue.front();
			mTransportsWaitQueue.pop();
			mChargingTransportsArray[i] = waiting_transport;
			mChargingTransportsArray[i]->SetAsCharging();
		}
	}
}

template <int MaxArraySize>
void joby::Charger<MaxArraySize>::AddToWaitQueue(joby::Transport * const transport)
{
	mTransportsWaitQueue.push(transport);

	transport->SetAsWaitingToCharge();
}

template <int MaxArraySize>
void joby::Charger<MaxArraySize>::RemoveTransportFromCharging(joby::Transport* const transport)
{
	for (int i = 0; i < MaxArraySize; ++i)
	{
		if (transport == mChargingTransportsArray[i])
		{
			mChargingTransportsArray[i] = nullptr;
		}
	}
	transport->SetAsInFlight();
}
