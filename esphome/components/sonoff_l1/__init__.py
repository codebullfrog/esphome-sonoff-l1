import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import light
from esphome.const import CONF_ID

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = [ ]
AUTO_LOAD = [ ]
MULTI_CONF = True

# C++ namespace
ns = cg.esphome_ns.namespace("sonoff_l1")
sonoff_l1 = ns.class_("sonoff_l1", cg.Component)

CONF_SONOFF_L1_ID = "sonoff_l1_id"

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(sonoff_l1),
    # Explicitly allow effects, but don’t enforce a specific schema
    cv.Optional("effects"): cv.ensure_list(cv.Any()),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
