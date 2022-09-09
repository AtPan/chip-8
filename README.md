# chip-8
A CHIP-8 Emulator written in C.

Uses SDL2 for the visuals, but sound is unimplemented.
The code should be cross-platform (so long as the target has SDL2 installed, but this was not tested), but the Makefile is Linux-only at the moment.

There are two modes you can compile to, debug and release. Debug is the default, release must be specified by 'make release'.
Debug mode requires manual stepping through every opcode and displays three items to the terminal:
  1. The state of the processor
  2. The next opcode to execute
  3. The state of the processor after the opcode has executed
To step to the next command, press 'Enter' while the SDL2 window is focused. It is recommnended to keep the terminal behind the emulator window, to see both screens simultaneously.
The clear command is called via 'system("clear")' to clear the terminal and avoid clutter.

-- Known Issues --

Upon exiting the debug build, there will likely be warnings about several memory leaks.
This is almost definitely an SDL issue. Whenever SDL is involved it seems like there is a memory leak problem.
The memory leaked isn't much (probably 3kb at worst), but still noticed by gcc's memory sanitizer.
