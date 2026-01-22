#pragma

#include "esphome/core/component.h"

# Namespace definition
namespace esphome {
namespace esphome-sonoff-l1 {

class esphome-sonoff-l1 : public Component {

  public:
      // Constructor
      esphome-sonoff-l1();

      void setup() override;
      void dump_config() override;

  protected:
    # Internal fields definition
};

}  //namespace sphome-sonoff-l1
}  //namespace esphome
