# Pina Yoryi 🍍

Piña Motor es un motor de videojuegos en tres dimensiones multipropósito, que utiliza el motor gráfico de [OGRE](#RENDERIZADO), el motor físico de [BULLET](#BULLET) y el motor de audio de [FMOD](#FMOD)

## Comenzando 🚀

Existe una única instancia de Input en el motor, utilizando el patrón de Singleton.

**E/S**

Detectamos la entrada de tanto teclado como ratón mediante _SDL_. 

**LECTURA ARCHIVOS**

Utilizamos _LUA_ para la lectura de los archivos: mapas, audio, etc para posteriormente pasar los datos al núcleo del motor.

**GRÁFICOS**

Usamos _Ogre_ para renderizar los gráficos generados e imágenes. 

**ENTIDADES**:

Unidad Objeto Motor. Tienen una lista de componentes que les dan comportamiento (y un componente forzado: _Transform_); interacción con el loop del juego, que hacen que itere por todos los componentes que tenga añadidos llamando a sus respectivos métodos.

**COMPONENTES**: 

El motor está estructurado en entidades y componentes. Las entidades son objetos sin función que lo que hacen es llamar a su lista de componentes. Los componentes son clases con funciones que se asignan a las entidades.

* TRANSFORM: Manejo de posición, rotación y escala de las entidades. Tiene métodos para mover, rotar y escalar. Las entidades comienzan con este componente incluido al crearlas. Asociado al _Parent_.

* UITRANSFORM: Componente exclusivo de _Transform_ (2D) utilizado para incluir entidades en la interfaz de usuario. Hereda todas las funcionalidades descritas y sirve para que se coloque desde ese punto relativo de la pantalla. Los atributos tienen como unidades los píxeles de la pantalla o, en caso del ancla, están normalizadas, de forma que (0,0) está en la esquina inferior izquierda.

* RIGIDBODY: Determina si la _Entidad_ es afectada por la físicas (_Bullet_): velocidades y aceleraciones (fuerzas, graviedad y fricción); dependiente de _Transform_.

* RENDERER: Comunica con _Ogre_ y renderiza mallas y texturas; actualizado frame a frame. Dependiente de _Transform_. 

* COLISIÓN: Interfaz del sistema de colisiones de _Bullet_. Si intersección: se hacen llamadas a los métodos de colisión o activador en ambas entidades. Depende de _Transform_. 

* IA: La tenencia de este componente dota a la entidad de la _IA_ básica del motor. Depende de _Transform_, _Rigidbody_. Tiene atributos para la velocidad de rotación, de movimiento, aceleración angular y lineal.

* CÁMARA: Muestra el mundo. Depende de _Transform_. La posición (0,0) de la cámara se corresponde con la posición de arriba a la izquierda de la pantalla. Se puede modificar su viewport y su resolución.

* TEXTO: Renderiza cualquier cadena de caracteres que quieras en la posición que quieras. Forma parte de la interfaz de usuario. Se puede modificar su fuente, tamaño, color tanto de los caracteres como del resaltado y alineación (izquierda, central o derecha).

* IMAGEN: Renderiza una imagen. Se puede modificar su tamaño y posición. Acepta diversos formatos como _.png_ y _.jpg_.

* ANIMACIÓN: Se encarga de realizar las animaciones que se quiera. Se da la opción de transicionar entre diferentes animaciones que previamente se han creado, realizarse en bucle o una sola vez, elegir la animación por defecto y parar de animar.

* DROPDOWN: Depende de _Transform_ y _Renderer_. Detecta eventos de teclado o ratón; es un desplegable tipo lista de botones.

*BOTÓN : Parte de la interfaz de usuario. Depende de _UITransform_ y Renderer. Detecta eventos de teclado o ratón.

* SISTEMA DE PARTÍCULAS: Se da la opción de crear un sistema de partícula a partir de un archivo _.particle_.

* AUDIO SOURCE: Carga un archivo de audio y, utilizando _FMOD_, lo reproduce según diferentes atributos: espacial o global, volumen de reproducción, loop, etc. Tiene métodos de acceso y modificación de sus atributos.

* AUDIO LISTENER: Utiliza la posición de Transform para averiguar si debe escuchar o no los diferentes sonidos que se crean en sus posiciones. Los sonidos globales los escucha siempre que estén reproduciendo.

* LIGHT: Uso de _OGRE_. Permite seleccionar el tipo de luz: direccional, de punto, foco…, la intensidad, color, sombras que genera.

**ESCENAS**

Son una lista de entidades con una jerarquía de Padre-Hijo, un mundo físico y una serie de objetos que se encargan de ser una interfaz con el motor, como Input o SceneManager. 

**SCENEMANAGER**

Es un objeto, al igual que Input, es un Singleton. Tiene métodos para cargar y descargar escenas. Tiene dos listas con las entidades que hay en la escena, la diferencia entre éstas es que una lista guarda las entidades que no hay que borrar cuando se cambia entre escenas.

**LUA**

Usamos lenguaje LUA para interpretar los distintos niveles de cada videojuego. Usaremos el intérprete de _LUA 5.4.2_  para interpretar las escenas codificadas y cargarlas en tiempo de ejecución. El formato de los archivos de escena utiliza el estándar _JSON_, con objetos _JavaScript_ para representar las entidades de la escena.

**PREFAB**

Los prefabs son como una escena que no tienen las propiedades de la misma, y son solamente una entidad. Tienen una **id** única por tipo de prefab que se puede usar para referenciarlos entre prefabs o entidades de escenas.

**IA**

Codificamos nuestra inteligencia artificial integrada en el motor, para dotar de comportamientos básicos de inteligencia a las entidades mediante componentes que tienen desarrollados dichos comportamientos.

**TRASLADARSE SIN PATHFINDER**

Permite trasladar a la entidad que se quiera de un punto a otro, aunque solo se da la opción de ser en línea recta, sin evitar obstáculos. Dadas las dos posiciones, encuentra el vector dirección y se mueve en dicho sentido a una velocidad.

**ORIENTARSE**

Permite orientar a la entidad que se quiera para que mire a un punto concreto. Dada una velocidad máxima de rotación, calcula cuánto ha de girarse y realiza el giro durante el periodo de tiempo apropiado.

**LOOP**

Es el bucle principal que hay en el motor. _Input-Fixed_ _Update-Update-Render_. Este bucle recorre todas las entidades invocando a sus respectivos métodos con el mismo nombre.

**START**

A este método se le llama la primera vez que se instancia un componente. Cada componente tiene su propio método Start y son independientes entre sí.

**INPUT**
Este método es privado para los desarrolladores que utilicen el motor, se encarga de actualizar las estructuras de entrada que proporciona el motor al desarrollador. Se llama una vez en cada frame para detectar si hay input.

**UPDATE**

A este método se le llama una vez cada frame a cada entidad de la escena, y estas a cada componente suyo, actualizando sus valores conforme pasa el tiempo y las entidades actúan.

**FIXED UPDATE**

Es una actualización que ocurre tras una cierta cantidad de tiempo real fija; lo que implica que puede ocurrir en un rango de cero a varias veces en un frame. Este método es recomendable utilizarlo para actualizaciones físicas, o actualizaciones que ocurran cada cierto tiempo real.

**RENDER**
Este método se llama una vez cada frame, y es privado para el desarrollador del motor. Se encarga de hacer llamadas al motor gráfico renderizando todos los objetos de la escena.

**INTERFAZ**

El motor permite crear elementos que existan fuera de la escena, en una interfaz, haciendo que de esta forma se encuentren siempre en la cámara superpuestas a los demás elementos.

**FÍSICA**

Usamos una librería externa de física, que va a tratar los eventos relacionados con aceleraciones, inercias, momentos, detección de colisiones, etc. Usando una librería nos aseguramos de que los cálculos físicos son correctos y están unificados y son compatibles entre sí. Decidimos usar [Bullet v3.0.9](https://github.com/bulletphysics/bullet3/releases).

**BULLET** <a name="BULLET"></a> 

Bullet es la librería más conveniente para este motor debido a que es efectiva, habiendo sido usada con éxito en grandes proyectos como Blender y es software libre de código abierto que además es relativamente sencillo de implementar

**AUDIO** <a name="FMOD"></a> 

La librería externa de audio que da soporte a diferentes extensiones, más de una pista de audio, a cargar, reproducir, pausar y parar el o los audios que están sonando. La librería a usar es FMOD que es la que más nos conviene para este proyecto porque, al igual que Bullet, es software libre y gratuito, que nos facilita la implementación de sonidos en el motor.

* FMOD: Se utilizará porque reproduce y mezcla sonidos de diversos formatos en varios sistemas operativos.  Su licencia permite que el software no destinado a la distribución comercial utilice FMOD de forma gratuita, al igual que Ogre y Bullet, lo cual es conveniente para este proyecto.

**RENDERIZADO**

Para el renderizado en pantalla de las entidades y efectos se va a usar una vez más una librería externa. Por motivos similares a los casos anteriores, vamos a usar [_OGRE_](https://www.ogre3d.org/) por su versatilidad y por ser de uso gratuito en el caso de este proyecto.

* OGRE
Ogre (es la base del motor, se encarga de la parte gráfica de este) es un motor gráfico en tres dimensiones que permite la integración de otras librerías ajenas a este. A pesar de ser puramente un motor de renderizado, cuenta con características convenientes, como clases propias de vectores y matrices, por ejemplo, manejo de memoria, etc.

* SDL
Ogre incluye la librería de [SDL2](https://www.libsdl.org/), que aparte de ser necesaria para Ogre también se utilizará, por ejemplo, para tratar los inputs del motor.


### Pre-requisitos 📋

_Que cosas necesitas para instalar el software y como instalarlas_

```
Da un ejemplo
```

### Instalación 🔧

_Una serie de ejemplos paso a paso que te dice lo que debes ejecutar para tener un entorno de desarrollo ejecutandose_

_Dí cómo será ese paso_

```
Da un ejemplo
```

_Y repite_

```
hasta finalizar
```

_Finaliza con un ejemplo de cómo obtener datos del sistema o como usarlos para una pequeña demo_

## Ejecutando las pruebas ⚙️

_Explica como ejecutar las pruebas automatizadas para este sistema_

### Analice las pruebas end-to-end 🔩

_Explica que verifican estas pruebas y por qué_

```
Da un ejemplo
```

### Y las pruebas de estilo de codificación ⌨️

_Explica que verifican estas pruebas y por qué_

```
Da un ejemplo
```

## Despliegue 📦

_Agrega notas adicionales sobre como hacer deploy_

## Construido con 🛠️

_Menciona las herramientas que utilizaste para crear tu proyecto_

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - El framework web usado
* [Maven](https://maven.apache.org/) - Manejador de dependencias
* [ROME](https://rometools.github.io/rome/) - Usado para generar RSS

## Contribuyendo 🖇️

Por favor lee el [CONTRIBUTING.md](https://gist.github.com/villanuevand/xxxxxx) para detalles de nuestro código de conducta, y el proceso para enviarnos pull requests.

## Wiki 📖

Puedes encontrar mucho más de cómo utilizar este proyecto en nuestra [Wiki](https://github.com/tu/proyecto/wiki)

## Versionado 📌

Usamos [SemVer](http://semver.org/) para el versionado. Para todas las versiones disponibles, mira los [tags en este repositorio](https://github.com/tu/proyecto/tags).

## Autores ✒️

_Menciona a todos aquellos que ayudaron a levantar el proyecto desde sus inicios_

* **Andrés Villanueva** - *Trabajo Inicial* - [villanuevand](https://github.com/villanuevand)
* **Fulanito Detal** - *Documentación* - [fulanitodetal](#fulanito-de-tal)

También puedes mirar la lista de todos los [contribuyentes](https://github.com/your/project/contributors) quíenes han participado en este proyecto. 

## Licencia 📄

Este proyecto está bajo la Licencia (Tu Licencia) - mira el archivo [LICENSE.md](LICENSE.md) para detalles

