# WSN-Dev-Board
This is the repository of sixfab wireless sensor network development board. 

## Product Description
WSN Dev. Kit is a board that combining Arduino and Sub1 GHz communication module with the rechargeable battery functionality. It has Atmega 328 microcontroller and cc1101 868 Mhz radio module.There are also built-in humidity and temperature sensors. You can also connect Arduino compatible sensors by using the open pins and vary your project.

## Detailed Features
* 868 MHz Wireless Communication (Up to 100 meters outdoor)
* Easy programming with Arduino nano-based microcontroller
* Rechargeable 1200 mAh Li-on Battery
* Built-in temperature sensor (HDC1080) (-40 +125 C)
* Built-in humidity sensor (HDC1080) (0% 100%)
* Easy charge with nano USB socket
* Communication and programming via nano USB socket
* 3 user LED’s
* Easy connection to external sensors (SPI, I2C, Analog Pins and General IO Pins)
* Usage without battery via USB socket
* SMD chip antenna
* Uart switching (USB<>Open pins)

## Attention
* ! Use only 3.7V CR123A Rechargeable battery with WSN Dev. Kit
* ! All data pins work with 3.3V reference. Any other voltage level should harm your device.
* ! “PIN<>USB” switch should be “USB” side for programming
* ! Battery begins to charge when you plug the USB. If the battery is full, please unplug the USB for longer battery life.

## Examples
1. Basic n2n (node to node) communication example
   * Requires min 2 Sixfab WSN Dev Board
   * Add firstly the libraries to your arduino library path.
   * Upload Rx.ino file to one of the WSN Dev Boards in order to make this one reciever node.
   * Upload Tx.ino file to another WSN Dev Board in order to make this one the transmitter node.
   * That's OK.
   
2. Basic wireless sensor network example
   * Requires min 3 Sixfab WSN Dev Board
   * This one will add soon.
   
## Applications
* node to node wireless communication
* smart farming sensor networks
* smart cities sensor networks
* smart home sensor networks
* Internet of Things (IoT) sensor networks
* Smart door lock
* Smart lightning
* Custom Remote Controller
