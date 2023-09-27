# Charger - BMS UART Communication Protocol

## Brief

The Charger and BMS will communicate with each other via UART.  
Any received transmission shall result in an acknowledgement by the receiving party.  
An “ok” will acknowledge a transmission.  
No “ok” after a timeout period shall initialize a resend of the last command.  
Continued failed acknowledgements shall result in the Charger not sending any power and the BMS will stop sending data.

## UART Specifications

The UART shall have the following settings
- Baudrate: 115200
- Parity: none
- Word length: nine (9) bit including parity
- Stop bit: one (1)


## Commands

- ok. Acknowledge a successful transmission.
- voltage. BMS requires a specific voltage level from the charger.
- begin. BMS wants Charger to start sending power.
- end. BMS wants Charger to stop sending power.
- charge. BMS wants to report the state of charge in the battery. BMS will send the current charge level.
- temp. BMS wants to report the current temperature of the battery. BMS will send a temperature after having received the “ok” -command.
- connect. This command will be sent by the BMS to let the Charger know a device is connected.
- beep. The heartbeat command, this will be sent regularly, and failure to receive one of these must cause the Charger to turn off power delivery.

## Handshake

To ensure both devices are aware of a new connection, a handshake will take place.

The Charger will not send out any power on the outputs until it detects a connection.  
BMS sends the “connect” -command.  
Charger will respond by sending the “ok”-command.  
BMS sends the "voltage" -command, followed by a colon and finally followed by one of eight (8) voltage levels.

### Voltage levels
As part of the handshake the BMS will reqest one of the following voltage levels
- 3.3 V
- 4.2 V
- 5 V
- 6 V
- 7.4 V
- 9 V
- 10 V
- 11.5 V

## Heartbeat

To prevent a potentially dangerous situation where the BMS is abruptly disconnected without time to send an “end” -command, a periodic heartbeat will be in place.  

BMS will send the “beep” -command at a regular interval.  
Charger does not have to respond to this command, as an abrupt disconnection of the BMS does not harm the BMS, nor does it pose any danger to users.  
If no heartbeat is detected, Charger shall instantly terminate power delivery until a new handshake is completed.  

## Initializing power transmission

BMS Will send the “begin” -command.  
Charger will respond with “ok”.  
Charger begins and continues to send power until the BMS wants to stop.

## Ending power transmission

When the BMS wants to stop receiving power from the Charger, the BMS will send the “end”-command.

BMS sends the “end” -command.  
Charger acknowledges with “ok”.  
Charger stops sending power.  

## Data transmissions

The BMS will send status updates to the Charger, these updates will include the following data

Battery temperature.
Current battery charge level.

This data will be sent by using the “temp” and “charge” -commands as prefixes, followed by a colon and then followed by the relevant data.

## Transmission frequency and heartbeat timeout

The BMS will send data to the Charger every time some relevant data has changed.  
The heartbeat will be sent twice per second, to ensure safe operation even if the BMS is abruptly disconnected.

