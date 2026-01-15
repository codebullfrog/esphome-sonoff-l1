import esphome.codegen as cg
from esphome.components import light

sonoff_l1_ns = cg.esphome_ns.namespace("sonoff_l1")
SonoffL1 = sonoff_l1_ns.class_("SonoffL1", cg.Component, light.LightOutput)
