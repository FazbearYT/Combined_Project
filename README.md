# CombinedProject

```powershell
# Установить vcpkg (Выполнить в powershell поочередно)
cd C:\

git clone https://github.com/microsoft/vcpkg.git

cd vcpkg

.\bootstrap-vcpkg.bat

# Установить freeglut
.\vcpkg install freeglut:x64-windows

# Интегрировать с Visual Studio
.\vcpkg integrate install
