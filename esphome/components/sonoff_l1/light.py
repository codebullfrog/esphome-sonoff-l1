import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light, uart
from esphome.const import CONF_OUTPUT_ID, CONF_ID
from esphome import automation

CODEOWNERS = ["@codebullfrog"]
DEPENDENCIES = ["uart"]

sonoff_l1_ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = sonoff_l1_ns.class_("SonoffL1", light.LightOutput, uart.UARTDevice, cg.Component)

# Actions for modes
SetModeColorfulAction = sonoff_l1_ns.class_("SetModeColorfulAction", automation.Action)
SetModeColorfulGradientAction = sonoff_l1_ns.class_("SetModeColorfulGradientAction", automation.Action)
SetModeColorfulBreathAction = sonoff_l1_ns.class_("SetModeColorfulBreathAction", automation.Action)
SetModeDiyGradientAction = sonoff_l1_ns.class_("SetModeDiyGradientAction", automation.Action)
SetModeDiyPulseAction = sonoff_l1_ns.class_("SetModeDiyPulseAction", automation.Action)
SetModeDiyBreathAction = sonoff_l1_ns.class_("SetModeDiyBreathAction", automation.Action)
SetModeDiyStrobeAction = sonoff_l1_ns.class_("SetModeDiyStrobeAction", automation.Action)
SetModeRgbGradientAction = sonoff_l1_ns.class_("SetModeRgbGradientAction", automation.Action)
SetModeRgbPulseAction = sonoff_l1_ns.class_("SetModeRgbPulseAction", automation.Action)
SetModeRgbBreathAction = sonoff_l1_ns.class_("SetModeRgbBreathAction", automation.Action)
SetModeRgbStrobeAction = sonoff_l1_ns.class_("SetModeRgbStrobeAction", automation.Action)
SetModeSyncToMusicAction = sonoff_l1_ns.class_("SetModeSyncToMusicAction", automation.Action)

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

# Register actions
SONOFF_L1_ACTION_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.use_id(SonoffL1),
})

@automation.register_action(
    "sonoff_l1.set_mode_colorful",
    SetModeColorfulAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_colorful_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_colorful_gradient",
    SetModeColorfulGradientAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_colorful_gradient_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_colorful_breath",
    SetModeColorfulBreathAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_colorful_breath_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_diy_gradient",
    SetModeDiyGradientAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_diy_gradient_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_diy_pulse",
    SetModeDiyPulseAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_diy_pulse_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_diy_breath",
    SetModeDiyBreathAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_diy_breath_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_diy_strobe",
    SetModeDiyStrobeAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_diy_strobe_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_rgb_gradient",
    SetModeRgbGradientAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_rgb_gradient_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_rgb_pulse",
    SetModeRgbPulseAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_rgb_pulse_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_rgb_breath",
    SetModeRgbBreathAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_rgb_breath_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

@automation.register_action(
    "sonoff_l1.set_mode_rgb_strobe",
    SetModeRgbStrobeAction,
    SONOFF_L1_ACTION_SCHEMA,
)
async def set_mode_rgb_strobe_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var

CONF_SENSITIVE = "sensitive"
CONF_SPEED = "speed"

@automation.register_action(
    "sonoff_l1.set_mode_sync_to_music",
    SetModeSyncToMusicAction,
    SONOFF_L1_ACTION_SCHEMA.extend({
        cv.Optional(CONF_SENSITIVE, default=10): cv.int_range(min=1, max=100),
        cv.Optional(CONF_SPEED, default=50): cv.int_range(min=1, max=100),
    }),
)
async def set_mode_sync_to_music_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    cg.add(var.set_sensitive(config[CONF_SENSITIVE]))
    cg.add(var.set_speed(config[CONF_SPEED]))
    return var