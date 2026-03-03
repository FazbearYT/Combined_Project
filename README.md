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

# Коммиты модулей

# Настройка
git config --global user.name "Ivan Ivanov"
git config --global user.email "ivan@example.com"

# Клонирование
cd C:\Projects
git clone https://github.com/FazbearYT/Combined_Project.git
cd Combined_Project

# Ветка
git checkout -b feature/boiling_soup # Один из 3 модулей (boiling_soup, wave_surface, rotating_cube)

# Добавление файлов
# (скопируйте BoilingSoupModule.cpp в modules/boiling_soup/)
git add modules/boiling_soup/

# Коммит
git commit -m "Добавлен модуль: Boiling Soup"

# Пуш
git push origin feature/boiling_soup

# → Создайте Pull Request на GitHub
