import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID

from . import SonoffL1, CONF_SONOFF_L1_ID

CONF_EFFECTS = "effects"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_SONOFF_L1_ID): cv.declare_id(SonoffL1),

    # Include all standard light options
    **light.LIGHT_SCHEMA.schema,

    # Override effects with simple string list
    cv.Optional(CONF_EFFECTS, default=[]): cv.ensure_list(cv.string),
})
