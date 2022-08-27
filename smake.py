from smake import Smake

Smake.library("lib", "lib")
Smake.library("alengine", "alengine", ["lib"])

Smake.extern_library("GL")
Smake.extern_library("glfw")

Smake.executable("test_game", "test/src", ["lib", "alengine", "GL", "glfw"])

Smake.run("test_game")

Smake.DEBUG = True
