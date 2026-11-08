"""Compile and execute small firmware source sections without Arduino hardware."""
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def between(source, start, end):
    """Keep the test bound to the production section, including future edits."""
    return source.split(start, 1)[1].split(end, 1)[0]


def compiler_environment():
    env = os.environ.copy()
    configured = env.get("CXX")
    if configured:
        return configured, env
    for name in ("c++", "g++", "clang++", "cl"):
        found = shutil.which(name)
        if found:
            return found, env
    if os.name == "nt":
        vswhere = Path(env.get("ProgramFiles(x86)", "C:/Program Files (x86)")) / "Microsoft Visual Studio/Installer/vswhere.exe"
        if vswhere.exists():
            installation = subprocess.check_output(
                [str(vswhere), "-latest", "-products", "*", "-requires",
                 "Microsoft.VisualStudio.Component.VC.Tools.x86.x64", "-property", "installationPath"],
                text=True).strip()
            if installation:
                setup = Path(installation) / "VC/Auxiliary/Build/vcvars64.bat"
                # Capture only compiler environment paths; never print the environment.
                with tempfile.TemporaryDirectory(prefix="bsb-lan-msvc-") as directory:
                    bootstrap = Path(directory) / "environment.cmd"
                    bootstrap.write_text('@echo off\ncall "' + str(setup) +
                                         '" >nul\nif errorlevel 1 exit /b 1\nset\n')
                    output = subprocess.check_output(
                        ["cmd", "/d", "/c", str(bootstrap)],
                        text=True, errors="replace")
                for line in output.splitlines():
                    key, sep, value = line.partition("=")
                    if sep and key.upper() in ("PATH", "INCLUDE", "LIB", "LIBPATH"):
                        env[key.upper()] = value
                found = shutil.which("cl", path=env.get("PATH"))
                if found:
                    return found, env
    raise unittest.SkipTest("A host C++ compiler is required (set CXX or install g++/clang++/MSVC).")


def compile_and_run(source):
    compiler, env = compiler_environment()
    with tempfile.TemporaryDirectory(prefix="bsb-lan-host-test-") as directory:
        directory = Path(directory)
        cpp = directory / "regression.cpp"
        executable = directory / ("regression.exe" if os.name == "nt" else "regression")
        cpp.write_text(source, encoding="utf-8")
        if Path(compiler).stem.lower() == "cl":
            command = [compiler, "/nologo", "/std:c++14", "/EHsc", "/W4", "/WX",
                       str(cpp), "/Fe:" + str(executable), "/Fo:" + str(directory / "regression.obj")]
        else:
            command = [compiler, "-std=c++11", "-Wall", "-Wextra", "-Werror", str(cpp), "-o", str(executable)]
        build = subprocess.run(command, cwd=directory, env=env, capture_output=True, text=True)
        if build.returncode:
            raise AssertionError("Host harness compilation failed:\n" + build.stdout + build.stderr)
        run = subprocess.run([str(executable)], cwd=directory, env=env, capture_output=True, text=True)
        if run.returncode:
            raise AssertionError("Firmware regression failed:\n" + run.stdout + run.stderr)
