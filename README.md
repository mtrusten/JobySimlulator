# JobySimlulator
Simple Simulator of eVTOL transports

### Module Diagram For Simulator:

https://drive.google.com/file/d/1tbF7fCQioJdcJ3-nn0SuI8UUmVMann0Y/view?usp=sharing

## Introduction:

The above link shows a diagram of the modules implemented for this project. In the latest version, there are 4 independent modules. The most important are the transports (eVTOLs). The base type manages all the work, but the derived types give data-definition to each of the different types, of which there are currently 5. The Charger module is used to store and handle the waiting of the "charging" transports. They will also trigger the Transports into their charging state. The timer module is meant to simplify changing the run-length of the simulator. Finally, the Stats Module keeps the actual reporting on progress outside of the transports (to the best of my ability).

### Transport Classes:
Transport - the base class for transports. The state mechanism is managed here.
TransportAlpha/Beta/Charlie/Delta/Echo - the derived classes. These are for data storage, nothing more. Their role is to know data regarding themselves, and to have an aggregate for transport-type-level statistics.

### TransportFactory:
this is the creator and tracker of all factories. In general, this class could be removed (functionally) with proper smart pointer management AND if no validation of memory or stats were needed. In the current design, the factory ensures each transport-type gets one stats gatherer object, and ensures that memory tracking of the simulator is working correctly.

### Charger Module
The Charger module is used to "recharge" the transports. In reality, the transports charge themselves over time. This module is mostly a data structure to remember who is waiting (queue) to charge, and to limit the number of transports charging at once (tiny std::array). Knowing this size would not change at runtime, I chose to make this based on std::array with a templatized class. When a transport gets added to the array, it is triggered as charging. When the transport is done charging, a message (enum-state) is sent to the charger to release it from the array, and the next frame the charger will add another transport (assuming one is waiting).

### Timer Module
uses the standard chrono module. Each frame length is computed and when the run-length of the simulator has been surpassed the simulation ends. In studying to use this module, investigation showed a potential this module does not work similarly on non-Intel chipsets.

### Stats Module
this is a "factory" of stats-gatherers that get provided to each transport-type. Static data of each transport type gets passed to the stats-gatherer to do as it sees fit. This makes it (effectively) a communication object. It knows the potential data it can receive from a transport and stores it in a way the parent Stats Module can use. This keeps the stat module from knowing about transports but lets all the type-data statistics to be retrieved and stored. If there was a graphical interface, this is what would be provided to update visuals (numbers or bar charts). This is also the module which would include different output formats, such as string, binary, csv, etc, and describe how to write the data out.

### Testing
A simple set of tests have been provided in this project. The class itself knows how to test itself, through static functionality. This way proves to be very simple to ensure nothing breaks before code execution (assuming it run). In this particular case, some runtime checking limits the ability to run both the simulator and tests, but this can be easily flipped with a single bool in main.

### Future Efforts:
* One of the pieces missing is threading. I have little-to-no experience threading a project from scratch, but the expectation I would have is the charger and transports could be run out of a pool of available threads. This would allow for more transports, minimize the per-frame-limiit imposed by the state machine, etc. Another option would be to have multiple threads, one for simulator (as is) and one for graphical output.
* Graphics output is not provided. At the moment, the only output is through console logging. Ideally, it would be best to create a graphical output that, as time progresses, shows the important factors of the transports in visual bar charts.
* Error management would also need to be improved if the project were larger. Given the constraints for this project, the need for handling errors is less needed. For now, large errors are reported through either asserts or exceptions, which are not currently caught. This enforces ending the simulator. In many ways, if an application throws these errors then it is a large enough issue where reboot is probably best.
