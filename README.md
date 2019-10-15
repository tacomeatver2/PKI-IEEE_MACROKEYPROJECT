
# PKI-IEEE MACROKEY PROJECT

This is a project designed for PKI-IEEE, a student chapter of IEEE based at the University of Nebraska-Lincoln's Omaha campus.  
The project is a macrokey (hotkey) project, where each of six keys and the rotary encoder are programmable, allowing you to control your music/video apps and call apps, as well as open a specific website or anything else you can do using a keyboard. This project will give you more experience with soldering and programing a microcontroller.

## Getting Started

These instructions will guide you through the hardware and software design. Please follow the instructions to complete the project.

### Prerequisites

To work on this project it is preferred to have the PCB but it is not required as you could breadboard the project instead.
![PCB](/images/pcb.png)
Format: ![Alt Text](url)
![schematic](/images/sch.png)
Format: ![Alt Text](url)
Components

- Arduino Pro Micro (Chosen because microUSB)
- Keyboard Keys
- Keyboard Keycaps (X-Key)
- Rotary Encoder
- 3mm LED
- 330Ω Resistor
- PCB designed for this project

To program this project you will need Arduino IDE and these import libraries.

- <https://github.com/NicoHood/HID>
- <https://github.com/PaulStoffregen/Encoder>

### Build the hardware

If you have the PCB, solder the components to the correct locations.  
You may adjust the resistor value to change the brightness of the LED.
On the PCB, there are also LEDs for each key which are connected to one GPIO pin.

### Uploading the software

Use Arduino IDE with the previously mentioned libraries imported.
Plug a MicroUSB cable to the Arduino Pro Micro.
In Arduino IDE, go to tools > Boards > Arduino pro micro.
Then choose the correct device through Tools > Boards > Serial Port.  
Press upload to upload the code.  
  
The code can be modifyed by changing the fuction of each button and rotary encoder.  

## Built With

* [EasyEDA]() - The EDA software used to design the PCB.
* [Arduino IDE](https://maven.apache.org/) - Used to program the project.

## Authors

- **Takumi Ito** - Designed project and software template.

See also the list of [contributors](https://github.com/nekotakumi/PKI-IEEE_MACROKEYPROJECT) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
