#include <iostream>
#include "event_emitter.h"

int main()
{
    {
        EventEmitter<std::string> emitter;

        int counter = 0;
        emitter.on("increment", [&]
                   { ++counter; });
        emitter.on("reset", [&]
                   { counter = 0; });

        emitter.emit("increment"); // counter == 1
        std::cout << "counter: " << counter << "\n";
        emitter.emit("increment"); // counter == 2
        std::cout << "counter: " << counter << "\n";
        emitter.emit("reset"); // counter == 0
        std::cout << "counter: " << counter << "\n";
    }

    {
        EventEmitter<> file_emitter;
        file_emitter.on(Events::Write, [&] { // write to file
        });
        file_emitter.on(Events::Read, [&] { // read file
        });
        file_emitter.emit(Events::Write); // test.txt -> "foo"

        file_emitter.emit(Events::Read); // data == "foo"
    }

    {
        EventEmitter<std::string, int, double> adc_emitted;

        // Set up our event handlers ahead of time
        adc_emitted.on("overrange", [&](const int &channel, const double &volts)
                   { std::cout << "Voltage overrange! channel " << channel << " " << volts << " V" << "\n"; });
        adc_emitted.on("log", [&](const int &channel, const double &volts)
                   { std::cout << "channel " << channel << " " << volts << " V" << "\n"; });

        // Start emitting our events as new data comes in
        static constexpr double adc[8] = {1.0,
                                          10.9,
                                          2.5,
                                          3.0,
                                          15.0,
                                          2.0,
                                          5.0,
                                          1.0};
        for (int i = 0; i < 8; ++i)
        {
            const double voltage = adc[i];
            if (voltage > 10.0)
            {
                adc_emitted.emit("overrange", i, voltage);
            }
            else
            {
                adc_emitted.emit("log", i, voltage);
            }
        }
    }

    return 0;
}