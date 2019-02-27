# MITKa (Material Identifying Trash Can)

### OVERVIEW
MITKa is a system to sort automatically different types of materials in trash cans. This is done by placing identifying tags on the materials so that the sensors inside the trash can activate a mechanical arm to place them in their right places.

### WHY DO WE NEED MITKa?
40% of people in the world die because of environmental pollution, namely water, soil and air. According to scientists, in the territory of 20 national parks of the United States there are at least 70 varieties of toxic substances. The pollution of the planet reduces the life of each person by 10 years and that number continues to increase.
scientists say that because of different factors, we have to live on earth for about 100 years, one of them is non-recycling and wasting.
Fortunately, there are many people in the world who are worried about the future of their home and doing at least a small but contributing to protect the planet. They sort garbage. But there are those who want to help. but they can not or do not know how to do it. For that we need MITKa.
MITKa it is an easier way of recycling. You just put your waste in a bin and MITKa is doing all your work.

**WHY MITKa?**
* this is a completely new product, and completely new technology
* you can easily sort the rubbish
* with recycling you can reduce your outcomes
* the streets will be less clogged
* everybody can use it (any age, budget)

**MATERIALS NEEDED**

The basis of our product is not only the bin (it can be made from any available material in any country), but a copper wire. For this installation you need:


For power transmission:
* 2 coils with a wire length of about 5 meters. Coil diameter - 3 mm, number of turns - 30.
* Resistors: 1kOhm
* BJT transistors: 2N3904
* Keyes SR1y Relay module circuit
* 3V battery (1.5v *2)
* LEDs of different colors.

Sensors & Servo Motors (separator) :
* Adafruit APDS9960 Proximity, Light, RGB, and Gesture Sensor
* Servo motor *2 (depends on the number of different materials)

Microcontroller : 
* Arduino
* 9V battery

For display : (optional)
* LEDs of different colors
* 10kOhm potentiometer 306E 
* LCD display

Others :
* Wires and breadboard


**HOW DOES IT WORK?**
the principle of work is based on induction. Receiver coil should be putted in waste material (plastic bottle for example) The simplest and the first scheme that can be introduced:

![](https://user-images.githubusercontent.com/44177829/53070845-b37ad100-34e0-11e9-8a45-f937d4a8b4f0.png)
![](https://user-images.githubusercontent.com/44177829/53070889-d311f980-34e0-11e9-9f47-8e93c5861840.png)
       
**How does it light up the LED at a distance?**

This happens due to induction. Let's use a transformer for example. A normal transformer has a core with wires on either sides. Let's suppose the wire on each side of the transformer is equal in amount. When electricity is passed through one coil, the coil becomes an electromagnet. If the electricity is oscillating voltage, that means the voltage would keep rising and dropping. So when an oscillating electricity is passed through the coil, the wire gains properties of electromagnet and then again loses electromagnetism when the voltage drops. A coil of wire becoming electromagnet and then losing its electromagnetic characteristics really fast is just like a magnet moving really fast in and out of the second coil. And when you pass a magnet really fast through coil of wires, you produce electricity, so the oscillating voltage in one coil on the transformer, induces electricity in the other coil of wire, and thus wirelessly electricity is transferred from one coil to the other. In our circuit, the air is the core, and there is oscillating voltage going through the first coil, so you induce A.C electricity in the second coil and light up the bulb!


 
**Final circuits**
![](https://user-images.githubusercontent.com/47625569/53072038-449f7700-34e4-11e9-9095-3a48fd2dd2c6.png)

Light detection: 

![](https://user-images.githubusercontent.com/47625569/53072063-5254fc80-34e4-11e9-9e30-12c07385e06b.png)

Wireless power transmission:

![](https://user-images.githubusercontent.com/47625569/53072293-09ea0e80-34e5-11e9-9029-4eeae24d57dc.png)

Proximity sensor:

![](https://user-images.githubusercontent.com/47625569/53072077-5aad3780-34e4-11e9-8466-6da6bac48a69.png)
