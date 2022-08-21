# Bed Occupancy Sensor
Contains the code for my custom bed occupancy sensor to use for home automations that require the knowledge of 
a bed being occupied.

<p align="center">
  <img src="img/IMG_20220821_125341788.jpg" width="350" title="The Sensor Package"
</p>

The sensor uses ESPHOME in combination with a ESP8266 controller and two HX711 sensors.\
It is able to transmit the weight of two zones over MQTT or the native API.
