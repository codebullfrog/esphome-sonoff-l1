import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

CONF_EFFECTS = "effects"

# Start with a copy of LIGHT_SCHEMA but remove the built‑in effects key
BASE_SCHEMA = light.LIGHT_SCHEMA.copy()
BASE_SCHEMA.pop(CONF_EFFECTS, None)

CONFIG_SCHEMA = BASE_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
    cv.Optional(CONF_EFFECTS, default=[]): cv.ensure_list(cv.string),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Register effects
    for effect in config.get(CONF_EFFECTS, []):
        cg.add(var.add_effect(effect.replace("_", " ").title(), effect))
