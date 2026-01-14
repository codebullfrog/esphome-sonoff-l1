# esphome/components/sonoff_l1/light.py

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light

from . import SonoffL1, CONF_SONOFF_L1_ID

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
})


async def to_code(config):
    # --- Extract effects from any key whose string form is "effects" ---
    effects = []
    keys_to_delete = []

    for key, value in config.items():
        if str(key) == "effects":
            if isinstance(value, list):
                # Convert every entry to string (should be 'gradient', 'breath', etc.)
                effects = [str(x) for x in value]
            keys_to_delete.append(key)

    # Remove those keys so ESPHome's effect registry sees NO effects at all
    for key in keys_to_delete:
        config.pop(key, None)

    # --- Normal light registration ---
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # --- Our own simple string-based effects on the C++ side ---
    for effect in effects:
        display_name = effect.replace("_", " ").title()
        cg.add(var.add_effect(display_name, effect))
