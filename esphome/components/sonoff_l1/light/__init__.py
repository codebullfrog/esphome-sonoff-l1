import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import light, uart
from esphome.const import CONF_ID

DOMAIN = "sonoff_l1"

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]
AUTO_LOAD = ["light"]
MULTI_CONF = True

# C++ namespace
ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = ns.class_("SonoffL1", cg.Component, light.LightOutput, uart.UARTDevice)

CONF_SONOFF_L1_ID = "sonoff_l1_id"

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
    cv.GenerateID(uart.CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Optional("effects"): cv.ensure_list(cv.Any()),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    uart_component = await cg.get_variable(config["uart_id"])
    cg.add(var.set_uart_parent(uart_component))
