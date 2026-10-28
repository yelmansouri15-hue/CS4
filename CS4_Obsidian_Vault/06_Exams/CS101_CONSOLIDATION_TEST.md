# CS101 — Consolidation Test

- Fecha: 2026-09-06
- Puntuación: **28/30**
- Estado: **PASSED**
- Decisión: **CS101 cerrado; listo para CS102**

## Corrección

### Bloque A — Big-O
- 1a: correcta — `O(log n)`
- 1b: correcta — `O(n²)`
- 1c: incorrecta — correcta `O(n)` porque el `while` y el `for` son secuenciales, no anidados.
- 1d: temporal `O(n)` y espacial `O(n)` correctas. La razón precisa de `set` es hashing/acceso esperado constante.

### Bloque B — Estructuras
- 2a–2d: correctas.

### Bloque C — Algoritmos
- 3a–3b: correctas.
- 3c: correcta en esencia; `set` ofrece búsqueda esperada `O(1)` y se consulta una vez por elemento.

### Bloque D — Grafos
- 4a: correcto; la estrategia descrita es BFS.
- 4b: correcto — queue.
- 4c: correcto — `visited`.

### Bonus
- Solución B correctamente elegida. La solución A es `O(n²)`.

## Diagnóstico
La prueba confirma que los errores del Exit Exam eran principalmente de formalización y no de falta de intuición algorítmica. La mejora tras feedback fue suficiente para cerrar CS101.
