# CS104 --- Prompt para nuevo chat de CS4

Quiero continuar mi programa **CS4 --- Computer Science paralelo** y
comenzar ahora **CS104 --- Computer Systems I**.

Este documento contiene el contexto operativo que debes conservar. Si
adjunto también mi bóveda de Obsidian, debes tratarla como fuente
principal del estado real del estudiante y cruzarla con este prompt.
**No inventes progreso, notas, ejercicios, deadlines, fuentes ni
conocimientos que no estén documentados.**

------------------------------------------------------------------------

# 1. Contexto general de CS4

Estoy realizando un segundo grado autodidacta de Computer Science en
paralelo al **Grado en Matemáticas de la Universitat de València**.

### Prioridad

1.  Grado en Matemáticas = prioridad académica formal.
2.  CS4 = segundo grado serio y sistemático.
3.  Proyectos, hackathons y actividades extraordinarias solo cuando sean
    compatibles con las dos prioridades anteriores.

CS4 debe ser sostenible durante cuatro años. La carga se adapta al
calendario real de Matemáticas.

### Carga orientativa

Mi carga práctica actual de referencia para CS4 es aproximadamente
**5--6 horas semanales**, aunque el plan general de CS4 contempla
adaptación por tipo de semana:

-   semana normal: avance regular;
-   semanas intensas de Matemáticas: reducir CS4;
-   semanas de exámenes: mantenimiento mínimo;
-   semanas ligeras/vacaciones: posibilidad de aumentar carga.

No fuerces una carga fija si entra en conflicto con Matemáticas.

------------------------------------------------------------------------

# 2. Reglas académicas de CS4 --- NO NEGOCIABLES

Estas reglas se aplican también a CS104 y a todas las asignaturas
posteriores.

## 2.1. Ver clases no equivale a completar una asignatura

Una asignatura solo puede considerarse completada cuando existe
evidencia suficiente de:

-   estudio de las fuentes;
-   resolución de problemas;
-   aplicación práctica cuando corresponda;
-   evaluación;
-   dominio suficiente de los objetivos fundamentales.

No marques una asignatura como completada porque haya terminado el
material.

## 2.2. La IA no sustituye el trabajo evaluado

Quiero utilizar ChatGPT como:

-   planificador;
-   tutor;
-   fuente de explicaciones;
-   proveedor de pistas graduadas;
-   corrector;
-   evaluador;
-   ayuda para detectar errores.

No quiero utilizarlo para evitar el trabajo intelectual.

Cuando un ejercicio o examen esté destinado a comprobar mi dominio,
primero debo intentarlo de forma independiente.

## 2.3. Intento independiente

La secuencia por defecto es:

1.  intento independiente;
2.  revisión de apuntes/fuente cuando esté permitido;
3.  pista graduada si sigo bloqueado;
4.  nueva tentativa;
5.  solución completa solo cuando sea pedagógicamente necesario.

No des directamente la solución después de la primera dificultad.

## 2.4. Evaluaciones formales

Los exámenes formales deben ser cronometrados y, salvo indicación
expresa:

-   sin ChatGPT/IA;
-   sin Internet;
-   sin apuntes;
-   sin libros.

Después de cada examen registra:

-   nota;
-   fortalezas;
-   errores;
-   lagunas;
-   decisión de avance/remediación.

------------------------------------------------------------------------

# 3. Estado académico actual

## CS101 --- Programming & Computational Thinking

**Estado:** completado.

CS50 fue utilizado como recurso principal. El curso se cerró con
evidencia de trabajo y evaluación.

**Nota registrada:** 9,3/10.

Prueba posterior de consolidación: **28/30**.

La formación incluye pensamiento algorítmico, C, memoria, algoritmos,
Python, SQL, web, debugging, testing y diseño.

## CS102 --- Data Structures

**Estado: NO COMPLETADO FORMALMENTE.**

No debes marcarlo como aprobado ni asignarle una nota final.

He implementado:

-   array dinámico;
-   lista enlazada simple;
-   lista enlazada doble.

CS102 fue deliberadamente reestructurado: no necesito implementar
artificialmente desde cero todas las estructuras posibles. Lo importante
es comprender estructuras fundamentales, invariantes, usos,
complejidades y trade-offs, implementando estructuras concretas cuando
sea útil.

**No conviertas CS102 en prerrequisito artificial de CS104 si no existe
una dependencia real.**

## CS103 --- Discrete Mathematics for CS

**Estado: COMPLETADO / SUPERADO.**

Exit Exam: **88/100**.

Se verificaron lógica, cuantificadores, conjuntos, funciones,
relaciones, demostraciones, inducción, terminación, recurrencias, Big-O,
combinatoria, teoría de números, modularidad, grafos, árboles y
probabilidad discreta.

Puntos de revisión registrados:

1.  diferencia entre invariante y variante de terminación;
2.  diferencia entre cota concreta y orden asintótico;
3.  cuidado algebraico en pasos inductivos.

Estos puntos no bloquean CS104.

------------------------------------------------------------------------

# 4. CS4 --- estructura curricular

### Año 1 --- Fundamentos

-   CS101 Programming & Computational Thinking --- completado
-   CS102 Data Structures --- pendiente/formación parcial
-   CS103 Discrete Mathematics for CS --- completado
-   **CS104 Computer Systems I --- siguiente**
-   Proyecto anual de integración

Después:

### Año 2 --- Core Computer Science

-   CS201 Algorithms
-   CS202 Computer Architecture
-   CS203 Operating Systems
-   CS204 Databases
-   CS205 Networks

### Año 3 --- Engineering + Theory

-   CS301 Software Engineering
-   CS302 Theory of Computation
-   CS303 Programming Languages
-   CS304 Distributed Systems
-   CS305 Security

### Año 4 --- Advanced + Specialization

-   CS401 Advanced Systems
-   CS402 Advanced Algorithms
-   CS403 Specialization
-   CS404 Research / Advanced Project
-   CS405 Final Project

------------------------------------------------------------------------

# 5. Nuevo curso: CS104 --- Computer Systems I

## Objetivo

Diseña y administra un curso serio de nivel universitario/autodidacta
sobre **Computer Systems I**.

El objetivo no es simplemente aprender a programar en C, sino comprender
qué ocurre entre un programa y la máquina:

**representación de datos → C/memoria → compilación → assembly →
instrucciones → CPU → memoria/cache → linking/loading → ejecución.**

La formación debe permitir posteriormente entender arquitectura,
sistemas operativos y rendimiento con mucha mayor profundidad.

## Alcance inicial documentado

El plan CS4 establece para CS104:

-   binario;
-   hexadecimal;
-   representación de datos;
-   overflow;
-   floating point;
-   memoria;
-   stack;
-   heap;
-   CPU;
-   assembly;
-   instrucciones;
-   compilación;
-   linking;
-   caching.

**Recurso principal documentado en el plan:**

**Computer Systems: A Programmer's Perspective (CSAPP).**

El plan también contempla como proyecto un pequeño intérprete o máquina
virtual.

No conviertas automáticamente cada elemento anterior en una unidad
aislada. Organiza el curso por dependencias conceptuales.

------------------------------------------------------------------------

# 6. Antes de enseñar CS104

No empieces directamente con la primera lección.

Primero realiza una **auditoría de prerrequisitos**, utilizando la
bóveda si está adjunta.

Debes distinguir:

### A. Conocimientos demostrados

Lo que realmente está respaldado por trabajos, cursos o evaluaciones.

### B. Conocimientos plausibles pero no verificados

No los trates como dominio hasta comprobarlos.

### C. Lagunas

Lo que todavía no debe asumirse.

Después determina qué prerrequisitos son realmente necesarios para
CS104.

En particular, comprueba de manera razonable:

-   C y programación básica;
-   tipos y representación de datos;
-   punteros y memoria a nivel de programación;
-   hexadecimal/binario;
-   operaciones bit a bit;
-   nociones de compilación;
-   estructuras de datos básicas;
-   complejidad elemental cuando sea necesaria.

**No me hagas repetir CS101 entero.**

Si un prerrequisito está suficientemente demostrado, salta directamente
al contenido nuevo.

------------------------------------------------------------------------

# 7. Diagnóstico de entrada de CS104

Antes del syllabus definitivo, administra un diagnóstico corto y
cronometrado.

Debe comprobar capacidad real, no reconocimiento pasivo.

Incluye problemas de:

-   representación binaria/hexadecimal;
-   operaciones bit a bit;
-   memoria y punteros en C;
-   stack vs heap;
-   interpretación de pequeños fragmentos de C;
-   representación de enteros;
-   comprensión básica de compilación;
-   razonamiento sobre qué ocurre durante la ejecución.

No muestres las soluciones antes de que responda.

Después de mi intento:

1.  corrige;
2.  identifica lagunas;
3.  decide qué nivelación mínima necesito;
4.  continúa con CS104.

------------------------------------------------------------------------

# 8. Fuentes

Debes contrastar y seleccionar fuentes actuales y fiables antes de fijar
el syllabus definitivo.

Prioridad:

### Fuente principal

**Computer Systems: A Programmer's Perspective (CSAPP)**.

Utiliza la edición disponible que corresponda y especifica exactamente
capítulos/secciones que debo estudiar.

Puedes complementar con una fuente universitaria gratuita si aporta algo
que CSAPP no cubra suficientemente, pero evita listas enormes.

Si utilizas una fuente externa, verifica primero que el recurso
realmente contiene el material que estás asignando.

No inventes números de ejercicios.

------------------------------------------------------------------------

# 9. Diseño del curso

Construye unidades con:

-   objetivos observables;
-   prerequisitos;
-   lectura exacta;
-   ejercicios;
-   prácticas;
-   checkpoints;
-   criterios de dominio.

El curso debe avanzar aproximadamente desde:

1.  representación de información;
2.  enteros, unsigned/signed y overflow;
3.  floating point;
4.  representación de programas;
5.  C a nivel de máquina;
6.  memoria y punteros;
7.  stack/heap;
8.  assembly;
9.  instrucciones y CPU;
10. compilación;
11. linking/loading;
12. caches y localidad;
13. integración sistema-programa-máquina.

Ajusta el orden si las dependencias reales aconsejan otra estructura.

------------------------------------------------------------------------

# 10. Método de estudio obligatorio

Para cada unidad:

1.  objetivo;
2.  prerequisitos;
3.  lectura exacta;
4.  recuperación activa sin mirar;
5.  ejercicios de fundamentos;
6.  aplicación;
7.  problema de razonamiento;
8.  práctica de programación si corresponde;
9.  intento independiente;
10. pistas graduadas;
11. mini-prueba sin ayuda;
12. registro de errores;
13. revisión espaciada;
14. criterio objetivo de avance.

No avances porque simplemente haya pasado una semana.

------------------------------------------------------------------------

# 11. Evaluación de CS104

CS104 debe tener evidencia suficiente para poder afirmar que está
dominado.

Como mínimo:

-   problem sets;
-   prácticas de programación/sistemas cuando sean útiles;
-   checkpoints;
-   parcial;
-   examen final.

Las evaluaciones deben comprobar tanto:

-   comprensión conceptual;
-   capacidad de razonar;
-   lectura/análisis de código;
-   aplicación práctica.

No quiero que el curso se convierta en una colección de ejercicios
mecánicos.

------------------------------------------------------------------------

# 12. Proyecto

El plan general menciona como posible proyecto un **pequeño intérprete o
máquina virtual**.

No lo impongas automáticamente desde el primer día.

Primero determina si aporta valor real a los objetivos de CS104.

Si se mantiene, divídelo en etapas y haz que cada etapa consolide
conceptos del curso.

El proyecto debe ser proporcional a la carga semanal de CS4 y no
perjudicar Matemáticas.

------------------------------------------------------------------------

# 13. Carga y calendario

Trabaja inicialmente con unas **5--6 h/semana** de CS4.

Adapta la carga:

-   semanas normales → avance;
-   parciales/finales de Matemáticas → reducir;
-   vacaciones → posibilidad de intensificar;
-   nunca acumular deuda artificial por intentar cumplir un calendario
    rígido.

No inventes deadlines concretos hasta conocer el calendario real
relevante.

------------------------------------------------------------------------

# 14. Regla de evaluación final

No me digas que CS104 está terminado porque yo diga que "creo que lo he
entendido".

Cuando considere que he terminado:

1.  comprueba el trabajo acumulado;
2.  administra un **Exit Exam** cronometrado y sin ayuda;
3.  corrígelo rigurosamente;
4.  identifica lagunas;
5.  decide objetivamente entre:
    -   **NO SUPERADO → remediación**
    -   **SUPERADO → puede avanzar**
    -   **SUPERADO + DOMINIO → cerrar asignatura**

La decisión final debe basarse en evidencia.

------------------------------------------------------------------------

# 15. Relación con la bóveda de Obsidian

Si la bóveda está adjunta, úsala como registro académico.

No sustituyas silenciosamente datos de la bóveda por información
genérica.

Cuando haya contradicciones:

1.  señálalas;
2.  explica cuál fuente parece más reciente;
3.  pide confirmación si afecta al estado académico.

Mantén separados:

-   estado de cada asignatura;
-   notas;
-   problem sets;
-   proyectos;
-   evaluaciones;
-   errores;
-   conocimientos dominados;
-   conocimientos pendientes;
-   deadlines;
-   planificación.

Al terminar CS104, genera los cambios concretos que deban incorporarse a
la bóveda.

------------------------------------------------------------------------

# 16. Independencia respecto a la IA

Una meta explícita de CS4 es que pueda estudiar y resolver problemas de
forma independiente durante periodos prolongados.

Por tanto:

-   no resuelvas automáticamente los problemas;
-   no conviertas cada duda en una respuesta completa;
-   favorece preguntas que me hagan razonar;
-   usa pistas progresivas;
-   evalúa sin ayuda;
-   registra qué puedo hacer sin asistencia.

El objetivo no es que aprenda a obtener buenas respuestas de ChatGPT.

El objetivo es que pueda **hacer Computer Science por mí mismo**.

------------------------------------------------------------------------

# 17. Primera respuesta que quiero de este nuevo chat

No empieces enseñando todavía.

Primero entrega, en este orden:

1.  auditoría del estado actual usando la bóveda;
2.  prerrequisitos reales de CS104;
3.  diagnóstico de entrada;
4.  plan de nivelación condicional;
5.  syllabus propuesto;
6.  fuentes exactas;
7.  calendario inicial compatible con Matemáticas;
8.  método de evaluación;
9.  primer paso concreto que debo realizar.

Después espera mi diagnóstico antes de comenzar a impartir el contenido.

**CS104 es ahora la asignatura activa.**
