import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

# Effect names
CONF_GRADIENT = "gradient"
CONF_BREATH = "breath"
CONF_RGB_GRADIENT = "rgb_gradient"
CONF_RGB_PULSE = "rgb_pulse"
CONF_RGB_BREATH = "rgb_breath"
CONF_RGB_STROBE = "rgb_strobe"
CONF_SYNC = "sync"

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),

    cv.Optional(CONF_GRADIENT): cv.invalid("No options allowed"),
    cv.Optional(CONF_BREATH): cv.invalid("No options allowed"),
    cv.Optional(CONF_RGB_GRADIENT): cv.invalid("No options allowed"),
    cv.Optional(CONF_RGB_PULSE): cv.invalid("No options allowed"),
    cv.Optional(CONF_RGB_BREATH): cv.invalid("No options allowed"),
    cv.Optional(CONF_RGB_STROBE): cv.invalid("No options allowed"),
    cv.Optional(CONF_SYNC): light.EFFECT_SCHEMA,
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Register effects
    if CONF_GRADIENT in config:
        cg.add(var.add_effect("Colorful Gradient", "gradient"))

    if CONF_BREATH in config:
        cg.add(var.add_effect("Colorful Breath", "breath"))

    if CONF_RGB_GRADIENT in config:
        cg.add(var.add_effect("RGB Gradient", "rgb_gradient"))

    if CONF_RGB_PULSE in config:
        cg.add(var.add_effect("RGB Pulse", "rgb_pulse"))

    if CONF_RGB_BREATH in config:
        cg.add(var.add_effect("RGB Breath", "rgb_breath"))

    if CONF_RGB_STROBE in config:
        cg.add(var.add_effect("RGB Strobe", "rgb_strobe"))

    if CONF_SYNC in config:
        cg.add(var.add_effect("Sound Reactive", "sync"))
