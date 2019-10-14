
DEFAULT_PLATFORM = "windows"
DEFAULT_TARGET = "debug"

platform_arg = ARGUMENTS.get("platform", ARGUMENTS.get("p", False))
target_arg = ARGUMENTS.get("target", ARGUMENTS.get("t", False))

platform = platform_arg if platform_arg else DEFAULT_PLATFORM
target = target_arg if target_arg else DEFAULT_TARGET

env = Environment(CPPFLAGS=[], CPPDEFINES={})

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
else:
    if target == "debug":
        env.Append(CPPFLAGS=["-W3", "-std=c++17", "-g"])
    else:
        env.Append(CPPFLAGS=["-O3"])

env.Program(target="alpine", source=["./main/main.cpp"])