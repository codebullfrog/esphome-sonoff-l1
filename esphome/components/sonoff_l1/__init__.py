import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, uart
from esphome.const import CONF_ID

sonoff_l1_ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = sonoff_l1_ns.class_("SonoffL1", cg.Component, light.LightOutput, uart.UARTDevice)

CONF_SONOFF_L1_ID = "sonoff_l1_id"

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),
}).extend(uart.UART_DEVICE_SCHEMA)
