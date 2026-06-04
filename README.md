## execution option 1:
# Compilation depuis les sources
- Qt6 installé (`libqt6widgets6`, `qt6-base-dev`)
- CMake ≥ 3.16
- Compilateur C++17 (GCC ou Clang)
# Créer le répertoire de build
mkdir build
cd build
# Configurer et compiler
cmake ..
make
# Lancer l'application
./sysinfo

## Installation Option 2:
# Installation paquet info-systeme.deb depuis les sources
```bash
sudo dpkg -i info-systeme.deb
```
