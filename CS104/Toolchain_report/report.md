# Informe Técnico: Del Código Fuente C al Ejecutable ELF en Linux x86-64

## 1. Entorno

El experimento se ejecutó en un entorno Linux x86-64 (WSL2 con Ubuntu) utilizando la cadena de herramientas GNU (`gcc` y `binutils`) para generar y analizar binarios en formato **ELF** (*Executable and Linkable Format*):

* **Arquitectura destino (`gcc -dumpmachine`):** `x86_64-linux-gnu`
* **Formato de binarios:** ELF 64-bit LSB (System V ABI)
* **Compilador y ensamblador:** `gcc` / `as` (GNU Binutils)
* **Herramientas de inspección:** `file`, `nm`, `objdump`, `readelf`

---

## 2. Programa

El proyecto se organiza en dos unidades de traducción independientes (`src/main.c` y `src/util.c`) conectadas mediante un archivo de cabecera (`src/util.h`) con *include guards*:

* **`src/util.h`**: Declara la interfaz pública de la función auxiliar `sumar` (protegida con `#ifndef` / `#define` / `#endif`) para que otros módulos conozcan su firma sin depender de su implementación.
* **`src/util.c`**: Define e implementa la función `sumar` (en nuestro caso, la operación aritmética invocada desde `main` con los argumentos `15` (`0xf`) y `27` (`0x1b`)).
* **`src/main.c`**: Incluye `<stdio.h>` y `"util.h"`, invoca `sumar(15, 27)` e imprime el resultado mediante `printf`.

---

## 3. Traducción

El proceso completo de transformación desde código fuente C hasta un ejecutable consta de cuatro etapas secuenciales:

```text
  src/main.c ──▶ [ Preprocesador (cpp) ] ──▶ build/main.i ──▶ [ Compilador (cc1) ] ──▶ build/main.s
                                                                                            │
  src/util.c ──▶ [ Preprocesador (cpp) ] ──▶ build/util.i ──▶ [ Compilador (cc1) ] ──▶ build/util.s
                                                                                            │
  ┌─────────────────────────────────────────────────────────────────────────────────────────┘
  ▼
[ Ensamblador (as) ] ──▶ build/main.o  ──┐
[ Ensamblador (as) ] ──▶ build/util.o  ──┼──▶ [ Enlazador (ld) ] ──▶ build/programa
                                         │
                             libc.so.6 ──┘
```

### Productos generados por etapa
| Etapa | Herramienta | Comando utilizado | Artefacto generado | Descripción |
| --- | --- | --- | --- | --- |
| **1. Preprocesamiento**      | ```cpp``` (```gcc -E```)    | ```gcc -E src/main.c -o build/main.i```    | ```build/main.i```, ```build/util.i```    | Expande directivas ```#include``` y macros; elimina comentarios    |
| **2. Compilación**                             | ```cc1``` (```gcc -S```)                            | ```gcc -S -O0 src/main.c -o build/main.s```                                           | ```build/main.s```, ```build/util.s```                                          | Traduce C preprocesado a código ensamblador x86-64.                                                                   |
| **3. Ensamblado**                             | ```as```                            | ```as build/main.s -o build/main.o```                                           | ```build/main.o```, ```build/util.o```                                          | Genera código máquina binario en ficheros objeto relocalizables.                                                                    |
| **4. Enlazado**                             | ```ld``` (```gcc```)                            | ```gcc build/main.o build/util.o -o build/programa```                                           | ```build/programa```                                          | Resuelve símbolos externos y produce el ejecutable ELF final.                                                                     |

### Diferencia frente a ```gcc -c```
Ejecutar ```gcc -c src/main.c -o build/main.o``` ejecuta de una sola vez las tres primeras etapas (```cpp``` $\to$ ```cc1``` $\to$ ```as```) sobre una única unidad de traducción y detiene el driver antes de invocar al enlazador (```ld```). Esto permite compilar cada módulo de forma modular e independiente sin necesidad de disponer todavía de las implementaciones de otros módulos ni de las bibliotecas finales.

## 4. Objetos
Al inspeccionar los tres artefactos binarios con ```file```:
```Plaintext
build/main.o:   ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
build/util.o:   ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
build/programa: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=a68df33a42b4652e556372593355fc1aba627a9f, for GNU/Linux 3.2.0, not stripped
```
- ```build/main.o``` y ```build/util.o``` son **ficheros objeto relocalizables** (```ET_REL```): contienen secciones de código (```.text```), datos de solo lectura (```.rodata```), tablas de símbolos (```.symtab```) y registros de reubicación (```.rela.text```), pero carecen de *Program Headers* porque no son ejecutables por sí mismos.

- ```build/programa``` es un **ejecutable independiente de posición** (```PIE```) enlazado dinámicamente, que incluye tanto *Section Headers* como *Program Headers* para su mapeo en memoria virtual por parte del núcleo Linux.

## 5. Símbolos
La inspección de las tablas de símbolos mediante ```nm build/main.o``` y ```nm build/util.o``` muestra:
```Plaintext
# nm build/main.o
0000000000000000 T main
                 U printf
                 U sumar

# nm build/util.o
0000000000000000 T sumar
```
- **Símbolo definido (```T```)**: Tanto ```main``` en ```build/main.o``` como ```sumar``` en ```build/util.o``` aparecen marcados con ```T``` (*Text section*). Esto indica que son símbolos globales cuyo código está definido en la sección ```.text``` de ese fichero objeto (en el desplazamiento inicial ```0x0```).

- **Símbolo indefinido (```U```)**: En ```build/main.o```, tanto ```sumar``` como ```printf``` figuran con ```U``` (*Undefined*). El módulo los referencia, pero su definición reside fuera de ```main.o``` (```sumar``` se resolverá estáticamente con ```util.o```, mientras que ```printf``` se resolverá dinámicamente contra ```libc.so.6```).

## 6. Reubicación
Al desensamblar ```build/main.o``` con ```objdump -dr build/main.o``` e inspeccionar las entradas de reubicación con ```readelf -r build/main.o```:
```Plaintext
0000000000000000 <main>:
   0:   f3 0f 1e fa             endbr64
   4:   55                      push   %rbp
   5:   48 89 e5                mov    %rsp,%rbp
   8:   48 83 ec 10             sub    $0x10,%rsp
   c:   be 1b 00 00 00          mov    $0x1b,%esi
  11:   bf 0f 00 00 00          mov    $0xf,%edi
  16:   e8 00 00 00 00          call   1b <main+0x1b>
                        17: R_X86_64_PLT32      sumar-0x4
```
```Plaintext
Relocation section '.rela.text' at offset 0x1d8 contains 3 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000017  000500000004 R_X86_64_PLT32    0000000000000000 sumar - 4
000000000024  000300000002 R_X86_64_PC32     0000000000000000 .rodata - 4
000000000033  000600000004 R_X86_64_PLT32    0000000000000000 printf - 4
```
- **Mecanismo de parcheo**: En `main.o`, la instrucción `call` comienza en `0x16` (`e8`) y deja un operando provisional de 32 bits a cero (`00 00 00 00`) a partir del desplazamiento `0x17`.

- **Símbolo y tipo de reubicación**: La entrada en `.rela.text` en el offset `0x17` es de tipo `R_X86_64_PLT32`, vinculada al símbolo sumar con un addend de `-4` (necesario porque el direccionamiento relativo al contador de programa `PC` se calcula respecto a la dirección de la siguiente instrucción, `0x1b`, ubicada 4 bytes después del inicio del operando).

- **Resultado tras el enlazado (`objdump -d build/programa`)**: En el ejecutable final, `main` se ubica en `0x1149`, el `call` queda en `0x115f` y sumar en `0x1187`. El enlazador sustituye los ceros por `23 00 00 00` (`0x1164 + 0x23 = 0x1187`), resolviendo la llamada mediante un salto directo relativo al PC.

## 7. Ejecutable
El análisis de la cabecera ELF (readelf -h), los encabezados de programa (readelf -l) y la sección dinámica (readelf -d) de build/programa revela:

Plaintext
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Entry point address:               0x1060
Plaintext
  INTERP         0x0000000000000374 0x0000000000000374 0x0000000000000374
                 0x000000000000001c 0x000000000000001c  R      0x1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
Plaintext
Dynamic section at offset 0x2dc8 contains 27 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]

- Tipo de ejecutable: DYN (Position-Independent Executable file). Se genera como objeto compartido posicionable para que el sistema operativo pueda aplicar ASLR (Address Space Layout Randomization) al cargarlo en memoria. Su punto de entrada (0x1060) apunta a _start, que inicializa el entorno de ejecución y llama a __libc_start_main pasándole la dirección de main (0x1149).

- Segmentos cargados en memoria (LOAD): El binario define 4 segmentos LOAD alineados a página (0x1000 bytes) con separación estricta de permisos (W^X):

    1. 0x0000 (R): Cabeceras ELF, .interp, .dynsym, .dynstr y tablas de reubicación dinámica.

    2. 0x1000 (R E): Código ejecutable de solo lectura (.init, .plt, .plt.sec, .text, .fini).
    
    3. 0x2000 (R): Datos constantes y metadatos de pila (.rodata, .eh_frame).
    
    4. 0x3db8 (RW): Variables globales y tablas de enlazado dinámico (.init_array, .fini_array, .dynamic, .got, .data, .bss), protegidas tras la resolución inicial mediante GNU_RELRO (BIND_NOW).

- Intérprete dinámico: Sí dispone de segmento INTERP apuntando a /lib64/ld-linux-x86-64.so.2, encargado de cargar las bibliotecas compartidas y resolver símbolos dinámicos antes de ceder el control al programa.

- Dependencias dinámicas: La sección .dynamic declara como única dependencia externa (NEEDED) a libc.so.6, desde donde se resuelve printf@GLIBC_2.2.5 a través de su entrada en .plt.sec (0x1050) y la Global Offset Table (.got en 0x3fd0).

## 8. Error experimental
Al intentar enlazar únicamente build/main.o omitiendo build/util.o:

Bash
gcc build/main.o -o build/programa_error
El enlazador produce el siguiente error:

Plaintext
/usr/bin/x86_64-linux-gnu-ld.bfd: build/main.o: in function `main':
main.c:(.text+0x17): undefined reference to `sumar'
collect2: error: ld returned 1 exit status

- Por qué la compilación de main.o sí tuvo éxito: Durante la compilación de src/main.c, el compilador solo necesita conocer la declaración (firma) de sumar proporcionada por src/util.h para verificar tipos y aplicar la convención de llamadas System V AMD64 ABI (primer argumento en %edi, segundo en %esi y retorno en %eax). El compilador deja deliberadamente un hueco de 4 bytes en .text+0x17 y delega su resolución al enlazador.

- Por qué el enlazado falla: La responsabilidad del enlazador (ld) es combinar todos los objetos y bibliotecas para asignar direcciones definitivas y parchear cada registro de reubicación. Al faltar build/util.o, ningún módulo exporta la definición del símbolo sumar, por lo que ld no puede calcular el desplazamiento de destino en main.c:(.text+0x17) y aborta la generación del ejecutable.

## 9. Conclusiones
1. Compilación modular vs. resolución global: La separación entre declaración (.h) e implementación (.c) permite traducir unidades independientes en paralelo hasta código máquina relocalizable (.o), postergando la resolución de direcciones hasta la fase de enlazado.

2. El papel central de las tablas de símbolos y reubicaciones: Los ficheros .o no son cajas negras; mediante .symtab y .rela.text registran exactamente qué símbolos ofrecen (T), cuáles necesitan (U) y qué instrucciones deben parchearse (R_X86_64_PLT32).

3. Diferencia entre resolución estática y dinámica: Mientras la llamada a sumar se resuelve de forma estática en tiempo de enlazado mediante un desplazamiento relativo directo (call 1187), las funciones de la biblioteca estándar como printf se resuelven dinámicamente en tiempo de carga/ejecución mediante /lib64/ld-linux-x86-64.so.2, la PLT y la GOT.

4. Seguridad y estructura de los ejecutables modernos: Los binarios ELF actuales en Linux x86-64 se construyen como PIE (ET_DYN) y dividen sus secciones en segmentos LOAD con permisos segregados (R, R E, RW) y GNU_RELRO para endurecer el proceso frente a ataques de corrupción de memoria.