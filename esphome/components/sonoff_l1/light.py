import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, uart
from esphome.const import CONF_ID

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]

ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = ns.class_("SonoffL1", light.LightOutput, uart.UARTDevice)

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.Required(uart.CONF_UART_ID): cv.use_id(uart.UARTComponent),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await light.register_light(var, config)
    uart_component = await cg.get_variable(config[uart.CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_component))
