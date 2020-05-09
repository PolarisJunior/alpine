

import os
import sys
import glob

import urllib.request

if not os.path.exists(os.path.join("thirdparty", "glew")):
    if sys.platform == "win32":
        import zipfile
        file_data = urllib.request.urlopen("https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download")
        data_to_write = file_data.read()
        zip_path = os.path.join("thirdparty", "glew.zip")
        with open(zip_path, "wb") as f:
            f.write(data_to_write)
        with zipfile.ZipFile(zip_path, "r") as zip_ref:
            zip_ref.extract("glew-2.1.0/", path=os.path.join("thirdparty", "glew"))
    elif sys.platform == "linux":
        import tarfile
        file_data = urllib.request.urlopen("https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.tgz/download")
        data_to_write = file_data.read()
        tar_path = os.path.join("thirdparty", "glew.tgz")
        with open(tar_path, "wb") as f:
            f.write(data_to_write)
        tar_ref = tarfile.open(tar_path)
        """ tar_ref.extractall(os.path.join("thirdparty", "glew"), members=["glew-2.1.0/"]) """



DEFAULT_PLATFORM = "windows" if sys.platform == "win32" else sys.platform
DEFAULT_TARGET = "debug"
DEFAULT_DIMENSIONS = "3d"

platform_arg = ARGUMENTS.get("platform", ARGUMENTS.get("p", False))
target_arg = ARGUMENTS.get("target", ARGUMENTS.get("t", False))
dimension_arg = ARGUMENTS.get("dimensions", ARGUMENTS.get("d", False))

platform = platform_arg if platform_arg else DEFAULT_PLATFORM
target = target_arg if target_arg else DEFAULT_TARGET
dimension = dimension_arg if dimension_arg else DEFAULT_DIMENSIONS

thirdparty_paths = ["thirdparty/SDL/include", "thirdparty/glew/include", "thirdparty/glm", "thirdparty/json/single_include", "thirdparty/entt/single_include", "thirdparty/SDL2_image/include"]
for i in range(len(thirdparty_paths)):
    thirdparty_paths[i] = "-I" + thirdparty_paths[i]

# Prevent GLEW link warnings, LNK4286.
cpp_defines = ["GLEW_STATIC"]

env = Environment(CPPPATH=["#"], CCFLAGS=thirdparty_paths)

if platform == "windows":
    # MSVC
    # Truncations, narrowing conversions, signed/unsigned comparisons...
    if target == "debug":
        env.Append(CPPFLAGS=["-W3", "/std:c++17"])
    else:
        env.Append(CPPFLAGS=["-O3"])
    # /clr hides the LNK4217 warning.
    disable_nonessential_warnings = ['/wd4267', '/wd4244', '/wd4305', '/wd4018', '/wd4800']    
    env.Append(CPPFLAGS=disable_nonessential_warnings)
    # Set exception handling model to avoid warnings caused by Windows system headers.
    env.Append(CPPFLAGS=["/EHsc"])
    # env.Append(CPPFLAGS=["/clr"])
    env.Append(MSVC_FLAGS=['/utf8'])
    env.Append(LINKFLAGS=["/subsystem:console"])
else:
    env.Append(CPPFLAGS=["-std=c++17"])
    if target == "debug":
        env.Append(CPPFLAGS=["-Wall", "-g", "-fpermissive"])
    else:
        env.Append(CPPFLAGS=["-O3"])

if target == "debug":
    cpp_defines.append("ALPINE_DEBUG")
else:
    cpp_defines.append("ALPINE_RELEASE")

if dimension == "2d":
    cpp_defines.append("ALPINE_2D")
else:
    cpp_defines.append("ALPINE_3D")

# sources = Glob("**/*.cpp", recursive=True)
sources = [x for x in glob.glob("**/*.cpp", recursive=True) if not x.startswith("thirdparty") and not x.startswith("CMakeFiles")]


libs = ["SDL2", "SDL2main", "SDL2_image", "glew32s", "OpenGL32.lib"]
lib_paths = ["thirdparty/SDL/lib/x64", "thirdparty/glew/lib/Release/x64", "thirdparty/SDL2_image/lib/x64"]

env.Append(LIBS=libs)
env.Append(LIBPATH=lib_paths)
env.Append(CPPDEFINES=cpp_defines)

env.Program(target="bin/alpine", source=sources)




