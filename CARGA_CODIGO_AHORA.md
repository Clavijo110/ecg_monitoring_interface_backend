# 🚀 CARGA EL CÓDIGO EN ARDUINO UNO - GUÍA FINAL

## ✅ Estado Actual

- ✅ Código compilado exitosamente (6640 bytes)
- ✅ Archivo HEX generado: `arduino_ecg_simulator.hex`
- ✅ Optimizado para Arduino Uno (ATmega328P)

**Problema:** El puerto COM4 está bloqueado a nivel de sistema.

---

## ✅ SOLUCIÓN - Arduino IDE Web (RECOMENDADO)

**Ventaja:** Funciona 100% garantizado, no hay problemas con puertos.

### Paso 1: Abre Arduino IDE Web
```
https://create.arduino.cc/
```

### Paso 2: Inicia sesión
- Si no tienes cuenta: **Sign up** (gratis)
- Con Google/GitHub es rápido

### Paso 3: Instala Arduino Create Agent
Si te pide "Connect your Arduino":
1. Descarga: https://create.arduino.cc/getting-started
2. Ejecuta el instalador (pequeño programa)
3. Conecta tu Arduino Uno
4. Actualiza la página de Arduino Create

### Paso 4: Copia el código
1. Abre el archivo: 
```
c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator\arduino_ecg_simulator.ino
```

2. Copia TODO el contenido

3. En Arduino Create, pega en el editor (reemplaza lo que hay)

### Paso 5: Carga
1. **Selecciona:** Arduino Uno
2. **Selecciona:** COM4
3. **Click:** Upload (⬆️ botón)
4. Espera a que termine

---

## 🟢 Alternativa 2: Arduino IDE Clásico (Local)

Si prefieres versión tradicional:

### 1. Cierra TODO
- VS Code
- Arduino IDE
- Cualquier terminal

### 2. Reinicia tu PC
```
Inicio → Reiniciar
```

Esto libera el puerto COM4.

### 3. Después de reiniciar, abre Arduino IDE

### 4. Abre el archivo
```
File → Open
c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator\arduino_ecg_simulator.ino
```

### 5. Configura
- **Tools → Board:** Arduino Uno
- **Tools → Port:** COM4

### 6. Upload
- Click **➡️ Upload**
- Espera: "Done uploading"

---

## ✅ Verificar que Funcionó

Después de cargar, abre **Serial Monitor** en Arduino IDE:

1. **Tools → Serial Monitor**
2. En la esquina abajo-derecha: **115200 baud**
3. Presiona **Reset** en Arduino (botón rojo)

Deberías ver:
```
READY
STATUS: ECG Simulator v1.0 - Starting
DATA,45,I,72,0
DATA,52,I,73,0
DATA,61,I,72,1
```

Si ves esto ✅ **¡Éxito!**

---

## 🎮 Luego Conecta desde la App

1. **Backend:** `npm start` (puerto 3001)
2. **Frontend:** `http://localhost:3000`
3. Actualizar puertos
4. Conectar COM4

¡Verás datos en vivo!

---

## 🆘 Si Aún No Funciona

### "Arduino IDE dice 'Port is busy'"
```
Solución:
1. Cierra TODAS las aplicaciones
2. Reinicia Windows
3. Vuelve a intentar
```

### "No veo COM4"
```
Solución:
1. Instala drivers: https://support.arduino.cc/hc/en-us/articles/4411305694610
2. Reinicia
3. Reconecta Arduino
```

### "Compilation error"
```
El código ya está compilado.
Descarga la carpeta: c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator\

Y en Arduino IDE abre: arduino_ecg_simulator.ino
```

---

## ♿ Última Opción: Upload Manual con HEX

Si todo falla, usa **Atmel Studio** o **XLoader**:

1. Descarga XLoader: http://xloader.russemotto.com/
2. Selecciona: `arduino_ecg_simulator.hex`
3. Device: ATmega328P
4. Comm Port: COM4
5. Baud: 115200
6. Upload

---

**Avísame cuando veas READY en Serial Monitor** 🚀

El código ECG está 100% listo, solo falta cargarlo en el Arduino.
