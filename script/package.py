import os, sys, re
import shutil
import time
# from gllogger import gL

# os.getcwd()
cwd = os.path.dirname(os.path.abspath(__file__))


def _copytree_h_file(dir, files):
    l = []
    for file in files:
        _abs_path = os.path.join(dir, file)
        if os.path.isfile(_abs_path):
            if not file.endswith('.h'):
                l.append(file)
    return l


_name = "frameless"
if __name__ == "__main__":
    _platform = sys.argv[1]
    _root_path = os.path.split(cwd)[0]
    _outside_path = os.path.split(_root_path)[0]
    _src_path = os.path.abspath(os.path.join(_root_path, "src"))
    _include_path = os.path.abspath(os.path.join(_root_path, "include"))
    _lib_path = os.path.abspath(os.path.join(_root_path, "lib", ))
    if os.path.exists(_include_path): shutil.rmtree(_include_path)
    # if os.path.exists(_lib_path): shutil.rmtree(_lib_path)

    _include_path = os.path.join(_include_path, _name)
    if _platform in ("linux64",):
        _lib_path = os.path.join(_lib_path, "linux64")
    elif _platform in ("win32msvc",):
        _lib_path = os.path.join(_lib_path, "win32msvc")
    elif _platform in ("win32mingw",):
        _lib_path = os.path.join(_lib_path, "win32mingw")

    elif _platform in ("darwin",):
        _lib_path = os.path.join(_lib_path, "macos")
    elif _platform in ("android",):
        _lib_path = os.path.join(_lib_path, "android")
    _lib_path = os.path.join(_lib_path, _name)

    time.sleep(0.5)
    os.makedirs(_lib_path, exist_ok=True)
    os.makedirs(_include_path)
    shutil.copytree(_src_path, _include_path, dirs_exist_ok=True, ignore=_copytree_h_file)

    _build_output = []
    if _platform in ("linux64",):
        _d1 = f"build-{_name}-Desktop_Qt_5_15_2_GCC_64bit-Release"
        _build_output.append(os.path.join(_outside_path, _d1, f"lib{_name}.so"))
    elif _platform in ("win32msvc","win32mingw",):
        if _platform in ("win32msvc",):
            _d1 = f"build-{_name}-Desktop_Qt_5_15_2_MSVC2019_32bit-Release"
            _build_output.append(os.path.join(_outside_path, _d1, f"{_name}.dll"))
            _build_output.append(os.path.join(_outside_path, _d1, f"{_name}.lib"))
        elif _platform in ("win32mingw",):
            _d1 = f"build-{_name}-Desktop_Qt_5_15_2_MinGW_32_bit-Release"
            _build_output.append(os.path.join(_outside_path, _d1, f"lib{_name}.dll"))
#            _build_output.append(os.path.join(_outside_path, _d1, f"lib{_name}.dll.a"))
    elif _platform in ("android",):
        _d1 = f"build-{_name}-Qt_5_15_2_Clang_Multi_Abi-Release"
        _build_output.append(
            os.path.join(_outside_path, _d1, "android-build", "libs", "armeabi-v7a", f"lib{_name}_armeabi-v7a.so"))
    for i in _build_output:
        shutil.copy(i, _lib_path)
