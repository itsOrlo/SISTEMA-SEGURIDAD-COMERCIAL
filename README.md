# 🔐 SISTEMA-SEGURIDAD-COMERCIAL 🔐

## Proyecto de Sistema de Seguridad Comercial + Botón de Pánico (IoT)

Este proyecto combina la seguridad comercial con la tecnología IoT (Internet de las Cosas) para ofrecer protección y tranquilidad a tu negocio.

### 🚨 Características principales

- **Gestión de recursos con librerías Arduino:** El código utiliza librerías especializadas para optimizar la compatibilidad con módulos externos, permitiendo una gestión eficiente de los recursos y la personalización de mensajes, direcciones IP y alertas.

- **API Telegram:**  A través de un bot de Telegram conectado a internet, podrás controlar remotamente el sistema de seguridad, activando y desactivando la alarma, así como recibir notificaciones instantáneas en caso de emergencia.

### ⚙️ Componentes del sistema

- **Dispositivo Arduino:** El cerebro del sistema, encargado de procesar las señales de los sensores y controlar los actuadores.
- **Sensores:** Detectan eventos como movimiento, apertura de puertas, rotura de cristales, etc.
- **Actuadores:** Sirenas, luces de alarma, relés para controlar otros dispositivos.
- **Botón de pánico:** Permite activar manualmente la alarma en caso de emergencia.
- **Conexión a internet:** Necesaria para la comunicación con el bot de Telegram.

### 🛠️ Instalación y configuración

1. **Hardware:**
   - Conecta los sensores y actuadores al dispositivo Arduino según el esquema proporcionado.
   - Configura la conexión a internet (WiFi, Ethernet, etc.).

2. **Software:**
   - Instala las librerías Arduino necesarias.
   - Configura el bot de Telegram y obtén el token de acceso.
   - Modifica el código fuente para incluir el token del bot, la dirección IP del dispositivo y personalizar los mensajes de alerta.

### 📱 Uso del sistema

1. **Activar/Desactivar:** Envía comandos específicos al bot de Telegram para activar o desactivar la alarma.
2. **Botón de pánico:** Presiona el botón físico para activar la alarma inmediatamente.
3. **Notificaciones:** Recibe alertas en Telegram en caso de que se active algún sensor.

### 🤖 Comandos del bot de Telegram

- `/activar`: Activa el sistema de seguridad.
- `/desactivar`: Desactiva el sistema de seguridad.
- `/estado`: Consulta el estado actual del sistema (activado/desactivado).

### 📄 Licencia

Este proyecto se distribuye bajo la Licencia MIT. 

---

**¡Protege tu negocio con este sistema de seguridad inteligente y mantén el control desde la palma de tu mano!** 
