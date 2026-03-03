# CombinedProject

```powershell
# Установить vcpkg
cd C:\
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Установить freeglut
.\vcpkg install freeglut:x64-windows

# Интегрировать с Visual Studio
.\vcpkg integrate install
