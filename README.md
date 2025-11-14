# GearShift
A 2d game in which you drive a car on a road, avoiding other cars or crashing into them.


## Setup

1. Clone this Repository
2. From vcpkg run:
```
vcpkg install sdl2 sdl2-image sdl2-ttf
vcpkg integrate install
```
###### You may need to use `./` or `.\` before the command on Windows
3. If Visual Studio doesn't find the NuGet packages, they may require manual installation
4. If vcpkg didn't interate with Visual Studio and it can't find header files or libraries, adding the paths manually in Visual Studio may be required.

### If you don't have `vcpkg` already:

1. Clone `vcpkg` (Can be found on GitHub at `github.com/microsoft/vcpkg`)
2. Run `bootstrap-vcpkg.bat` -> This will create `vcpkg.exe` in the directory
3. To run vcpkg commands, open the directory where it is in `cmd`, and you can run commands like `./vcpkg install sdl2`