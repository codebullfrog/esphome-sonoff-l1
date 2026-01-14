import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light

from . import SonoffL1, CONF_SONOFF_L1_ID

CONF_EFFECTS = "effects"

# Allow effects in YAML as a simple list of strings
CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
    cv.Optional(CONF_EFFECTS, default=[]): cv.ensure_list(cv.string),
})


async def to_code(config):
    # Extract effects from YAML
    effects = config.get(CONF_EFFECTS, [])

    # Remove effects from config so ESPHome's internal registry ignores them
    config[CONF_EFFECTS] = []

    # Create C++ object
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Register effects on C++ side
    for effect in effects:
        display_name = effect.replace("_", " ").title()
        cg.add(var.add_effect(display_name, effect))
