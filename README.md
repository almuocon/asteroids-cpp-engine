# Asteroids 2D Engine & Arcade Simulation

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Build System](https://img.shields.io/badge/Build-CMake-064F8C.svg)](https://cmake.org/)
[![Graphics Engine](https://img.shields.io/badge/Graphics-BiGS%20%2F%20Allegro%205-orange.svg)](https://liballeg.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Motor y simulación del clásico juego arcade *Asteroids*, desarrollado en **C++ moderno (C++17)** con cinemática física 2D personalizada, gestión dinámica de memoria de bajo nivel, renderizado gráfico por capas y persistencia de puntuaciones.

---

## 🎓 Contexto Académico

Este proyecto nació originalmente durante el **primer curso del Grado en Ingeniería Informática** en la **Universidad de Granada (UGR)**, dentro del marco de la asignatura *Metodología de la Programación*, con la orientación del profesorado del **Departamento de Ciencias de la Computación e Inteligencia Artificial (DECSAI)**.

---

## 🛠️ Aspectos Técnicos y Decisiones de Ingeniería

* **Cinemática Vectorial Desacoplada:** Simulación newtoniana de inercia espacial en gravedad cero. La rotación angular se desacopla del vector de velocidad lineal para permitir maniobras clásicas de empuje, desaceleración por arrastre (*drag*) progresivo y freno retrógrado activo.
* **Gestión Dinámica de Memoria:** Implementación de estructuras de datos lineales propias (`ListaParticulas`, gestión de arrays dinámicos en `Clasificacion`) asegurando liberación limpia de memoria (RAII) sin fugas (*memory leaks*).
* **Colisiones y Conservación de Momento:** Detección de colisiones radiales continuas, transferencia de momento lineal en rebotes elásticos y fragmentación de asteroides en cuerpos menores conservando velocidades vectoriales ortogonales.
* **Pipeline Gráfico (BiGS / Allegro 5):** Renderizado acelerado por hardware en modo diferido (*double buffering*), soporte de canal alfa para sprites PNG transparentes, escalado dinámico relativo a radios de colisión y rotación en tiempo real.
* **HUD y Máquina de Estados:** Bucle de eventos no bloqueante con cálculo de delta-time ($\Delta t$) para asegurar velocidad de juego independiente de la tasa de refresco, panel semitransparente de métricas en vivo (piloto, puntuación y munición) y estados de victoria/derrota.
* **Persistencia del Leaderboard:** Módulo desacoplado de clasificación que serializa y recupera datos en almacenamiento persistente mediante algoritmos de ordenación en memoria ($O(N \log N)$).

---

## 📁 Estructura del Proyecto

```text
asteroids-cpp-engine/
├── CMakeLists.txt         # Configuración de compilación y empaquetado de assets
├── asteroides.cpp         # Bucle principal, HUD y controlador de estados
├── particula.h/.cpp       # Entidad cinemática base (física, dibujo y colisión)
├── Vector2D.h/.cpp        # Álgebra vectorial 2D (coordenadas cartesianas/polares)
├── listaparticulas.h/.cpp # Contenedor dinámico para gestión del ciclo de vida
├── clasificacion.h/.cpp   # Lógica de ranking, ordenación y persistencia
├── matematicas.h/.cpp     # Funciones auxiliares y conversión numérica
├── assets/                # Sprites PNG (nave, asteroides, fondo)
└── bigs-linux/            # Biblioteca gráfica BiGS (DECSAI - UGR)
```

---

## 🚀 Compilación y Ejecución

### Requisitos previos
En distribuciones basadas en Debian/Ubuntu:
```bash
sudo apt update
sudo apt install build-essential cmake liballegro5-dev
```

### Compilación
```bash
# 1. Clonar el repositorio
git clone [https://github.com/almuocon/asteroids-cpp-engine.git](https://github.com/almuocon/asteroids-cpp-engine.git)
cd asteroids-cpp-engine

# 2. Generar build con CMake
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

### Ejecución
```bash
./asteroides -num [num] -disparos [num] -jugador [tu nombre] -ranking ranking.txt
```

#### Argumentos de línea de comandos:
* `-num <int>`: Cantidad de asteroides iniciales en el campo.
* `-disparos <int>`: Límite de proyectiles simultáneos permitidos en pantalla.
* `-tvida <double>`: Tiempo de vida (en segundos) de cada disparo.
* `-jugador <string>`: Identificador del piloto para registrar en la tabla de clasificación.
* `-ranking <ruta>`: Archivo de texto para persistencia de puntuaciones.

#### Controles:
* **$\uparrow$ (Flecha Arriba):** Impulso / Aceleración lineal.
* **$\downarrow$ (Flecha Abajo):** Retro-propulsor / Frenado activo.
* **$\leftarrow$ / $\rightarrow$ (Flechas):** Giro / Orientación angular de la nave.
* **Espacio:** Disparo de proyectiles.
* **Tecla B:** Alternar entre modo rebote elástico en bordes y modo paso continuo (*wrap-around*).

---

## 👤 Autor y Agradecimientos

* **Desarrollador:** Almudena O. ([@almuocon](https://github.com/almuocon)) — Estudiante del Grado en Ingeniería Informática en la **Universidad de Granada (ETSIIT - UGR)**.
* **Marco de apoyo:** Proyecto tutorizado originalmente por el Prof. Javier Martínez Baena y el profesorado del **DECSAI (UGR)**.
* **Biblioteca Gráfica:** **BiGS** (Capa gráfica ligera sobre Allegro 5)
