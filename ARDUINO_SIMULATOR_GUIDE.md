# 🎯 Arduino ECG Simulator - Instrucciones de Carga

## 📋 Descripción

Código Arduino que simula una señal ECG realista con:
- ✅ **6 derivadas** (I, II, III, aVR, aVL, aVF)
- ✅ **Forma de onda PQRST** realista (componentes del ECG)
- ✅ **Variabilidad de ritmo** (cambios en BPM)
- ✅ **Eventos de marcapasos** simulados
- ✅ **Respuesta a comandos** del frontend
- ✅ **Modo auto/manual** de derivadas

---

## 🛠️ Requisitos

1. **Arduino IDE** - Descargar desde [arduino.cc](https://www.arduino.cc/en/software)
2. **Arduino Board** - Mega, Uno, o compatible
3. **Cable USB** - Para conectar Arduino a PC
4. **Backend corriendo** - `npm start` en `ecg_monitoring_interface_backend`

---

## 📥 Pasos para Cargar

### 1️⃣ Descargar el código

**Opción A - Desde el repositorio:**
```bash
# El archivo ya está en:
c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator.ino
```

**Opción B - Copiar contenido:**
```
Copiar contenido del archivo arduino_ecg_simulator.ino
```

### 2️⃣ Abrir Arduino IDE

1. Abre **Arduino IDE**
2. Vete a: `File → New`
3. Pega el código
4. Guarda con: `arduino_ecg_simulator.ino`

### 3️⃣ Seleccionar Board y Puerto

En Arduino IDE:
1. **Tools → Board** → Selecciona tu Arduino (ej: Arduino Mega 2560)
2. **Tools → Port** → Selecciona tu puerto COM (ej: COM3, COM4)

### 4️⃣ Verificar y Cargar

```
1. Haz click en ✔️ "Verify" (compilar)
2. Haz click en ➡️ "Upload" (cargar)
3. Espera a que aparezca: "Done uploading"
```

### 5️⃣ Ver Datos en Serie

En Arduino IDE:
- **Tools → Serial Monitor**
- Velocidad: **115200 baud** ⚠️ MUY IMPORTANTE
- Deberías ver: `READY` y luego `DATA,xx,I,72,0`

---

## 📊 Protocolo de Datos

### Envío del Arduino (→ Backend)

```
READY                           # Inicio
DATA,ecg_value,derivada,bpm,mp # Datos ECG cada 40ms
ACK,ECG_ON                      # cuando comando 'e'
ACK,ECG_OFF                     # cuando comando 's'
ACK,AUTO_ON                     # cuando comando 'a'
ACK,MANUAL_ON                   # cuando comando 'm'
ACK,DERIVADA,derivada           # cuando comando 1-6
AUTO,DERIVADA,derivada          # cambio automático de derivada
EVENT,MP                        # evento marcapasos
```

### Recepción del Arduino (← Frontend)

| Comando | Acción |
|---------|--------|
| `e` | Iniciar ECG |
| `s` | Detener ECG |
| `a` | Modo automático (cambia derivadas) |
| `m` | Modo manual (controla derivadas) |
| `1` | Derivada I |
| `2` | Derivada II |
| `3` | Derivada III |
| `4` | Derivada aVR |
| `5` | Derivada aVL |
| `6` | Derivada aVF |
| `?` | Query estado |

---

## 🧪 Verificar Conexión

### 1. Serial Monitor

Si ves en **Serial Monitor (115200 baud)**:
```
READY
STATUS: ECG Simulator v1.0 - Starting
DATA,45,I,72,0
DATA,52,I,73,0
DATA,61,I,72,0
...
```
✅ **Arduino OK**

### 2. Frontend

1. Abre: `http://localhost:3000`
2. Click: "Actualizar puertos"
3. Deberías ver tu puerto COM (ej: COM3)
4. Click: "Conectar"
5. Deberías ver valores en BPM y gráfica

---

## 🎮 Prueba de Funcionalidad

### Test 1: Derivadas
```
1. Click "Derivada 1" → Gráfica
2. Click "Derivada 2" → Gráfica diferente
3. Click "Derivada 3" → Otra forma
```
✅ Cada derivada debe mostrar forma diferente

### Test 2: Modo Auto
```
1. Click "Modo Auto"
2. La derivada cambia automáticamente cada 7 ciclos
3. Verás AUTO,DERIVADA en Serial Monitor
```

### Test 3: Modo Manual
```
1. Click "Modo Manual"
2. Control manual: "Derivada 1", "Derivada 2", etc
3. La derivada no cambia sola
```

### Test 4: ECG On/Off
```
1. Click "Iniciar ECG"
2. La gráfica se actualiza
3. Click "Detener ECG"
4. La gráfica se congela (no recibe datos)
```

### Test 5: Marcapasos
```
1. Ver Serial Monitor
2. Ocasionalmente verás: "EVENT,MP"
3. En la app: metric "Marcapasos" = "Si"
```

---

## ⚠️ Troubleshooting

### "Puerto COM desaparece"
```
Solución:
1. Revisa que Arduino IDE esté cerrado
2. O que Serial Monitor esté cerrado
3. Un solo programa puede usar el puerto serial
```

### "No se carga el código"
```
Solución:
1. Verifica: Tools → Board sea correcto
2. Verifica: Tools → Port sea correcto
3. Desconecta/Reconecta Arduino
4. Prueba con otro cable USB
```

### "Serial Monitor muestra basura"
```
Solución:
1. Verifica velocidad: 115200 baud ⚠️
2. No debe ser 9600 ni otra velocidad
3. Recarga el código completo
```

### "Datos pero gráfica no se actualiza"
```
Solución:
1. Verifica backend corriendo: npm start
2. Verifica Socket.io conecta: "✅ Socket conectado"
3. Revisa Console (F12) por errores
```

---

## 📈 Características del Simulador

| Parámetro | Valor | Descripción |
|-----------|-------|------------|
| Baudrate | 115200 | Velocidad comunicación |
| Sample Rate | 250 Hz | 250 muestras/seg |
| BPM Base | 72 | Ritmo cardíaco inicial |
| Variabilidad | ±2 BPM | Cambios aleatorios |
| Marcapasos | 5% | Probabilidad evento |
| Derivada Auto | 7 ciclos | Tiempo entre cambios |

---

## 🔄 Próximos Pasos

1. ✅ Código cargado en Arduino
2. ✅ Verificar datos en Serial Monitor
3. ✅ Conectar desde frontend
4. ✅ Probar todos los botones
5. ✅ Capturar datos ECG simulados

Cuando todo funcione:
- Reemplaza simulador con Arduino real
- Usa mismo protocolo de comunicación
- Todo lo demás funciona igual

---

**¡Éxito! 🚀**

Cuando tengas dudas ejecuta: `arduino_ecg_simulator.ino` en Arduino IDE
