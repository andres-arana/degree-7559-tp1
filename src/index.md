ConcuCalesita                            {#mainpage}
=============

ConcuCalesita es el primer proyecto práctico para la materia 75.59 - Técnicas
de Programación Concurrente I de la carrera de Ingeniería en Informática de la
FIUBA. El mismo consiste en una simulación de una calesita a través de
múltiples procesos intercomunicados a través de diferentes técnicas de IPC en
linux.

Arquitectura de la Solución
---------------------------

La aplicación se divide en varios ejecutables diferentes, cada uno simple y con
una única responsabilidad, que son lanzados desde un proceso controlador,
llamado director. A continuación se listan los procesos y una descripción breve
de cada uno:

* **audit**: Representa el auditor que controla el estado de caja cada cierto
  tiempo.

* **carrousel**: Proceso encargado de gestionar las vueltas en la calesita.

* **cashier**: Representa el cajero que cobra a los niños.

* **child**: Proceso que representa un único niño.

* **director**: Proceso que controla recursos compartidos y dispara todos los
  procesos controladores para iniciar y terminar la simulación.

* **spawner**: Proceso que se encarga de crear los procesos child para cada
  niño.

Para más información acerca de cada uno de estos, ver la documentación de las
funciones main de cada ejecutable.

Por otra parte, hay tres librerías compartidas que son utilizadas por los
ejecutables:


* **util**: Utilidades generales compartidas.

* **syscalls**: Wrappers de system calls primitivas, utilizando excepciones
  para reportar errores y tipos de c++ como std::string.

* **raii**: Objetos que implementan el patrón RAII para los recursos del
  sistema operativo manejados por las system calls de **syscalls**.
