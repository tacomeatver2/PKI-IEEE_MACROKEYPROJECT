# PKI-IEEE MACROKEY PROJECT
This is a project for PKI-IEEE a student chapter of IEEE at University of Nebraska-Lincoln at Omaha.  
The project is a macrokey(hotkey) project, each keys and rotary encoder is programmable and you can control your mucsic/video app, call apps, open a specific website, and anything you can imagine using a keyboard. This project will give you more soldering experience and programing a Microcontroller.  

## Getting Started

These instructions will get you instructions on the hardware design and the software design. Please follow the instructions to complete the project. 

### Prerequisites

To work on this project it is perfered to have the PCB but it is not required.

Components
- Arduino pro Micro (Choose because microUSB)
- Keyboard keys
- Keyboard Keycaps (X-Key)
- Rotary encoder
- 3mm LED
- 330Ω Resistor
- PCB

To program this project you will need Arduino IDE.
import libraries
- https://github.com/NicoHood/HID
- https://github.com/PaulStoffregen/Encoder



### Build the hardware

If you have the PCB, solder the components to the correct position.  
You may change the resistor for the LED to change the brightness.  
On the PCB there are also LEDs for each key which is connected to one GPIO pin.  

### Uploading the software

Use Arduino IDE with the libraries imported.  
Plug a microusb cable to the Arduino pro micro.  
Go to tools > Boards > Arduino pro micro.  
Then choose the correct device through Tools > Boards > Serial Port.  
Press upload to upload the code.  
  
The code can be modifyed by changing the fuction of each button and rotary encoder.  

## Built With

* [EasyEDA]() - The EDA software used to design the PCB
* [Arduino IDE](https://maven.apache.org/) - Used to program the project

## Authors

* **Takumi Ito** - 

See also the list of [contributors](https://github.com/nekotakumi/PKI-IEEE_MACROKEYPROJECT) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
