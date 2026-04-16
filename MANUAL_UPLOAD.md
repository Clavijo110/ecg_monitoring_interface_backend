# 🚀 CARGAR SIMULADOR ECG EN ARDUINO UNO - INSTRUCCIONES MANUALES

## ✅ El código está compilado y listo

**Carpeta con código compilado:**
```
c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator\
```

---

## 📋 OPCIÓN 1: Arduino IDE Web (RECOMENDADO - MÁS FÁCIL)

### Paso 1: Abre Arduino IDE Web
```
https://create.arduino.cc/
```

### Paso 2: Inicia sesión (o crea cuenta gratis)

### Paso 3: Crea nuevo Sketch
- Click: **"Create new Sketch"**
- Dale nombre: `arduino_ecg_simulator`

### Paso 4: Copia el código
1. Abre: `c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator.ino`
2. Copia TODO el contenido
3. Pega en Arduino IDE Web (reemplaza el código)

### Paso 5: Configura y carga
1. **Select Board**: "Arduino Uno"
2. **Select Port**: "COM4" 
3. Click **Upload** (botón verde con flecha) ➡️
4. Espera: "Done uploading"

---

## 📋 OPCIÓN 2: Arduino IDE Clásico (Local)

### Paso 1: Instala Arduino IDE
```
https://www.arduino.cc/en/software
```
Descarga e instala versión 1.8.x o 2.x

### Paso 2: Abre Arduino IDE

### Paso 3: Abre el código
- `File → Open`
- Selecciona: `c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator\arduino_ecg_simulator.ino`

### Paso 4: Configura
- **Tools → Board** → Arduino Uno
- **Tools → Port** → COM4

### Paso 5: Carga el código
- Click **Upload** (botón ➡️)
- Espera: "Done uploading"

---

## ✅ Verificar que se cargó

Una vez cargado, abre Serial Monitor en Arduino IDE:
```
Tools → Serial Monitor
```

Configura:
- Velocidad: **115200 baud** ⚠️
- Line ending: **Newline**

Deberías ver:
```
READY
STATUS: ECG Simulator v1.0 - Starting
DATA,45,I,72,0
DATA,52,I,73,0
DATA,61,I,72,1
...
```

Si ves esto, ✅ **¡El simulador está corriendo!**

---

## 🎮 Prueba desde App

Una vez el Arduino esté enviando datos:

1. **Backend corriendo:**
```bash
npm start  # en ecg_web_node_backend
```

2. **Frontend:**
```bash
python -m http.server 3000 --directory frontend/public
```

3. **Abre:** `http://localhost:3000`

4. **Click:** "Actualizar puertos"
   - Deberías ver COM4

5. **Conecta**
   - ¡Verás los datos ECG en tiempo real!

---

## 🔧 Si no funciona

### "No veo nada en Serial Monitor"
```
1. Verifica velocidad: 115200 baud
2. Presiona botón Reset del Arduino
3. Espera 2-3 segundos
4. Deberías ver READY
```

### "Still say 'Acceso denegado'"
```
1. Cierra TODAS las aplicaciones (VS Code, Serial Monitor, etc)
2. Desconecta Arduino
3. Espera 3 segundos
4. Reconecta Arduino
5. Intenta upload nuevamente
```

### "Says port not found"
```
1. Verifica que Arduino está conectado (LED debe brillar)
2. Instala drivers Arduino: https://support.arduino.cc/hc/en-us/articles/4411305694610-Install-the-Arduino-IDE
3. Reinicia computadora
```

---

## 📊 Una vez funcione

Tendrás:
- ✅ 6 derivadas (I, II, III, aVR, aVL, aVF)
- ✅ Forma de onda PQRST realista
- ✅ Cambios de BPM dinámicos
- ✅ Eventos de marcapasos
- ✅ Respuesta a todos los botones

---

**Avísame cuando hayas cargado y veas READY en Serial Monitor** 🚀
