
#ifndef CHARGER_HPP
#define CHARGER_HPP

#include <queue>
#include <array>


namespace joby
{
	class Transport;

	template <int MaxArraySize>
	class Charger
	{
	public:

		void Update();
		void AddToWaitQueue(Transport* transport);
		void RemoveTransportFromCharging(Transport* transport);
	private:
		std::queue<Transport*> mTransportsWaitQueue;
		std::array<Transport*, MaxArraySize> mChargingTransportsArray{};
	}; // Charger class
} // joby namespace

#include "Charger_templatized.cpp"

#endif // CHARGER_HPP