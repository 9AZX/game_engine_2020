# Cloning the project

When cloning the project you also have to initialize git submodules using this command: `git submodule update --init`  
Right now the vcpkg submodule only exists on the `develop` branch so you will have to clone the project, checkout the `develop` branch and then run `git submodule update --init`.

# Building the project

The project use [vcpkg](https://github.com/microsoft/vcpkg) as a submodule so all you have to do is clone the project as described in [Cloning the project](#cloning-the-project).  
CMake will then build vcpkg and the dependencies of the project written in `vcpkg.json`.