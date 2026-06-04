
## 📁 Structure du projet
code_source/
├── main.cpp                  # Point d'entrée
├── FenetrePrincipale.h       # Déclaration de la fenêtre principale
├── FenetrePrincipale.cpp     # Logique de la fenêtre principale
├── FenetrePrincipale.ui      # Interface Qt Designer
├── SystemInfo.h/.cpp         # Classe de récupération des infos système
└── CMakeLists.txt            # Configuration CMake

## Option 1:
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

### Option 2:
# Installation paquet info-systeme.deb depuis les sources
```bash
sudo dpkg -i info-systeme.deb
```
