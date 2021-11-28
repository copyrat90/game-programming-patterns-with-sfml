
Interactive Game Programming Patterns (a.k.a IGPP)
https://github.com/copyrat90/interactive-game-programming-patterns

========== NOTICE ==========

This is a binary release for the Windows (x64);
If you're running other OS, you need to download the other version from the link above.

(Unfortunately, only 64-bit release is available;
If you're running a 32-bit Windows, you need to manually build it from the source.)

If you encountered missing DLL files error (e.g. MSVCP140.dll, VCRUNTIME140.dll, etc),
Install the Microsoft Visual C++ Redistributable Runtime Package (2015-2022) from the link below.
https://aka.ms/vs/17/release/vc_redist.x64.exe


========== Running ==========

See ./Patterns/{xx-Pattern}/{yy-Example}/RelWithDebInfo/{xx_Pattern_yy_Example}.exe
That is the executable.

If you're on terminal, you need to change your working directory to the ../RelWithDebInfo
If you don't, the program won't load the assets properly, and will terminate immediately.


========== Licenses ==========

./LICENSE file is the license of the IGPP.
./licenses/ folder contains third-party licenses for the shared libraries.
./Patterns/{xx-Pattern}/{yy-Example}/assets folder contains the license of the asset, with the asset itself.
