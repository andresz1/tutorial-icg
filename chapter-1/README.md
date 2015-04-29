# Capítulo 1
En este capítulo se abordan diversos de temas que van desde crear una ventana empleando GLFW, hasta desplegar primitivas básicas y una interfaz gráfica de usuario por pantalla. También se explican diversas nociones básicas de OpenGL enfocadas al despliegue 2D.

### Mi primera aplicación
Lo primero que se tiene que hacer es incluir GLFW, después realizar su respectiva inicialización, crear una ventana y el contexto de OpenGL. Una vez hecho esto, tenemos que:

* Vincular todos los callbacks para el manejo de eventos (cambio de tamaño de ventana, movimiento del ratón, uso del teclado, entre otros).
* Ajustar el viewport al tamaño de la ventana.
* Crear el ciclo principal que contendrá (en respectivo orden):
  * Función de despliegue.
  * Cambio de buffer trasero (en donde se está haciendo el despliegue) con el delantero.
  * Envió de eventos a la cola del sistema operativo.

Para cerrar la aplicación simplemente se debe romper dicho ciclo y destruir la ventana y el contexto generado. 

### Creación de ventana y contexto
Para crear la ventana y vincularla con el contexto de OpenGL, se hará uso de GLFW. GLFW provee un conjunto de funciones que hacen este proceso realmente sencillo. Adicionalmente, como esta biblioteca es multiplataforma no hay que preocuparse por el sistema operativo que se esté empleando.

```c++
GLFWwindow *gWindow;

bool initGlfw()
{
  if (!glfwInit())
  	return false;
  
  gWindow = glfwCreateWindow(gWidth, gHeight, "Chapter 1", NULL, NULL);
  
  if (!gWindow)
  {
  	glfwTerminate();
  	return false;
  }
  
  glfwMakeContextCurrent(gWindow);
  
  // ...
}
```

Si GLFW inicia, la ventana es creada y vinculada con el contexto de OpenGL correctamente, podremos hacer uso de la ventana por medio del puntero `gWindow`, en caso contrario, la aplicación debe cerrarse.

### Eventos
GLFW provee una variedad de funciones para el manejo de eventos de ventanas, para esto, se debe seleccionar una función dependiendo del evento que se quiera controlar, posteriormente, se debe especificar la ventana y la función que lo maneja. Los parametros formales de la función que maneja el evento estan relacionados con este. Sin embargo, siempre se incluye un puntero a la ventana que afecta el evento.

```c++
GLFWwindow *gWindow;

bool initGlfw()
{
  // ...
    
  glfwSetWindowSizeCallback(gWindow, reshape);
  glfwSetKeyCallback(gWindow, keyInput);
  glfwSetMouseButtonCallback(gWindow, mouseButton);
  glfwSetCursorPosCallback(gWindow, cursorPos);
  glfwSetCharCallback(gWindow, charInput);
  
  return true;
}
```

#### Tecla presionada
Al ser presionada una tecla, la función `keyInput` sera invocada.
```c++
void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  // ...
}
```

#### Ratón presionado
Al ser presionado un boton del ratón, la función `mouseButton` sera invocada.
```c++
void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
  // ...
}
```

#### Movimiento del ratón
Al mover el ratón, la función `cursorPos` sera invocada.
```c++
void cursorPos(GLFWwindow* window, double x, double y)
{
  // ...
}
```

#### Cambio de tamaño
Al cambiar el tamaño de la ventana, la función `reshape` sera invocada, en este caso, unicamente se debe actualizar el valor de la variables del ancho y el alto, ajustar el tamaño del viewport y modificar la matriz de proyección. El viewport es el lienzo empleado por OpenGL para reflejar el despliegue final de la escena, usualmente se ajusta al tamaño de la ventana, como se muestra a continuación.

```c++
void reshape(GLFWwindow *window, int width, int height)
{
  gWidth = width;
  gHeight = height;
  
  glViewport(0, 0, gWidth, gHeight);
  
  // Modificar la matriz de proyección
}
```

#### Inicio y ciclo principal
Al iniciar la aplicación  se debe realizar la invocación de la función `initGlfw`, posteriormente se tiene que invocar una sola vez la función `reshape`, ya que se debe ajustar el viewport y la matriz de proyección al tamaño inicial de la ventana. Luego cargamos la identidad a la matriz de modelo-vista (se explicará en el siguiente capítulo), a continuación se debe ejecutar el ciclo principal. 

En el ciclo principal se llama a la función de despliegue `display`, se cambia al buffer trasero (en donde se está haciendo el despliegue) con el delantero `glfwSwapBuffers(gWindow)` para que no se perciba el cambio entre el cuadro (en ingles, frame) viejo y el nuevo y se envian los eventos a la cola del sistema operativo `glfwPollEvents()`.

```c++
int main(void)
{
  // ...
  
  if (!initGlfw())
  	return EXIT_FAILURE;
  
  reshape(gWindow, gWidth, gHeight);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  while (!glfwWindowShouldClose(gWindow))
  {
  	display();
  
  	updateUserInterface();
  
  	glfwSwapBuffers(gWindow);
  
  	glfwPollEvents();
  }
  
  destroy();
  
  return EXIT_SUCCESS;
}
```

### Función de despliegue
Esta función es donde se despliegan todos los elementos que se deseen y se va a estar llamando constantemente desde el ciclo principal, contendrá por ahora en este orden las siguientes acciones:

* Elegir un color para limpiar la pantalla `glClearColor`.
* Limpiar el buffer de color `glClear(GL_COLOR_BUFFER_BIT)`.
* Despliegue de elementos (en este caso primitivas 2D).

```c++
void display()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Despliegue
}
```

### Primitivas
OpenGL nos provee de diversas primitivas 2D y 3D, por ahora usaremos únicamente las 2D (requiere vértices 2D) utilizando `glBegin` y `glEnd` (actualmente obsoleta por el gran gasto que genera el paso constante de los elementos entre CPU y GPU). Algunas de las primitivas más usadas son:

* Puntos `GL_POINTS`
* Líneas `GL_LINES`
* Triángulos `GL_TRIANGLES`
* Cuadriláteros `GL_QUADS`

Cada uno de estas primitivas reciben una serie de datos que corresponden a los puntos necesarios para formar dichos elementos. Por ejemplo para el triángulo se necesitan tres vértices. 
	
##### El orden importa

Es importante tomar en cuenta para las primitivas `GL_TRIANGLES` y `GL_QUADS` que a la hora de indicar los vértices que conforman a la primitiva el orden en que se realiza tiene importancia, y es que OpenGL a la hora de desplegar estas primitivas tiene en cuenta que poseen una cara trasera y una cara delantera. Una cara delantera se reconoce cuando el orden de los puntos es en contra de las agujas del reloj.

### Coordenadas de ventana
OpenGL no maneja la ventana como estamos acostumbrados a manipularlas, en pixeles. Internamente hace una correlación de las dimensiones a un rango entre [-1,1].

<p align="center">
  <img src ="http://s23.postimg.org/5yqdlxvp7/image.jpg" />
</p>

### Proporción y matriz de proyección 
Si se dibujam un cuadrado se puede notar que si se cambia el tamaño de la ventana deja de ser un cuadrado y pasa a ser un rectángulo. En la mayoría de los casos ese comportamiento es indeseado y debemos corregirlo. El problema es que no le hemos indicado a OpenGL como manipular las proporciones de nuestra ventana. 

Podemos corregir este problema de muchas maneras (unas más sofisticadas que otras), pero en este caso utilizaremos una matriz ortogonal como matriz de proyección, para esto primero debemos cargar la identidad y luego multiplicarla por la ortogonal. Para esto usamos la instrucción `glOrtho`.
Como se explicó anteriormente, dicha instrucción depende del tamaño de la ventana y se debe efectuar cada vez que su dimensión cambie.

<p align="center">
  <img src ="http://s7.postimg.org/v3oziu1a3/image.jpg" />
</p>

```c++
void reshape(GLFWwindow *window, int width, int height)
{
  // ...
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}
```

### Figuras
Para mantenar una buena organización del código fuente, es recomendado trabajar de forma modular, razón por la cual se crea la clase Figura. 
<p align="center">
  <img src ="http://s2.postimg.org/65p9a3qrt/3864fa76.png" />
</p>

### Requerimientos
* GLFW
* AntTweakBar

### Por hacer
- [x] Introducción :smile:
- [ ] Diagrama de clases :sob:
- [ ] Figuras :sweat:
- [ ] Interfaz gráfica de usuario :smirk:
- [ ] Selección de figuras :scream:
