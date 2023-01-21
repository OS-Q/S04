"""
Arduino

Arduino Wiring-based Framework allows writing cross-platform software to
control devices attached to a wide range of Arduino boards to create all
kinds of creative coding, interactive objects, spaces or physical experiences.

http://www.stm32duino.com
"""

import sys
from os.path import join, isfile

from SCons.Script import DefaultEnvironment, SConscript

env = DefaultEnvironment()
mcu = env.BoardConfig().get("build.mcu")
core = env.BoardConfig().get("build.core", "")

if core == "maple":
    build_script = join(
        env.PioPlatform().get_package_dir("framework-arduinoststm32-maple"),
        "tools", "platformio-build-%s.py" % mcu[0:7])
elif core == "stm32l0":
    build_script = join(
        env.PioPlatform().get_package_dir("framework-arduinoststm32l0"),
        "tools", "platformio-build.py")
else:
    build_script = join(env.PioPlatform().get_package_dir(
        "framework-arduinoststm32"), "tools", "platformio", "platformio-build.py")

if not isfile(build_script):
    sys.stderr.write("Error: Missing PlatformIO build script %s!\n" % build_script)
    env.Exit(1)

SConscript(build_script)
