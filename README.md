# Andromeda

Source code for JellyCar and other my experiments...

To build examples from Tests

1. Install newest VitaSDK using https://github.com/vitasdk/vdpm  
2. install bullet lib from https://github.com/DrakonPL/bullet-physics-vita    

- Go to Tests/Tests/Andromeda_Tests
- make -jn  (where n is numer of cores of your cpu)  

To build JellyCar

1. Install newest VitaSDK using https://github.com/vitasdk/vdpm  

2. Vita 
- Go to Games/JellyCar/JellyCar
- make -jn  (where n is numer of cores of your cpu)  
- Copy eboot.bin to Games/Data
- Create .vpk from all files in Data and copy to vita

3. Windows
- Go to Build/Andromeda
- Open Andromeda.sln with VisualStudio 2015
- Compile Release version
- Copy Build/Andromeda/Release/JellyCar.exe to Games/Data

Tested with latest Vita SDK from https://vitasdk.org/
Windows version is not great... I'was using it for gameplay testing.
In theory booth - vita and windows version should compile without problems.