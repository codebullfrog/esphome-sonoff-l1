import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

CONF_EFFECTS = "effects"

# Build a minimal schema that includes:
# - the standard light options
# - your component ID
# - a simple list of effect names
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),

    # Include all standard light options (brightness, color, transitions, etc.)
    **light.LIGHT_SCHEMA.schema,

    # Override effects with a simple list of strings
    cv.Optional(CONF_EFFECTS, default=[]): cv.ensure_list(cv.string),
})


async def to_code(config):
    # Create the C++ object
    var = cg.new_Pvariable(config[CONF_SONOFF_L1_ID])

    # Register as a component and as a light output
    await cg.register_component(var, config)
    await light.register_light(var, config)

    # Register each effect name with your C++ add_effect() method
    for effect in config.get(CONF_EFFECTS, []):
        # Convert "rgb_gradient" → "Rgb Gradient" for display
        display_name = effect.replace("_", " ").title()
        cg.add(var.add_effect(display_name, effect))
