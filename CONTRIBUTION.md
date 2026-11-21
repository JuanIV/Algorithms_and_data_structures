# Guía de contribución y flujo de trabajo

## 1. Objetivo

Este documento establece las normas de colaboración y gestión del código del proyecto.

El objetivo es evitar conflictos entre integrantes, mantener una rama principal estable y garantizar que todos los cambios sean revisados antes de incorporarse al proyecto.

**Ningún integrante debe modificar directamente la rama `main`.**

## 2. Estructura de ramas

El repositorio tendrá exactamente estas cuatro ramas de trabajo:

| Rama | Responsable |
|---|---|
| `main` | Rama principal del proyecto |
| `enProceso/juan` | Juan |
| `enProceso/alvaro` | Álvaro |
| `enProceso/tiago` | Tiago |

### Normas

- `main` contiene únicamente código integrado y revisado.
- Cada integrante trabaja exclusivamente en su propia rama.
- Cada integrante es responsable de realizar los commits y subir sus cambios a su rama.
- No se deben crear ramas adicionales.
- No se deben realizar commits directamente sobre `main`.
- No se deben modificar las ramas personales de otros integrantes.

Las ramas personales son permanentes: no es necesario crear una rama nueva para cada tarea.

## 3. Flujo de trabajo obligatorio

### Paso 1. Sincronizar el proyecto

Antes de empezar a trabajar, cada integrante debe actualizar su copia local con los últimos cambios de `main`.

```bash
git switch main
git pull origin main
```

A continuación, debe cambiar a su rama personal:

```bash
git switch enProceso/juan
```

Sustituir `juan` por el nombre correspondiente.

Para incorporar los últimos cambios de `main` a la rama personal:

```bash
git merge main
```

Si aparecen conflictos, deben resolverse antes de continuar.

### Paso 2. Trabajar en la rama personal

Todos los cambios deben realizarse en la rama personal correspondiente.

Comprobar la rama actual:

```bash
git branch
```

Guardar los cambios:

```bash
git add .
git commit -m "Descripción clara de los cambios"
```

Los mensajes de commit deben describir brevemente qué se ha modificado.

Ejemplos:

```text
Add login screen
Fix database connection
Update user interface
Refactor authentication logic
```

### Paso 3. Subir los cambios

Enviar los commits al repositorio remoto:

```bash
git push origin enProceso/juan
```

Sustituir la rama por la correspondiente a cada integrante.

### Paso 4. Crear un Pull Request

Cuando los cambios estén preparados, el integrante debe crear un Pull Request en GitHub:

- **Base:** `main`
- **Compare:** su rama personal (`enProceso/juan`, por ejemplo).

El Pull Request debe incluir:

- Una descripción de los cambios realizados.
- El objetivo de esos cambios.
- Cualquier aspecto que los revisores deban tener en cuenta.

No se debe integrar ningún cambio directamente en `main`.

### Paso 5. Revisión y aprobación

Los otros dos integrantes deben revisar el Pull Request.

Cada revisor debe comprobar:

- Que los cambios funcionan correctamente.
- Que no introducen errores.
- Que el código es comprensible y mantiene la organización del proyecto.
- Que no se modifican funcionalidades ajenas sin justificación.

**Los tres integrantes deben estar de acuerdo con cada integración.**

El autor del Pull Request no puede aprobar sus propios cambios. Por tanto, se necesitan dos aprobaciones de los otros integrantes.

Si se solicitan modificaciones, el autor debe realizarlas en su rama personal y subir los nuevos commits. Las aprobaciones anteriores pueden quedar invalidadas y será necesario revisar de nuevo los cambios.

### Paso 6. Integrar los cambios

Una vez obtenidas las dos aprobaciones y resueltas todas las conversaciones pendientes, se podrá integrar el Pull Request en `main`.

La integración debe realizarse mediante GitHub, utilizando el mecanismo de merge habilitado en el repositorio.

### Paso 7. Actualizar las ramas personales

Después de que un Pull Request haya sido integrado, todos los integrantes deben actualizar su copia local:

```bash
git switch main
git pull origin main
```

Después, deben incorporar los nuevos cambios a su propia rama:

```bash
git switch enProceso/juan
git merge main
git push origin enProceso/juan
```

Así, todas las ramas personales estarán sincronizadas con la última versión del proyecto.

---

## 4. Normas de colaboración

1. **Nunca trabajar directamente en `main`.**
2. **Cada integrante trabaja exclusivamente en su rama personal.**
3. No subir cambios de trabajo incompletos a `main`.
4. Todos los cambios que lleguen a `main` deben pasar por un Pull Request.
5. Todos los integrantes deben revisar y aprobar cada Pull Request.
6. Mantener las ramas personales actualizadas con `main`.
7. Resolver los conflictos antes de solicitar la integración.
8. No modificar el trabajo de otro integrante sin comunicarlo previamente.
9. Utilizar mensajes de commit descriptivos.
10. Comunicar al equipo los cambios importantes que puedan afectar a otras partes del proyecto.

## 5. Resolución de conflictos

Si dos integrantes modifican las mismas partes del proyecto, Git puede detectar conflictos al integrar sus cambios.

En ese caso:

1. Identificar los archivos afectados.
2. Revisar las modificaciones de ambos integrantes.
3. Decidir conjuntamente qué cambios deben conservarse.
4. Resolver los conflictos.
5. Comprobar que el proyecto sigue funcionando.
6. Realizar un commit con la resolución.
7. Continuar con el proceso de Pull Request.

No se deben resolver conflictos eliminando cambios de otro integrante sin comprobar previamente su contenido.

---

## 6. Resumen del flujo

```text
          MAIN
           |
           | Actualizar
           v
     RAMA PERSONAL
           |
           | Trabajar y hacer commits
           v
       GIT PUSH
           |
           v
     PULL REQUEST
           |
           v
   REVISIÓN DEL EQUIPO
           |
      2 APROBACIONES
           |
           v
       MERGE EN MAIN
           |
           v
   ACTUALIZAR RAMAS PERSONALES
           |
           v
      SIGUIENTE TAREA
```

**Regla fundamental:** ningún cambio entra en `main` sin haber sido revisado y aprobado por los otros dos integrantes del equipo.
