import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, uart
from esphome.const import CONF_ID, CONF_OUTPUT_ID

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]

sonoff_l1_ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = sonoff_l1_ns.class_("SonoffL1", light.LightOutput, uart.UARTDevice, cg.Component)

CONFIG_SCHEMA = cv.All(
    light.RGB_LIGHT_SCHEMA.extend(
        {
            cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(SonoffL1),
        }
    ).extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    await uart.register_uart_device(var, config)