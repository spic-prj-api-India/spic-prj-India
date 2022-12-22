# spic-prj-api
Engine API for the SPiC minor's project.

Copyright (c) 2021 Avans Hogeschool, 's-Hertogenbosch.

Install guide for VCPKG
1) Run "Set-ExecutionPolicy -ExecutionPolicy Unrestricted" in powershell with elevated privileges(remove quotes)
2) Right click on "installing_vcpkg.ps1" and click on "run with powershell"
3) If it asks for input press y

#instalation
The game engine is a static library, so this library must be statically linked to your project. Furthermore it is not out of the box compatible with CMake. Instead, it uses a Visual studio solution file.

Follow these steps to install the libraries used by the game engine (using the package manager VCPKG):
In powershell run the following line “set execution policy unrestricted”. 
Warning make sure you have at least 10 gigabytes left on the C: drive. 
Run the script “Install_VCPKG.ps1” by right clicking on it and then click on “run with powershell” (this can take up to half an hour). 
Now VCPKG will be installed with all included libraries in the folder “C:\dev\vcpkg\vcpkg”.

Follow these steps to install/use the game engine:
Download the zip and extract the zip into your project. Place the folder in a logical place in your project, for example in a folder “external”.
Link the static game library with your game. If you do not know how to do this you can follow the guide [here](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170).
Now you can code games with the examples in this document and the engine documentation outlined here on the website. This website always has the latest information about the engine. 
