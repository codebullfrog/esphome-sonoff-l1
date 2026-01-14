import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

sonoff_l1_ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = sonoff_l1_ns.class_("SonoffL1", cg.Component, cg.LightOutput)

CONF_SONOFF_L1_ID = "sonoff_l1_id"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await cg.register_light(var, config)
