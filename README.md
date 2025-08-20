quick sfml engine I wrote up from a prompt question

specifically look at management of movement at high speeds.

build intsructions (windows im not sure will work ootb about was using minGW on linux so the makefile might a little edit under cygwin:
linux:
`make`
Windows:
`make wondows`


to fix build for mingw , change the `wcxx` variable to your specific compile command the makefile
the ld flags should be ok but the one to look at in `wlibs`
