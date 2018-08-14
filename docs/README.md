# TEAM IV - (robot name)
## 2018 UBC ENGINEERING PHYSICS ROBOT SUMMER - 3RD PLACE

Course Description

## Our robot

photo

description

## Our team

photo (maybe the one in front of the "this just might work" sign?)

description with our names and roles

## Our Design + Strategy

### First design

### Second design



### Third design

- say something about the open chassis and how it helped us in the end (reducing noise, etc)

## Electrical Components

### STM32 "Blue Pill" Board

The STM32F106... board has a 72MHz processor, a fast analog digital converter, and three timers in a $2 tiny form factor. The small size and high speed were extremely useful, but the board had never been used in ENPH253 before; we learned a lot when developing a lot of software from scratch, learning along with the instructors.

### H-bridges

H-bridges are circuits that can amplify the small signals from our microcontroller and allow our motors to run both in forward and reverse at high power. The MOSFET transistors in this circuit act as switches, providing power in either forward or reverse through the motor. Teams historically have a difficult time building and testing this circuit, and our team was no exception; we learned a lot about noise, microcontroller timers, and cable management while debugging this circuit.

### Line Following with Infrared Sensors

A black line running across the competition surface acts as a guide for our robots to follow. In order to sense this line, we pulse infrared light from LEDs at the ground, and measure the amount of reflected light with infrared sensors. The black surface reflects less light than the white surface, providing a sense of where we are.

### IR Beacon

Inspired by our line-following sensors, we mounted a high-powered equivalent at the front of our robot. In order to account for different ambient infrared amounts, we pulse the LEDs in order to get readings with only ambient light, and readings that include light reflected off the surroundings. Using this method, we were able to sense detect from over half a meter away!

### Encoders

To provide more control over our robot, we added encoders on our wheels. These sensors allow us to know how many rotations our wheels have had. This allows our robot to make precise movements which will always work as expected. A simpler time-based control is much more dependent on battery voltage or small changes in mass distribution.

### Form Factor

In our first design, we did not reserve any space for our circuitry, leading to makeshift mounting solutions and extremely messy wiring. Learning from our mistakes, we designed an enclosure which isolated our circuits to one location, and relied on high-quality JST connectors for any sensor input. This solution allowed for easy replacement of electronic components, easy access to circuitry, and one of the most compact electronics systems in this year's competition.

### Loose Wires

In a final product design, the loose wires found on our robot would be unacceptable; free wires can become detached at connection points when they move. However, hidden, completely secured wires are difficult to replace or move. We found a balance on our final design; we used good connectors, and we made sure to zip-tie our wires in place once we finalized our circuitry. The free wires saved us hours when we fine-tuned and replaced our sensors.

## Software

### Frequency Sensing: 1kHz vs 10kHz

(graph thing)

One of the obstacles of the course was made easier by a shortcut provided by the instructors; if our robot could sense the difference between an infrared signal pulsing at 1kHz, and a signal pulsing at 10kHz, we would be able to skip the obstacle. Most teams used a solution discussed in class; using resistors, capacitors and op-amps, an analog filter can be built that will determine the frequency. We built this circuit, but ultimately we decided to use a much simpler circuit and determine the frequency using software. This solution allowed us to fine-tune and debug our frequency sensor much faster.

In order to filter frequencies, we convoluted our signal against reference signals of 1kHz and 10kHz sine waves.... [todo]

### Proportional Integral Derivative Control

During almost all of our movements, we used a control technique called Proportional Integral Derivative - or PID. This control technique allows for accurate control over movement by adjusting to any errors that are sensed. During line following, motor power is adjusted based on our distance off of the line. Unique to our team was the use of PID during encoder-controlled movements. This allowed for accuracy and consistency that very few other teams were able to achieve.

idk write down some buzzwords. or maybe some of the software components that gave us an advantage

our "FFT" class maybe

PID on movements

Pulsing IR

weird shakes and shit like that

unit testing at the end

Dylan says something about state diagrams but tbh I don't feel like that's particularly relevant...
