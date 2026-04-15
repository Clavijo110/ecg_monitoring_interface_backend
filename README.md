# ECG Monitoring Backend

Backend Node.js para la aplicación de monitoreo ECG. Maneja la comunicación con dispositivos seriales (puertos COM) y proporciona datos en tiempo real vía WebSocket.

## Requisitos

- Node.js 14+
- npm

## Instalación

```bash
npm install
```

## Ejecución

### Desarrollo local (con auto-reinicio)
```bash
npm run dev
```

### Producción (o sin nodemon)
```bash
npm start
```

El servidor estará disponible en `http://localhost:3001` (o en el puerto definido por `$PORT`)

## Variables de Entorno

```
PORT=3001          # Puerto donde escucha el servidor
```

## API Endpoints

- `GET /api/ports` - Lista puertos seriales disponibles
- `POST /api/connect` - Conectar a un puerto serial
- `GET /api/status` - Obtener estado de conexión
- `POST /api/cmd` - Enviar comando al dispositivo

## WebSocket Events

### Cliente → Servidor
- `connect` - Conexión establecida
- `disconnect` - Desconexión

### Servidor → Cliente
- `serial_status` - Estado de conexión serial
- `serial_data` - Datos del dispositivo
- `serial_tx` - Comandos enviados
- `serial_raw` - Respuestas raw del dispositivo

## Estructura del Código

- `server.js` - Punto de entrada principal
  - Express server
  - Socket.io setup
  - Rutas API
  - Manejo de puertos seriales

## Dependencias Principales

- **express** - Framework web
- **socket.io** - Comunicación WebSocket
- **serialport** - Comunicación con puertos seriales
- **cors** - CORS middleware

## Despliegue en Render.com

1. Ve a [render.com](https://render.com)
2. Crea un nuevo "Web Service"
3. Conecta este repositorio GitHub
4. Configura:
   - **Build Command**: `npm install`
   - **Start Command**: `node server.js`
5. Deploy

## Notas

- El servidor se ejecutará en `${PORT}` (3001 por defecto)
- Socket.io está disponible en `/socket.io/socket.io.js`
- CORS está habilitado para todas las origins

## Desarrollo

Para modificar el servidor:

```bash
# Instalar dependencias si faltan
npm install

# Editar server.js según sea necesario
# El servidor se reinicia automáticamente en desenvolvimento
```

## Licencia

MIT
