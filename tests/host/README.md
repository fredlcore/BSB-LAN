# Host regression tests

Run from the repository root:

```sh
python -m unittest discover -s tests/host -v
```

The tests compile and execute the relevant production source sections with a
host C++ compiler and small hardware stubs. They require Python 3 and a C++11
compiler (`c++`, `g++`, `clang++`, or MSVC). Set `CXX` to select a compiler.
On Windows, an installed Visual Studio C++ toolchain is also detected through
`vswhere`. No Arduino board, network connection, or heating system is used.
MSVC needs the Windows SDK as well as the C++ tools. Alternatively, Windows
users with an existing WSL toolchain can run the command with `wsl` and `python3`.

Coverage includes raw JSON payload preservation, nonmutating string decoding,
the verified RVA scalar and relay decoders, profile selection, and bounded SET
encoding (including the optional differential's disable byte). These host tests
do not replace compiling the complete firmware or testing on the target board.
The M tests also cover recorded flow values, an invalid room sensor, the old
curve scale, and separate pump/open/close fields. Opening/closing direction
cases are synthetic until a live movement is independently observed.
