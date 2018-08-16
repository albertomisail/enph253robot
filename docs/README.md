# TEAM IV - Lil Bot: A New Hope 
## 2018 UBC ENGINEERING PHYSICS ROBOT SUMMER - 3RD PLACE

# Table of Contents 
1. [Course Description](#course-description)
2. [Our Robot](#our-robot)
3. [Our Team](#our-team)
4. [Our Design + Strategy](#our-design-+-strategy)
  4.1 [First Design](#first-design)
    4.1.1 [Lift System](#lift-system)
    4.1.2 [Pulley System](#pulley-system) 

## Course Description
From [course website:](https://projectlab.engphys.ubc.ca/enph253_2018/)

ENPH 253 – Introduction to Instrument Design. Practical laboratory exposure to instrument bread-boarding including simple mechanical and electrical design, and communications with sensors, actuators. Micro-controller implementation and design.    Credits: [5]        Pre-reqs: One of ENPH 259, PHYS 259, PHYS 209.

Background on the course:

UBC Engineering Physics is an intense, five-year undergraduate engineering / physics / math combined major tailored for students who want to work at the new leading edge of science and engineering, whether in industry or academia. Part of this program is a series of project-based courses to educate students in the practice of engineering and applied physics. Introduction to Instrument Design is one of these courses, taken by our second-year (sophomore) students. Its goal is to train students in the practical aspects of intelligent instrument design and construction, including electrical and mechanical design, prototyping, microcontrollers, sensors, actuators, motion control, and control theory.

To offset the intensity and difficulty of the course, the engineering content to be tackled by the students has been framed in the context of an autonomous robot competition. Each year students spend six weeks in a series of labs and lectures to learn some basic elements of electromechanical design, and then form teams of four to embark on seven weeks of full-time robot design and construction. Time commitment during this phase is at the students’ discretion but often reaches 50 – 70 hrs/week. The course culminates in a publicly attended robot competition that also serves as the final exam. Past competitions have included one-on-one hockey, volleyball, and search and rescue challenges.

## Our robot

![Final Chassis After Competition](res/final_robot_after_comp.jpg)

description

## Our team

![Team Photo: Frank Jia, Charles Qian, David Berard, Alberto Misail](res/team_4_photo.jpg)

description with our names and roles

## Our Design + Strategy

### First Design 

![First Chassis with Lift](res/first_chassis.JPG)

The first iteration of our design was composed of a dual scissor lift and pulley with a basket in the middle. The lift and pulley mechanism would allow us to go up and down the two ziplines on the course, allowing us to complete the competition in a non-linear fashion. 

This was the strategy that would allow us to retain flexibility and target ewoks selectively, which would give us a competitive advantage in certain situations. We worked on this first iteration extensively but discovered that the engineering challenge was too difficult in the given time-frame. This realization forced us to pivot to a simpler design that was much more reliable but less flexible. Nevertheless, we were able to design and build all modular components of this first design.

#### Lift System

![Lift System Design](res/first_chassis_lift.JPG)

Our first design features a dual scissor lift, driven by a standard DC motor and geared down with a transmission. The transmission is coupled to a lead screw which would lift up and down the upper platform. Initial prototypes were constructed using laser-cut hardboard pieces and 3D printed mounts.

#### Pulley System
![Pulley System Design](res/first_chassis_pulley.JPG)

The pulley to allow our robot to go up and down the ziplines needed to be light (to keep the center of mass low to the ground), yet powerful enough to drive a 5kg+ load up an inclined zipline. Using these design restrictions, we opted for a relatively simple and lightweight structure, built using 0.8mm aluminum that was waterjet cut to fit specifications. We used a DC motor which was geared down for increased torque

### Pivot in Strategy + Final Design
As mentioned, our initial strategy was too time intensive to execute. In addition to fabricating all the designs, we found that we had very little time to iterate for reliability. In addition, the weight of a dual lift and pulley system put our robot at a speed disadvantage. To address these issues, we stripped our design of all parts that were non-critical to the competition flow. Our final chassis was extremely light, agile, and reliable, which gave us a significant advantage during the time-limited competition runs.

![Final Chassis Design](res/small_chassis_with_circuit_holder.png)

[Final Chassis CAD - OnShape](https://cad.onshape.com/documents/e5c3377a8716b8da60088099/w/010801819196a53872331fb3/e/1dbbbb5ea80693d58eb4c532 "Lil Bot CAD") 

Our final chassis was a dual-layered and had support for the following:
- A claw system for holding and picking up ewoks and chewbacca
- Two bridges (and a simple bridge dropping mechanism) for crossing the gaps
- A second level for circuit mounting and wire organization
- Support for motor, axle, and encoder mounts as well as required sensors

We stripped even the functionality of having a basket, opting to rescue each ewok individually. This gave us a significant decrease in size, which contributed to a large increase in agility and speed. We also opted for an open chassis design, which allowed us to troubleshoot much faster and helped us eliminate motor noise issues from a cramped inner compartment.

#### Basic Chassis Design

![Final Basic Chassis Design](res/small_chassis_base.JPG)

The basic chassis was large enough to hold the motors, wheels, axles, and one claw. The first layer of the chassis was constructed out of laser-cut hardboard, and was dual-layered to reduce any possible flex. The rigidity of the chassis allowed us to make quick adjustments in speed and direction. 

#### Claw System

![Final Claw System Design](res/small_chassis_claw.JPG)

Given the relative inaccuracy of IR object sensing (Attributed mostly by the changing ambient light conditions) and the intention to hold ewoks for extended amounts of time (instead of dropping them into a basket), our claw needed to be forgiving and relatively strong. We opted for a "serrated" claw design with a hook-like structure at the end. The serrated design would help hold ewoks in place during travel, and the hook-like structure would help scoop any ewoks in if they were slightly too far. This entire mechanism was driven by a small servo, geared to increase grip torque. 

The entire claw assembly was attached to a rotating base, so that we could hold the claw up when it is gripping an ewok or when it is not in use.

#### Bridge Laying Mechanism

![Second (L) and First (R) Bridge Design](res/small_chassis_bridges.JPG)

Simplicity and reliability allowed us to perform so well on competition day. Our bridge laying mechanism was a simple servo that would rotate to drop one bridge, but not the other. Iterating many times, we found the above bridge designs to fall into position the most reliably. The flanges within the bridges themselves acted as a guiding mechanism for the bridges to fall properly. 

## Electrical Components

### STM32 "Blue Pill" Board

The STM32F106... board has a 72MHz processor, a fast analog digital converter, and three timers in a $2 tiny form factor. The small size and high speed were extremely useful, but the board had never been used in ENPH253 before; we learned a lot when developing a lot of software from scratch, learning along with the instructors.

### H-bridges

![H-Bridge Schematic](res/hbridge.png)

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

## Reflections and Lessons Learned

One of the most important lessons we learned throughtout this course is that a simple and consistent design is key to a great engineering project. Initially, our design was much more complex and therefore had more points of failure. By reducing the 

If we were to do this again, we can definitely improve on our documentation. Though we attempted to use Trello to keep track of our development and progress, things got very messy on our Trello board quickly. It is very important for a well functioning team to have an organized structure to document the development process.

One of the major mistakes that slowed down our progress was that we were too slow to adapt to changes in the rules. Originally, Chewy was worth 3 times as much as a single Ewok, therefore we believed that if we were able to bring back the first Ewok, go up the Zipline and bring back Chewy and the Ewok inside the stronghold, we would be in a very good position to win the competition. However, when the rules changed and Chewy was worth 5 points inside of 9 in total, we did not adapt to this change quickly and stuck to our original plan. Had we re-evaluated the situation, we could have changed our design earlier and had more time to improve on our final design. 

