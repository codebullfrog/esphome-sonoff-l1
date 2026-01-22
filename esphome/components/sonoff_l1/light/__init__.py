import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import light, uart

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]

ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = ns.class_("SonoffL1", light.LightOutput, uart.UARTDevice)

CONF_OUTPUT_ID = "output_id"

CONFIG_SCHEMA = light.OUTPUT_SCHEMA.extend({
    cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(SonoffL1),
    cv.Required(uart.CONF_UART_ID): cv.use_id(uart.UARTComponent),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)   # see next note
    await light.register_light(var, config)
    uart_component = await cg.get_variable(config[uart.CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_component))
