cl *.cpp /DRELEASE /Fe:engine.exe /link /SUBSYSTEM:WINDOWS user32.lib
cl *.cpp /DDEBUG /Fe:engine_debug.exe /ZI /link /SUBSYSTEM:WINDOWS user32.lib


