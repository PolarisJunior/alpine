

import os
import sys

DEFAULT_PLATFORM = "windows"
DEFAULT_TARGET = "debug"

platform_arg = ARGUMENTS.get("platform", ARGUMENTS.get("p", False))
target_arg = ARGUMENTS.get("target", ARGUMENTS.get("t", False))
run_on_finish = ARGUMENTS.get("run")

platform = platform_arg if platform_arg else DEFAULT_PLATFORM
target = target_arg if target_arg else DEFAULT_TARGET

# env = Environment(CPPFLAGS=[], CPPDEFINES={}, ENV=os.environ)
env = Environment(CPPFLAGS=[], CPPDEFINES={}, CPPPATH=["#", "./thirdparty/SDL2/include"])

if platform == "windows":
    # MSVC
    # Truncations, narrowing conversions, signed/unsigned comparisons...
    if target == "debug":
        env.Append(CPPFLAGS=["-W3", "/std:c++17"])
    else:
        env.Append(CPPFLAGS=["-O3"])
    disable_nonessential_warnings = ['/wd4267', '/wd4244', '/wd4305', '/wd4018', '/wd4800']    
    env.Append(CPPFLAGS=disable_nonessential_warnings)
    # Set exception handling model to avoid warnings caused by Windows system headers.
    env.Append(CPPFLAGS=["/EHsc"])
    env.Append(MSVC_FLAGS=['/utf8'])
    env.Append(LINKFLAGS=["/subsystem:console"])
else:
    if target == "debug":
        env.Append(CPPFLAGS=["-W3", "-std=c++17", "-g"])
    else:
        env.Append(CPPFLAGS=["-O3"])

if target == "debug":
    env.Append(CPPDEFINES=["ALPINE_DEBUG"])
else:
    env.Append(CPPDEFINES=["ALPINE_RELEASE"])

sources = Glob("./**/*.cpp")

env.Append(LIBS=["SDL2", "SDL2main"])
env.Append(LIBPATH=["thirdparty/SDL2/lib/x64"])

env.Program(target="bin/alpine", source=sources)




