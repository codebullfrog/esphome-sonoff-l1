import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, uart
from esphome.const import CONF_OUTPUT_ID, CONF_EFFECTS

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]

sonoff_l1_ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = sonoff_l1_ns.class_("SonoffL1", light.LightOutput, uart.UARTDevice, cg.Component)

# Define effect classes
ColorfulEffect = sonoff_l1_ns.class_("ColorfulEffect", light.LightEffect)
ColorfulGradientEffect = sonoff_l1_ns.class_("ColorfulGradientEffect", light.LightEffect)
ColorfulBreathEffect = sonoff_l1_ns.class_("ColorfulBreathEffect", light.LightEffect)
DiyGradientEffect = sonoff_l1_ns.class_("DiyGradientEffect", light.LightEffect)
DiyPulseEffect = sonoff_l1_ns.class_("DiyPulseEffect", light.LightEffect)
DiyBreathEffect = sonoff_l1_ns.class_("DiyBreathEffect", light.LightEffect)
DiyStrobeEffect = sonoff_l1_ns.class_("DiyStrobeEffect", light.LightEffect)
RgbGradientEffect = sonoff_l1_ns.class_("RgbGradientEffect", light.LightEffect)
RgbPulseEffect = sonoff_l1_ns.class_("RgbPulseEffect", light.LightEffect)
RgbBreathEffect = sonoff_l1_ns.class_("RgbBreathEffect", light.LightEffect)
RgbStrobeEffect = sonoff_l1_ns.class_("RgbStrobeEffect", light.LightEffect)
SyncToMusicEffect = sonoff_l1_ns.class_("SyncToMusicEffect", light.LightEffect)

CONF_SENSITIVE = "sensitive"
CONF_SPEED = "speed"

@light.register_effect(
    "sonoff_l1.colorful",
    ColorfulEffect,
    "Colorful",
    {}
)
async def colorful_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.colorful_gradient",
    ColorfulGradientEffect,
    "Colorful Gradient",
    {}
)
async def colorful_gradient_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.colorful_breath",
    ColorfulBreathEffect,
    "Colorful Breath",
    {}
)
async def colorful_breath_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.diy_gradient",
    DiyGradientEffect,
    "DIY Gradient",
    {}
)
async def diy_gradient_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.diy_pulse",
    DiyPulseEffect,
    "DIY Pulse",
    {}
)
async def diy_pulse_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.diy_breath",
    DiyBreathEffect,
    "DIY Breath",
    {}
)
async def diy_breath_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.diy_strobe",
    DiyStrobeEffect,
    "DIY Strobe",
    {}
)
async def diy_strobe_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.rgb_gradient",
    RgbGradientEffect,
    "RGB Gradient",
    {}
)
async def rgb_gradient_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.rgb_pulse",
    RgbPulseEffect,
    "RGB Pulse",
    {}
)
async def rgb_pulse_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.rgb_breath",
    RgbBreathEffect,
    "RGB Breath",
    {}
)
async def rgb_breath_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.rgb_strobe",
    RgbStrobeEffect,
    "RGB Strobe",
    {}
)
async def rgb_strobe_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config["name"])

@light.register_effect(
    "sonoff_l1.sync_to_music",
    SyncToMusicEffect,
    "Sync to Music",
    {
        cv.Optional(CONF_SENSITIVE, default=10): cv.int_range(min=1, max=100),
        cv.Optional(CONF_SPEED, default=50): cv.int_range(min=1, max=100),
    }
)
async def sync_to_music_effect_to_code(config, effect_id):
    effect = cg.new_Pvariable(effect_id, config["name"])
    cg.add(effect.set_sensitive(config[CONF_SENSITIVE]))
    cg.add(effect.set_speed(config[CONF_SPEED]))
    return effect

CONFIG_SCHEMA = light.RGB_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(SonoffL1),
    }
).extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    await uart.register_uart_device(var, config)