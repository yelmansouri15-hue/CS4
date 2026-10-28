> [!important] Estado de ejecución actualizado — 2026-10-09
> Este documento conserva el mapa amplio del currículo. Para el estado real y las próximas tareas, la fuente de verdad es `CS4_Obsidian_Vault/00_Master/MASTER_RECORD.md`. El curso activo ahora es CS103. CS102 está reestructurado/en pausa; la biblioteca completa de estructuras de datos ya no es obligatoria y sus deadlines antiguos están superseded.

# Resumen Ejecutivo  
CS4 es un plan autodidacta de 4 años para cubrir el **núcleo esencial de Computer Science** paralelo al Grado en Matemáticas. Cada año combina cursos teóricos (por asignatura), práctica de programación (labs y proyectos) y evaluación formal (tests y exámenes). Se alinea con el horario real de la UV para Mátemáticas, integrando asignaturas de Informática e ideas de las asignaturas de Matemáticas (análisis, álgebra, estadística). El plan incluye un calendario anual/mensual con deadlines concretos (uso “semana 0 = inicio de semestre”), plantillas semanales de carga de estudio, un riguroso sistema de evaluación (prácticas, parciales, proyectos finales, criba de recuperación), 3–5 proyectos “capstone” con entregas y rúbricas, un **roadmap** para igualar un grado de CS (topics y horas estimadas), plan detallado tras completar CS50 (curso CS101), integración con clases UV, estrategia de hackathons/eventos (fuentes españolas e internacionales), recomendaciones de prácticas y open-source (con guías de contribución), sugerencias de bootcamps intensivos de verano y mecanismos de prevención de burn‐out. Incluye **tablas comparativas** (asignaturas vs horas) y un **cronograma mermaid**. Se adjunta un DOCX/PDF con tabla de contenidos, plantillas y checklist semanal.

## 1. Currículum CS4 (4 años)  
Se propone un currículo paralelo, equivalente al tronco común de un Grado en CS, organizado por años y semestres. A cada asignatura le corresponden unos recursos principales (libros/ocw), objetivos de aprendizaje y prerrequisitos:

- **Año 1 (Fundamentos)** – *30–32 semanas totales (2 semestres)*  
  - **CS101: Programación y Pensamiento Computacional (CS50)** – Introducción (C, Python, SQL, HTML/CSS, JS) y lógica de programación. Objetivos: programar en C, manejar memoria, punteros, estructuras, debugging, razonamiento algorítmico. *Prerequisito:* ninguno. **Recursos:** [CS50x Harvard], libro *“C Programming Language”* (K&R) para C; *Python Crash Course* (Zelle) para Python.
  - **CS102: Estructuras de Datos** – Arreglos, listas enlazadas, pilas, colas, tablas hash, árboles (BST, AVL, rojo-negro), montículos, grafos, recorridos (DFS/BFS). *Prerequisito:* CS101. **Recursos:** *Open Data Structures* (Pat Morin), [CLRS Algoritmos (cap. de estructuras)] en MIT OCW.
  - **CS103: Matemáticas Discretas para CS** – Lógica proposicional y de predicados; técnicas de demostración e inducción; combinatoria básica; grafos; relaciones y funciones; recurrences y probabilidad discreta. *Prerequisito:* Matemáticas Básicas del Grado. **Recursos:** Apuntes de *Matemática Discreta*, *Concrete Mathematics* (Knuth) o material gratuito.
  - **CS104: Sistemas y Computadores I** – Representación binaria, enteros en C, aritmética en punto flotante, arquitectura básica de CPU/memoria, modelo de Von Neumann, punteros y stack, enlazado de código, caché. *Prerequisito:* CS101, algún álgebra lineal básico. **Recursos:** *Computer Systems: A Programmer’s Perspective* (Bryant&O’Hallaron) o similar; [MIT 6.004 Computation Structures (arkitipos)].

- **Año 2 (Core CS)** – *30–32 sem.*  
  - **CS201: Algoritmos y Análisis** – Complejidad asintótica, ordenación, búsquedas, divide y vencerás, DP, greedy, hashing amortizado, árboles (segment trees, Fenwick), grafos (caminos mínimos, MST). *Prereq:* CS102, Matemática Discreta. **Recursos:** [MIT 6.006 OCW], CLRS, *Algorithm Design Manual* (Skiena).
  - **CS202: Arquitectura de Computadores** – Diseño de CPU (ISA, pipelining, superscalar); jerarquía de memoria (caches, memoria virtual); paralelismo a nivel de instrucción; introducción a GPU y concurrencia hardware. *Prereq:* CS104. **Recursos:** [MIT 6.823 OCW (Computer Architecture)], *Computer Organization and Design* (Patterson&Hennessy).
  - **CS203: Sistemas Operativos** – Procesos/threads, scheduling, sincronización, memoria virtual, sistemas de archivos, llamadas al sistema, I/O. *Prereq:* CS104. **Recursos:** *Operating Systems: Three Easy Pieces* (Arpaci-Dusseau), [MIT 6.828 OCW].
  - **CS204: Bases de Datos** – Modelo relacional, SQL, índices, normalización, transacciones ACID, concurrencia, diseño de esquemas, fundamental de NoSQL. *Prereq:* CS102. **Recursos:** [MIT 6.830 OCW (Database Systems)], *Database System Concepts* (Silberschatz et al.).
  - **CS205: Redes** – TCP/IP, UDP, capa de aplicación (HTTP, DNS), sockets, seguridad de red básica, arquitectura cliente-servidor. *Prereq:* CS104. **Recursos:** *Computer Networking* (Tanenbaum) o online “CS144 Stanford Lecture”, prácticas de sockets (Python/C).

- **Año 3 (Ingeniería y Teoría)** – *30–32 sem.*  
  - **CS301: Ingeniería de Software** – Diseño de software (modularidad, patrones de diseño), control de versiones, testing (unitario, integración), CI/CD, análisis de requisitos, revisión de código, refactoring. *Prereq:* CS201. **Recursos:** [MIT 6.033 (Computer System Engineering)], *Design Patterns* (GoF), *Clean Code* (Martin).
  - **CS302: Teoría de la Computación** – Autómatas finitos, gramáticas, máquinas de Turing, decidibilidad, NP-completitud, reducciones. *Prereq:* CS103. **Recursos:** *Introduction to the Theory of Computation* (Sipser) o notes de MIT 6.045.
  - **CS303: Lenguajes de Programación** – Paradigmas (procedural, funcional, orientado a objetos), sistemas de tipos, compiladores/interpretes básicos, garbage collection. *Prereq:* CS101, CS102. **Recursos:** [MIT 6.035 (Computer Language Engineering)], *Crafting Interpreters* (book).
  - **CS304: Sistemas Distribuidos** – Replicación, consistencia, consenso (Paxos/Raft), escalabilidad, tolerancia a fallos. *Prereq:* CS202, CS203. **Recursos:** *Distributed Systems* (Tanenbaum & van Steen), [MIT 6.824 OCW (Distributed Systems)].
  - **CS305: Seguridad Informática** – Criptografía básica, autenticación, vulnerabilidades comunes (XSS, buffer overflows), seguridad de redes. *Prereq:* CS203. **Recursos:** [MIT 6.858 OCW (Computer Systems Security)], *Computer Security* (Goodrich/Cyr).

- **Año 4 (Avanzados y Especialización)** – *30–32 sem.*  
  En función de interés (IA/ML, gráficos, sistemas avanzados, etc.). Ejemplos:  
  - **ML/IA:** Aprendizaje automático (Regresión, clasificación, DL, RL). Prerreq: Álgebra lineal, Estadística. Recursos: *Machine Learning* (Andrew Ng), [MIT 6.036 OCW].  
  - **Gráficos:** Álgebra lineal avanzada, geometría computacional, rendering (GPU, shaders, ray-tracing). Recursos: *Real-Time Rendering* (Akenine-Möller), [UdeSA CG course OCW].  
  - **Videojuegos:** C++ avanzado, motores (Unreal/Unity), física. Recursos: documentación de Unity/Unreal, [Carnegie Mellon GameDev courses].  
  - **Computación Científica:** Métodos numéricos, HPC, simulación. Recursos: *Numerical Recipes*, cursos HPC.  
  - **II Simpáticas:** Optativa de CS, proyectos de fin de carrera.  

> **Tabla comparativa cursos (horas semanales aprox.)**:

| Asignatura              | Horas/sem (clases+estudio) | Pre-rec.        | Recursos clave (OCW/LIBRO)                        |
|:------------------------|:-------------------------:|:---------------:|:-------------------------------------------------|
| CS101 (CS50)            | 8                         | –               | CS50 Harvard (C, Python, SQL)      |
| CS102 (Data Structures) | 6                         | CS101           | *Open Data Structures*, CLRS                      |
| CS103 (Discreta)        | 4                         | –               | Apuntes UV, *Concrete Mathematics*                |
| CS104 (Sistemas I)      | 6                         | CS101           | *CS:APP* (Bryant/O’Hallaron), [MIT OS/arch]       |
| **Año 1 total**         | ≈24 h/sem                 |                 |                                                   |
| CS201 (Algoritmos)      | 8                         | CS102, Discreta | [MIT 6.006 Algoritmos], CLRS       |
| CS202 (Arquitectura)    | 6                         | CS104           | [MIT 6.823 Arquitectura]           |
| CS203 (Sist. Oper.)     | 6                         | CS104           | [MIT 6.828 OS]                     |
| CS204 (Bases de datos)  | 5                         | CS102           | [MIT 6.830 BD]                     |
| CS205 (Redes)           | 5                         | CS104           | Tanenbaum (redes)                                  |
| **Año 2 total**         | ≈30 h/sem                 |                 |                                                   |
| CS301 (Ing. SW)         | 5                         | CS201           | [MIT 6.033 SW Eng]                 |
| CS302 (Teoría)          | 4                         | CS103           | *Sipser (Teoría Comput.)*                          |
| CS303 (Leng. Prog.)     | 5                         | CS101           | *Crafting Interpreters*, [MIT 6.035]               |
| CS304 (Distrib.)        | 5                         | CS202,CS203     | *Tanenbaum Distrib.*, [MIT 6.824]                 |
| CS305 (Seguridad)       | 5                         | CS203           | [MIT 6.858 Seguridad], *Goodrich/Cyr.*            |
| **Año 3 total**         | ≈24 h/sem                 |                 |                                                   |
| CS4xx (Especialización) | 20–30 h                  | Varios          | Depende del área (p.ej. *DL libro*, *CG libro*)     |
| **Año 4 total**         | ≈20–30 h sem             |                 |                                                   |

*Notas:* Las horas estimadas incluyen clases y estudio personal. Las referencias indican recursos clave. Este plan asegura que al final CS4 el estudiante habrá cubierto los temas básicos de un graduado en CS (por ejemplo, el MIT OCW 6.006 cubre algoritmos básicos, 6.033 cubre ingeniería de software, 6.828 OS, 6.823 arquitectura, 6.830 BD). Matemáticas sólidas (Álgebra, Cálculo, Estadística) proporcionan una ventaja en IA/ML, criptografía, gráficos, etc.

## 2. Calendario Operativo Año 1 (2026–27)  
Se asume semestre de otoño ~14 sep 2026 – 16 dic 2026 (12 sem.), y primavera ~10 ene 2027 – fin mayo 2027 (12 sem.), con semana 0 al inicio. Se articulará así el **primer semestre** (Año 1):

- **Sem. 0 (13–17 sept):** Presentación del Grado (orientación). Inicio lecturas intro de CS50.
- **Sem. 1–6:** *CS101 (CS50)* – completar las **Weeks 0–5** de CS50 (C, primeros algoritmos, structures). Programación: 8h/sem, incluyendo lab y problemas. Además: asistir a clases de Informática UV (34159) los martes y jueves mañanas.
- **Sem. 7:** *Parcial Matemáticas* (Análisis I primer parcial ~día 14 dic). Planear semana de recuperación (CS4 reducido).
- **Sem. 8–11:** *CS102: Estructuras de Datos* – preparar parciales con ejercicios semanales (listas, árboles). Continua CS50: completar Weeks 6–10 (Python, web).
- **Semana 10 (6 dic):** Entrega **Proyecto CS101** (un pequeño intérprete o mini-app en C/Python).  
- **Semana 12:** **Exámenes UVA** de fin de semestre (Análisis, Álgebra). *Carga UV alta*; CS4  solo repasos leves (1–2h).  
- **Semana 13 (ene 2027):** Examen Final CS101 (2h, propuesto antes de vacaciones). ¡Fin sem1! De ahora en adelante, cargas intensivas según nuevos cursos (CS102, etc.).
- **Primavera 2027:** paralelamente cursar CS102, CS104, CS103 según secuencia del año 1. Parciales de CS102 (mes marzo) y finales en mayo.

> **Fechas clave (relativas):** CS50 finaliza ~semana 11. *Proyecto CS101*: entre sem. 10–12. *Examen Final CS101*: sem. 13. *Parciales Mat1*: sem. 7. *Examen Final Mat1*: sem. 13. *Parciales CS102*: ~sem. 20. *Trabajo Fin Año (CS102/CS104)*: mayo 2027.  

### Calendario Semanal  
Según el horario real UV, las clases ocupan **Lunes–Viernes 8:30–13:00** (alguna sesión de 13:00–14:30). Un ejemplo de **programación semanal** en sem. normal sería:

| Día      | Universidad            | Estudio Matemáticas | CS4 (Programación) |
|:---------|:-----------------------|:--------------------|:-------------------|
| Lunes    | 8:30–13:00 clases      | 15:00–17:00 repaso/Mates | 17:30–19:30 (CS50) |
| Martes   | 8:30–13:00 clases      | 14:30–16:30 repaso   | 17:00–19:00 (CS50) |
| Miércoles| 8:30–13:00 clases      | 15:00–17:00 repaso   | 17:30–19:30 (CS50) |
| Jueves   | 8:30–13:00 clases      | 14:30–16:30 repaso   | 17:00–19:00 (CS102 lecturas) |
| Viernes  | 8:30–13:00 clases      | 14:30–16:30 repaso   |  *Libre/extra práctica*   |
| Sábado   | —                      | 10:00–12:00 repaso   | 12:30–14:30 (CS50 contest/lab) |
| Domingo  | **DESCANSO**           | Organización semanal |  *Descanso*         |

- **Carga normal:** ~8h semanales de CS4 (después de 17h), 18–22h Matemáticas fuera de clases.  
- **Sem. intensa (parciales/entregas):** reducir CS4 a 4–5h (solo práctica mínima).  
- **Sem. de exámenes (UV):** CS4 ~1–2h (repaso muy básico).  
- **Semana ligera / vacaciones:** CS4 10–12h posibles (avance o proyectos).  
- El **domingo** debe reservarse para descanso, deporte u ocio.

## 3. Sistema de Evaluación CS4  
Cada asignatura CS4 se evalúa como en la universidad: **Problem Sets (20–30%)**, **Parcial(es) (25–30%)**, **Proyecto práctico (20%)** y **Examen Final (25–30%)**. Ejemplo de rúbrica:

- **Problem Sets:** ejercicios cortos semanales o quincenales. *Objetivo:* garantizar dominio de cada tema (al menos 80% de corrección).   
- **Examen Parcial:** 1–1.5 h, preguntas teóricas + problemas, tipo “¿Por qué funciona este algoritmo? *¿Cuál es su complejidad?*”, sin ayuda externa. (Semana media de cada curso).  
- **Proyecto:** p.ej. implementación de un componente (p. ej. árbol binario balanceado, servidor, compilador mini). **Entregables:** diseño, código, documentación. *Criterios:* funcionalidad, eficiencia, calidad de código, claridad de documentación.  
- **Examen Final:** 2.5–4 h, formato similar a parcial pero integrando varios temas. Incluye **una pregunta de diseño global** (“Diseña un sistema que…”) que integre materia de la asignatura y evalúe capacidad de arquitectura.   
- **Nota:** Escala 0–10 (≥5 aprobado). Sin compensación de notas: si un examen clave queda <5, repetir materia completa. Buscamos no solo aprobar sino dominio: apuntar a ≥7–8.

**Ejemplos de criterios:**  
- *Pasar:* ≥5 en examen final y promedio de PS/Parcial ≥6.  
- *Excelente:* ≥9 en proyecto y ≥8 final.  
- **Examen oral:** ocasionalmente se hará revisión oral (“explica este algoritmo/¿qué pasaría si…?”) para asegurar comprensión profunda, al estilo entrevista.  
- **Calificaciones:** registrar en un expediente CS4 paralelo. Por ejemplo:

  > **CS4 – Año 1, Semestre 1**  
  > – CS101 Programación: 8.4 (Proy 8.5, Parcial 8.0, Final 8.2)  
  > – CS102 Estructuras: 7.9 (… )  
  > *(media ponderada…)*  
  > **CS4 GPA:** 8.1

Esto servirá de referencia en entrevistas (no es oficial UV).  

## 4. Proyectos Capstone  
Para demostrar habilidades, se planifican **3–5 proyectos grandes** distribuidos en los años. Ejemplos:  

- **Proyecto 1 (Año 1):** *Intérprete/Maquina Virtual Simple* en C. Objetivo: integrar conocimientos de CS101 y CS104. *Entregables:* código comentado, manual breve, demo de ejecución.  
- **Proyecto 2 (Año 2):** *Sistema de Base de Datos Simple* (p.ej. gestor de pequeños registros en Python o C++). Incluye esquema SQL (CS204), implementa transacciones básicas. *Criterios:* diseño de tablas, manejo de índices, concurrencia simulada.  
- **Proyecto 3 (Año 3):** *Aplicación Distribuida* (p.ej. chat o juego multiusuario). Combina redes (sockets), concurrencia, arquitectura cliente-servidor (CS301), integración. *Rúbrica:* modularidad, escalabilidad, pruebas.  
- **Proyecto 4 (Especialización):** Según interés: p.ej. *Motor Gráfico* básico en C++/OpenGL (CS202/Gráficos), o *Pipeline de ML* (Python con TensorFlow, CSML). Debe ser original y documentado.  
- **Proyecto Final (Año 4):** un proyecto amplio integrador: p.ej. juego completo, aplicación web compleja, o contribución importante a open-source. *Entregables:* reporte técnico, presentación.  

Cada proyecto tiene **milestones** (propuesta, prototipo, versión final) con fecha límite. Se evaluará *funcionalidad completa, calidad de diseño* (p. ej. uso correcto de estructuras), documentación clara (README, comentarios) y pruebas de uso. Por ejemplo, el proyecto 1 debe resolver ejemplos de prueba y entregar un “manual de usuario” de cómo compilar/ejecutar. Las rúbricas serán similares a las de software engineering universitario (p. ej. las de ACM ICPC o cursos MIT 6.033).

## 5. Roadmap a Paridad con un Graduado en CS  
Para equipararse a un graduado fuerte en CS, se deben cubrir unos **1.500–2.000 horas** de estudio/práctica (estimación). El **roadmap** sugerido (aparte de los cursos arriba) incluye:

- **Programación básica:** 200–300 h (lenguajes C, C++, Python; estructuras).  
- **Algoritmos/Estructuras:** 300 h (implementar y analizar múltiples algoritmos).  
- **Sistemas/Arquitectura:** 200 h (prácticas en Linux, VPS, entender CPU).  
- **Bases de Datos/Redes:** 150 h (SQL labs, aplicaciones cliente-servidor).  
- **Software Eng.:** 200 h (proyectos en equipo, git, testing).  
- **Matemáticas para CS:** 150 h (LP, combinatoria, estadística aplicada).  
- **Especialización:** 300–400 h (p.ej. IA/Gráficos/Ciencia de datos).  

Estos se adquieren realizando cursos MOOCs o libros avanzados **en orden lógico** (ver punto 7). Una referencia de paridad: “72% empresas equiparan bootcamp a grado” indica que el fondo académico importa, pero al final cuentan los *proyectos reales* y la base de conocimientos. La “Regla de los 5 años” dice que tras 5 años en industria, importa menos la titulación y más el historial técnico, por lo que lo esencial ahora es aprender a fondo y documentarlo con credenciales (certificados de cursos, GitHub activo, CV de proyectos).

## 6. Plan de Estudio tras CS50 (CS101)  
Partiendo de CS50 (CS101), el siguiente orden recomendado es: 

1. **Algoritmos (CS201):** MIT OCW 6.006 (introducción). Quizzes semanales y un parcial. *Tarea inmediata:* resolver quizzes del MIT y problemas CLRS de sorting y DP.  
2. **Arquitectura (CS202):** en paralelo empezar MIT 6.823 o notas: comprender pipelining y cachés.  
3. **Sistemas Operativos (CS203):** seguir con OSTEP (lectura de capítulos), implementar pequeñas réplicas de scheduler o malloc.  
4. **Estructuras de Datos (CS102):** terminar implementación de estructuras (lib personal). Entregar *parcial* en sem. de exámenes.  
5. **Bases de Datos (CS204):** aprender SQL/NoSQL, diseñar y montar base de datos MySQL/PostgreSQL.  
6. **Ingeniería Software (CS301):** aplicar git/GitHub, CI (GitHub Actions), escribir tests. Seguir proyectos colaborativos de GitHub para code review.

Cada 4–6 semanas evaluar avance mediante autoexamen o con un “parcial casero” (p.ej. usar problemas reales de examen MIT 6.006, UVA, etc.). Prioridad: fundaciones (C/C++ y memoria, luego algoritmos) antes de frameworks o tecnologías de moda. 

**Checklist para las próximas 8 semanas (situación actual: completado CS50 W0-1, parcial W2 listo):**  
- **Semana 1 (Hoy–Sem1):** Terminar CS50 Week2 (e.g. algoritmo search, punteros).  
- **Semana 2:** Completar CS50 Week3 (estructuras dinámicas); empezar lectura MIT 6.006, ver Lectura 1 sobre comparaciones y ordenación.  
- **Semana 3:** CS50 Week4; practicar C (leer *K&R*, ejercicios punteros). Revisar apuntes de Álgebra Lineal (Aplica vectores en CG/ML).  
- **Semana 4:** Finalizar CS50 (Weeks5-6); comenzar implementaciones en C (p.ej. lista enlazada propia).  
- **Semana 5:** Iniciar CS102: hashing y árboles, ejercicios de *Open Data Structures*. Realizar quiz MIT 6.006.  
- **Semana 6:** CS102: pila/cola/heap; programa un heap binario; leer *APL 8.0*.  
- **Semana 7:** Preparar mini-parcial “CS101” (repasar todo C aprendido, resolver problemas sin ayuda, cronométrate 2h).  
- **Semana 8:** Proyecto CS101: bosquejar diseño, iniciar implementación; apuntar a tener proto alpha (mínimo funcional) al final de la semana.  

Estas tareas semanales *deben gestionarse junto con el estudio formal de Matemáticas (que es prioridad en su horario)*. Siempre hay que priorizar descansos adecuados y adaptar el plan si surgen dificultades.  

## 7. Integración con las clases de la UV  
Para aprovechar sinergias:  
- La asignatura **Informática (34159)** del primer curso UV enseña fundamentos de programación (bloques, estructuras). Hay que aplicar ese aprendizaje al CS101 (e.g. usar C, estructuras propias). Aprovechar los labs de Informática para practicar Git o Python.  
- **Álgebra Lineal** (ALG I) soporta gráficos, ML. P.ej. vectores/espacios de matrices vistos en cálculo serán útiles en álgebra lineal computacional (CG/ML).  
- **Análisis Matemático** y **Probabilidad/Estadística**: utilizar análisis para entender algoritmos numéricos, y estadísticas para ML (si se elige IA).  
- En proyectos multidisciplinares (p.ej. reto de Data Science en hackathon), tus conocimientos de Estadística UV serán valor added.  

No se “descartan” clases UV; se vinculan. Por ejemplo, un ejercicio de la asignatura de Álgebra (taller práctico) puede ampliarse como mini-proyecto CS (p.ej. script en Python que resuelva problema lineal con GUI).

## 8. Cronograma (Mermaid) – Año 1 (Vista General)  
```mermaid
gantt
    title Cronograma CS4 – Primer año (2026-27)
    dateFormat  YYYY-MM-DD
    %% Semestre Otoño
    section CS4 Programaci\u00f3n
    CS50 (CS101)           :done, 2026-09-01, 2026-11-30
    Proyecto CS101         :milestone, 2026-12-10, 2026-12-15
    Examen Final CS101     :milestone, 2027-01-10, 1d
    section Matem\u00e1ticas
    Parciales \u00c1n\u00e1lisis :milestone, 2026-12-05, 2026-12-05
    Examen Final \u00c1n\u00e1lisis: 2027-01-15, 5d
    section Eventos & Extras
    Hackathon Gand\u00eda      :milestone, 2026-11-15, 2026-11-17
    Semana Blanca UV         :milestone, 2026-12-20, 2026-12-24
  ```
*Nota:* Las fechas son orientativas; “2026-09-01” se toma como semana 0 (inicio septiembre 2026). El diagrama sintetiza: CS50 de sept a fines-nov, proyecto en dic, final en enero. Los exámenes UVA coinciden con picos de semestre (navidad/verano).  

## 9. Plan de Hackathons y Eventos  
**Participar en hackathons** compensa la falta de “networking académico”. Fuentes y estrategias:  

- **Hackathons locales:** Estar atento a eventos universitarios valencianos. Ejemplo: *Campus Salud Gandía* (hackathon universitario de salud) que en 2026 reunió estudiantes de distintas carreras (Gandía, UPV). Seguir redes de la UPV y Facebook/LinkedIn de clubs: suelen anunciar hackatones temáticos (tecnología, social, IoT).  
- **Hackathons globales/online:** Sitios como Devpost o [dev.events📌](https://dev.events/hackathons/EU/ES/Valencia/tech) listan hackathones online (p.ej. hackathons de IA o blockchain accesibles desde València). Ej: hackathons de programación de 1–2 semanas de duración (ver “Tech hackathons in Valencia”). Suscribirse a newsletters como Hackathons.com, GitHub Explore, o Slack de desarrolladores.  
- **Ferias y conferencias:** Aunque no sean hackathons, asistir a eventos tech refuerza networking: e.g. *4 Years From Now (4YFN)* y *MWC Barcelona* (febrero-marzo); *Codemotion Madrid* (abril); meetups de IA/Cyber/BlockChain. Mantén calendario (si es necesario via Google Calendar) con tiempos de inscripción.  
- **Presupuesto:** Muchos hackathons son gratuitos o con becas. Guardar unos €500/año para viajes a 1-2 hackathons fuera de Valencia (e.g. Madrid, Barcelona) durante las vacaciones de Navidad o Semana Santa, que suelen tener intensivos de 48–72h. Planificar con ~2–3 meses de antelación (a mayo/septiembre busca incripciones otoño/invierno).  
- **Objetivos en Hackathons:** Al inicio, enfócate en *equipos* y aprendizaje colaborativo (no en ganar). Luego, en especializarte tecnológicamente (p.ej. IA, juegos). Documenta cada hackathon (proyecto hecho, link GitHub, contacto equipo). Puede abrir puertas a prácticas o becas, y obtener recomendaciones profesionales informales.

## 10. Prácticas, Open Source y Networking  
- **Prácticas (Internships):** Aplicar a programas de prácticas de empresas tecnológicas. En Valencia/ES destacan: Everis/TCS, Indra, Amazon (Castellón), Google Summer of Code (global), Microsoft, startups locales (p.ej. Lingokids, HP, Penteo). El portal de empleo del campus y LinkedIn son claves. Prepara CV orientado a software engineering (menciona GPA CS4 como “formación autodidacta” con notas virtuales).  
- **Contribución Open Source:** Participar en proyectos open source mejora visibilidad. Por ejemplo, contribuir con bugs de Python, proyectos educativos de GitHub, librerías. Las guías de iniciación al open source recomiendan empezar corrigiendo documentación o issues pequeños. Citar: *“Contribuir en proyectos de código abierto puede ser una provechosa manera de aprender… y conseguir experiencia en cualquier habilidad”*. En tu CV, incluir repositorios propios y PR aceptadas. Usar GitHub como portafolio vivo.  
- **Networking:** Usa LinkedIn/GitHub para conectar con otros devs; participa en meetups (València Tech Meetup, Python Valencia). Sube tu proyecto grande final a GitHub y dilo en foros (r/programming, StackOverflow). Busca mentores: por ejemplo, profesores UV o egresados en software.  

## 11. Planes de Verano y Bootcamps  
- **Verano 2027:** Programa intensivo de aprendizaje. Opciones:  
  - **Bootcamp de Programación:** Un bootcamp de 3–6 meses (p.ej. Archi’s Academy, Ironhack, Le Wagon) puede profundizar en stack web o datos. Según encuestas recientes, ~79% de graduados de bootcamps logran empleo tech. Evaluar opciones gratuitas (becas públicas) antes de invertir miles de euros.  
  - **Cursos Online Intensivos:** e.g. curso de Data Science en Coursera/edX (10-12 semanas), intensivo de redes (Cisco Packet Tracer), MOOC CS de MIT en 1 mes.  
  - **Verano en el extranjero:** Aplicar a Summer Schools de CS (p.ej. en universidades europeas) o intercambio Erasmus de investigación en CS.  
- **Bootcamps (curso prep):** Si se decide, asegúrese de que el bootcamp exige crear proyectos propios (no solo replicar tutoriales). El blog de Archi’s Academy advierte que muchos bootcamps fallan en simular proyectos reales; buscamos uno con mentorías reales y revisión de código.  

## 12. Gestión de Riesgos (Burnout, Contingencia)  
- **Prevención Burnout:** No más de ~8–10h diarias combinadas. Seguir los bloques de horario semanales con descansos. Semana de descanso tras parciales fuertes (sem. intensas UV).  
- **Semanas de recuperación:** Tras cada parcial/entrega UV, bajar CS4 a mínimo, y luego “recuperar” subiendo el ritmo (sem. ligera).  
- **Cortafuegos:** Mantener hobbies (deporte, amigos, familia) para desconectar. Aprender a decir “no” a tareas CS4 extras si el UV aprueba en riesgo.  
- **Plan B:** Si un curso autoevaluado resulta muy difícil (p.ej. OS o arquitectura), considerar inscribirse en clases online MOOC o incluso en segundo año hacer un **Minor o Grado de CS part-time** (alguna uni online) mientras continúas Matemáticas. Tu formación matemática no se pierde; siempre puedes volver a reforzar CS4 más tarde.  
- **Consulta continua:** Pedir feedback cada mes (“¿Estoy atrasado en CS4?”). Ajustar el calendario si no se cumplen hitos. Mejor reposicionarse temprano que quemarse intentando cubrirlo todo.

## 13. Descargas y Plantillas Adjuntas  
Se ha generado un documento **CS4_Plan_Computer_Science_Paralelo_4_Años** con este contenido, listo para descargar: contiene índice, tablas (comparación asignaturas, carga horaria), un calendario editable (plantilla mensual/diaria) y checklists.  

- [🔗 Descargar CS4_Plan.docx (Word)](sandbox:/mnt/data/CS4_Plan_Computer_Science_Paralelo_4_Anos.docx)  
- [🔗 Descargar CS4_Plan.pdf (PDF)](sandbox:/mnt/data/CS4_Plan_Computer_Science_Paralelo_4_Anos.pdf)  

*(Estos archivos incluyen el plan completo, calendario semestral/semana, rúbricas de evaluación y plantillas de seguimiento).*  

## Referencias  
- [CS50 Harvard (introducción CS)]  
- [MIT 6.006 (Algoritmos)]  
- [MIT 6.033 (Ingeniería SW)]  
- [MIT 6.823 (Arquitectura)]  
- [MIT 6.828 (Sistemas Operativos)]  
- [MIT 6.830 (Bases de Datos)]  
- UV Horarios Grado Matemáticas  
- Campus Salud Gandía Hackathon 2026  
- Listado Hackathons dev.events (online)  
- Datos bootcamps 2026 (Archi’s Academy)  
- Guía Contribuir Open Source  

