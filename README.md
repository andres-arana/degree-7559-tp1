# 75.59 - Técnicas de Programación Concurrente I

Este repositorio contiene el primer proyecto práctico realizado en la materia
(75.59) Técnicas de Programación Concurrente I en la FIUBA.

## Introducción

El proyecto consiste en una aplicación de escritorio que corre en modo consola
en entornos UNIX compuesta de varios subprocesos intercomunicados para simular
un escenario en el que varios niños utilizan una calesita.

## Desarrollo

### Estructura del repositorio

El repositorio está organizado en el siguiente árbol de directorios:

* `docs`: Contiene los fuentes del informe que acompaña la entrega y el
  enunciado.

* `src`: Contiene el código fuente de toda la solución

    * `src/audit`: Contiene el código fuente del ejecutable audit.

    * `src/carrousel`: Contiene el código fuente del ejecutable carrousel.

    * `src/cashier`: Contiene el código fuente del ejecutable cashier.

    * `src/child`: Contiene el código fuente del ejecutable child.

    * `src/director`: Contiene el código fuente del ejecutable director.

    * `src/spawner`: Contiene el código fuente del ejecutable spawner.

-   `src/util`: Contiene el código fuente de la librería compartida entre todos
    los procesos.

-   `build`: Directorio temporal que contiene los resultados de lo generado a
    través del makefile. Se genera automáticamente según sea requerido por el
    makefile al correr ciertas tareas, y no se incluye por default.

### Makefile

El proyecto incluye un makefile con varios targets para realizar todo tipo de
tareas relacionadas. Toda salida de dichas tareas se realiza dentro del
directorio build, generado automáticamente según sea necesario. Las tareas
están correctamente configuradas para detectar dependencias; no es necesario
correr una tarea como clean antes de hacer el build, o de correr all antes de
run.Las tareas son las siguientes:

* **all**: Compila todos los ejecutables de cada proceso del proyecto
  generándolos en la carpeta `build/exec`.

* **run**: Ejecuta el `director`, proceso principal que dirige la simulación.

* **doc**: Genera el PDF del informe que acompaña la entrega en `build/doc`.

* **doc-preview**: Visualiza el PDF del informe utilizando evince.

* **doc-spell**: Utiliza aspell para chequear errores de spelling en el
  informe.

* **srcdoc**: Genera la documentación anotada del código fuente con doxygen.

* **srcdoc-preview**: Visualiza la documentación del código fuente utilizando
  firefox.

* **clean**: Elimina cualquier artefacto generado por el sistema de build.

### Arquitectura

Para más información sobre la arquitectura de la solución, correr `make
srcdoc-preview`. El código fuente está ampliamente documentado y la
documentación generada por doxygen incluye varias páginas adicionales
introductorias al proyecto.
