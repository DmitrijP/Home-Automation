#include "esphome.h"
#include "HX711.h"

class CustomBedSensor : public PollingComponent {
  
  public:
  HX711 scale_1;  
  HX711 scale_2;
  int sensor_1_factor = 0; 
  int sensor_2_factor = 0; 
  Sensor *first_scale_sensor = new Sensor();
  Sensor *second_scale_sensor = new Sensor();
  Sensor *factor1 = new Sensor();
  Sensor *factor2 = new Sensor();

  CustomBedSensor() : PollingComponent(15000) {}

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }
  
  void setup() override {
    setup_scale(scale_1, 2, 0, sensor_1_factor);
    setup_scale(scale_2, 4, 5, sensor_2_factor);
  }

  void update() override {
    read_scale(scale_1, 1);
    read_scale(scale_2, 2);
  }

  void setup_scale(HX711 scale, int dt, int sck, int scaleOffset){
    scale.begin(dt, sck);   // Start scale on specified pins
    scale.wait_ready();  //Ensure scale is ready, this is a blocking function
    scale.set_scale(scaleOffset);                                  
    scale.wait_ready();
    scale.tare();        // Tare scale on startup
    scale.wait_ready();
  }

  void read_scale(HX711 scale, int number){
    scale.power_up();
    float reading; 
    float raw; 
    scale.wait_ready(); 
    scale.set_scale(2000);  
    scale.wait_ready();
    reading = scale.get_units(10);        
    raw = scale.read_average(5);  
    if (reading < 0) {
        reading = 0.00;   
    }

    if(number == 1){
       factor1->publish_state(sensor_1_factor);
       first_scale_sensor->publish_state(reading);
    }
    if(number == 2){
       factor2->publish_state(sensor_2_factor);
       second_scale_sensor->publish_state(reading);
    }
    scale.power_down();    
  }
};
