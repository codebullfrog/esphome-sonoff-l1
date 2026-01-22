import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import light, uart 
from esphome.const import CONF_ID

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]
AUTO_LOAD = ["light"]
MULTI_CONF = True

# C++ namespace
ns = cg.esphome_ns.namespace("sonoff_l1")
sonoff_l1 = ns.class_("sonoff_l1", cg.Component, light.LightOutput, uart.UARTDevice)

CONF_SONOFF_L1_ID = "sonoff_l1_id"

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(sonoff_l1),
    cv.GenerateID(uart.CONF_UART_ID): cv.use_id(uart.UARTComponent),
    # Explicitly allow effects, but don’t enforce a specific schema
    cv.Optional("effects"): cv.ensure_list(cv.Any()),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    uart_component = await cg.get_variable(config["uart_id"])
    cg.add(var.set_uart_parent(uart_component))
