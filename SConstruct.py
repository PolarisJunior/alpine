

import os
import sys
import glob

import urllib.request
import zipfile



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
    else:
        import tarfile
        file_data = urllib.request.urlopen("https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.tgz/download")
        data_to_write = file_data.read()
        tar_path = os.path.join("thirdparty", "glew.tgz")
        with open(tar_path, "wb") as f:
            f.write(data_to_write)
        tarfile.open(tar_path).extractall(os.path.join("thirdparty", "glew"))


""" with zipfile.ZipFile("glew.tgz", "r") as zip_ref:
    zip_ref.extractall(".") """

DEFAULT_PLATFORM = "windows"
DEFAULT_TARGET = "debug"
DEFAULT_DIMENSIONS = "3d"

platform_arg = ARGUMENTS.get("platform", ARGUMENTS.get("p", False))
target_arg = ARGUMENTS.get("target", ARGUMENTS.get("t", False))
dimension_arg = ARGUMENTS.get("dimensions", ARGUMENTS.get("d", False))

platform = platform_arg if platform_arg else DEFAULT_PLATFORM
target = target_arg if target_arg else DEFAULT_TARGET
dimension = dimension_arg if dimension_arg else DEFAULT_DIMENSIONS

thirdparty_paths = ["thirdparty/SDL/include", "thirdparty/glew/include", "thirdparty/glm/glm"]
for i in range(len(thirdparty_paths)):
    thirdparty_paths[i] = "-I" + thirdparty_paths[i]

env = Environment(CPPPATH=["#"], CCFLAGS=thirdparty_paths)

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

if dimension == "2d":
    env.Append(CPPDEFINES=["ALPINE_2D"])
else:
    env.Append(CPPDEFINES=["ALPINE_3D"])

# sources = Glob("**/*.cpp", recursive=True)
sources = [x for x in glob.glob("**/*.cpp", recursive=True) if not x.startswith("thirdparty")]


libs = ["SDL2", "SDL2main", "glew32s", "OpenGL32.lib"]
lib_paths = ["thirdparty/SDL/lib/x64", "thirdparty/glew/lib/Release/x64"]

env.Append(LIBS=libs)
env.Append(LIBPATH=lib_paths)

env.Program(target="bin/alpine", source=sources)




