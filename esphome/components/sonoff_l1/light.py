import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1

CONF_SONOFF_L1_ID = "sonoff_l1_id"

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
    # Explicitly allow effects, but don’t enforce a specific schema
    cv.Optional("effects"): cv.ensure_list(cv.Any()),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
