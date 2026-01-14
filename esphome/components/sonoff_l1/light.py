import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

CONF_EFFECTS = "effects"

# Build a schema WITHOUT the built-in effects key
BASE_LIGHT_SCHEMA = {
    key: value
    for key, value in light.LIGHT_SCHEMA.schema.items()
    if key != "effects"
}

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
    **BASE_LIGHT_SCHEMA,
    cv.Optional(CONF_EFFECTS, default=[]): cv.ensure_list(cv.string),
})


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Register effects
    for effect in config.get(CONF_EFFECTS, []):
        display_name = effect.replace("_", " ").title()
        cg.add(var.add_effect(display_name, effect))
