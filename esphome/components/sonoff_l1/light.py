import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

CONF_EFFECTS = "effects"

# Use the normal LIGHT_SCHEMA so all usual light options work
CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
})


async def to_code(config):
    # Grab the effects from the YAML before ESPHome touches them
    effects = config.get(CONF_EFFECTS, [])

    # Strip effects so ESPHome's built-in registry logic sees an empty list
    # This avoids the EStr.items() crash.
    if CONF_EFFECTS in config:
        config[CONF_EFFECTS] = []

    # Create the C++ object
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])

    # Register as a component and as a light output
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Now add our own simple string-based effects directly to the C++ class
    for effect in effects:
        display_name = effect.replace("_", " ").title()
        cg.add(var.add_effect(display_name, effect))
