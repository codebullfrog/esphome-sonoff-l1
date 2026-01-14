import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
    }
).extend(light.EFFECTS_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Register effects
    cg.add(var.add_effect("Colorful Gradient", "gradient"))
    cg.add(var.add_effect("Colorful Breath", "breath"))
    cg.add(var.add_effect("RGB Gradient", "rgb_gradient"))
    cg.add(var.add_effect("RGB Pulse", "rgb_pulse"))
    cg.add(var.add_effect("RGB Breath", "rgb_breath"))
    cg.add(var.add_effect("RGB Strobe", "rgb_strobe"))
    cg.add(var.add_effect("Sound Reactive", "sync"))
