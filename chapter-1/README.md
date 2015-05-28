# Capítulo 1
En este capítulo se abordan diversos temas que van desde crear una ventana empleando GLFW, hasta desplegar primitivas básicas y una interfaz gráfica de usuario por pantalla. También se explican las nociones básicas de OpenGL enfocadas al despliegue 2D.

### Mi primera aplicación
Lo primero que se hace es incluir GLFW, después realizar su respectiva inicialización, crear una ventana y el contexto de OpenGL. Una vez hecho esto, se tiene que:

* Vincular todos los callbacks para el manejo de eventos (cambio de tamaño de ventana, movimiento del ratón, uso del teclado, entre otros).
* Ajustar el viewport al tamaño de la ventana.
* Crear el ciclo principal que contendrá (en respectivo orden):
  * Función de despliegue.
  * Cambio de buffer trasero (en donde se está haciendo el despliegue) con el delantero.
  * Envió de eventos a la cola del sistema operativo.

Para cerrar la aplicación simplemente se debe romper dicho ciclo y destruir la ventana y el contexto generado. 

### Creación de ventana y contexto
Para crear la ventana y vincularla con el contexto de OpenGL, se hará uso de GLFW. GLFW provee un conjunto de funciones que hacen este proceso realmente sencillo. Adicionalmente, como esta biblioteca es multiplataforma, no hay que preocuparse por el sistema operativo que se esté empleando.

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

Si GLFW inicia, la ventana es creada y vinculada con el contexto de OpenGL correctamente, se puede hacer uso de la ventana por medio del puntero `gWindow`, en caso contrario, la aplicación debe cerrarse.

### Eventos
GLFW provee una variedad de funciones para el manejo de eventos de ventanas, para esto, se debe seleccionar una función dependiendo del evento que se quiera controlar, posteriormente, se debe especificar la ventana y la función que lo maneja (`callback`). Los parametros formales de la función que maneja el evento estan relacionados con éste. Sin embargo, siempre se incluye un puntero a la ventana que afecta el evento.

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
Al iniciar la aplicación  se debe realizar la invocación de la función `initGlfw`, posteriormente se tiene que invocar una sola vez la función `reshape`, ya que se debe ajustar el viewport y la matriz de proyección al tamaño inicial de la ventana. Luego se carga la identidad a la matriz de modelo-vista (se explicará en el siguiente capítulo), a continuación se debe ejecutar el ciclo principal. 

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
OpenGL provee diversas primitivas 2D y 3D, por ahora se usaran únicamente las 2D (requiere vértices 2D) utilizando `glBegin` y `glEnd` (actualmente obsoleta por el gran gasto que genera el paso constante de los elementos entre CPU y GPU). Algunas de las primitivas más usadas son:

* Puntos `GL_POINTS`
* Líneas `GL_LINES`
* Triángulos `GL_TRIANGLES`
* Cuadriláteros `GL_QUADS`

Cada uno de estas primitivas reciben una serie de datos que corresponden a los puntos necesarios para formar dichos elementos. Por ejemplo para el triángulo se necesitan tres vértices. 
	
##### El orden importa

Es importante tomar en cuenta para las primitivas `GL_TRIANGLES` y `GL_QUADS` que a la hora de indicar los vértices que conforman a la primitiva el orden en que se realiza tiene importancia, y es que OpenGL a la hora de desplegar estas primitivas tiene en cuenta que poseen una cara trasera y una cara delantera. Una cara delantera se reconoce cuando el orden de los puntos es en contra de las agujas del reloj.

### Coordenadas de ventana
OpenGL no maneja la ventana como se está acostumbrado a manipularla, en pixeles. Internamente hace una correlación de las dimensiones a un rango entre [-1,1].

<p align="center">
  <img src ="http://s23.postimg.org/5yqdlxvp7/image.jpg" />
</p>

### Proporción y matriz de proyección 
Si se dibuja un cuadrado se puede notar que si se cambia el tamaño de la ventana pasa a ser un rectángulo. En la mayoría de los casos ese comportamiento es indeseado y se debe corregir. El problema es que no se le ha indicado a OpenGL como manipular las proporciones de nuestra ventana. 

Se puede corregir este problema de muchas maneras (unas más sofisticadas que otras), pero en este caso se empleara una matriz ortogonal como matriz de proyección, para esto primero debemos cargar la identidad y luego multiplicarla por la ortogonal. Para esto usamos la instrucción `glOrtho`.
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
Para mantenar una buena organización del código fuente, es recomendado trabajar de forma modular, razón por la cual se crea la clase figura `CFigure`, de esta pueden heredar un cojunto figuras (línea, cuadrilátero, triángulo, círculo, etc) ya que todas estas tienen atributos y metodos en común. Por razones de sencillez, en el tutorial solo se implementa línea `CLine` y cuadrilátero `CQuad`. A continuación se presenta el diagrama de clases. 
<p align="center">
  <img src ="http://s2.postimg.org/65p9a3qrt/3864fa76.png" />
</p>

De modo que podriamos agrupar todas las figuras en un vector `figures`, para luego, por ejemplo, en la función `display`, hacer lo siguiente.

```c++
vector <CFigure *> figures;

void display()
{
	// ...

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();
}
```

Cada figura define su propia forma de despliegue, donde se hace uso del bloque `glBegin` `glEnd`, para especificar la primitiva a usar y un conjunto de vertices, antes de esto, se puede cambiar el color con `glColor`. Por ejemplo la forma de despliegue de la línea es la siguiente.

```c++
void CLine::display()
{
	glColor3fv(mColor);

	glBegin(GL_LINES);
		glVertex2fv(mVertices[0]);
		glVertex2fv(mVertices[1]);
	glEnd();
}
```

### Interfaz gráfica de usuario
AntTweakBar define un conjunto de funciones básicas para su uso. En un comienzo se tiene que inicializar invocando a `TwInit`, luego se crean las interfaces que se deseen y en el ciclo principal se deben desplegar todas las interfaces creadas, esto se hace mediante la función `TwDraw`. Adicionalmente, para el manejo eventos, se deben invocar diversas funciones en los `callbacks` descritos anteriormente.

### Selección de figuras
Existen diversos métodos para lograr este objetivo, el más simple es empleando la caja envolvente de la figura. Donde se compara el punto donde se hizo click con los puntos extremos de la figura, es decir (Xmin, Ymin) y (Xmax, Ymax). Este proceso se tiene que repetir por cada figura que se este desplegando. 

```c++
int picked;

void pick(int x, int y)
{
	// ...
	
	for (int i = 0; i < figures.size(); i++)
	{
		float *v1 = figures[i]->getVertex(0);
		float *v2 = figures[i]->getVertex(1);
		float max[2];
		float min[2];

		// This should be precalculated

		max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);

		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			picked = i;

			// ...
		}
	}
}
```

### Requerimientos
* GLFW
* AntTweakBar

### Por hacer
- [x] Introducción :smile:
- [x] Diagrama de clases :sob:
- [x] Figuras :sweat:
- [x] Interfaz gráfica de usuario :smirk:
- [x] Selección de figuras :scream:
- [ ] Video tutorial :interrobang:
- [ ] Extras :alien:
