#include "esphome.h"
#include "HX711.h"

class CustomBedSensor : public PollingComponent {
  
  public:
  HX711 scale_1;  
  HX711 scale_2;
  Sensor *first = new Sensor();
  Sensor *second = new Sensor();

  CustomBedSensor() : PollingComponent(15000) {}

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }
  
  void setup() override {
    setup_scale(scale_1, 2, 0);
    setup_scale(scale_2, 4, 5);
  }

  void update() override {
    read_scale(scale_1, 1);
    read_scale(scale_2, 2);
  }

  void setup_scale(HX711 scale, int dt, int sck){
    scale.begin(dt, sck);   // Start scale on specified pins
    scale.wait_ready();  //Ensure scale is ready, this is a blocking function
    scale.set_scale();                                  
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
       first->publish_state(reading);
    }
    if(number == 2){
       second->publish_state(reading);
    }
    scale.power_down();    
  }
};
