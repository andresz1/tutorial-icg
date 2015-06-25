# Capítulo 3

### Shader

Un shader o sombreador es cualquier unidad escrita en un lenguaje de sombreado que se puede compilar independientemente. Es una tecnología reciente y que ha experimentado una gran evolución destinada a proporcionar al programador una interacción con la unidad de procesamiento gráfico (GPU) hasta ahora imposible. Los shaders son utilizados para realizar transformaciones y crear efectos especiales. Para su programación los shaders utilizan lenguajes específicos de alto nivel que permitan la independencia del hardware.

### GLSL 

Es un lenguaje de sombreado desarrollado por el grupo Khronos. Está diseñado específicamente para su uso dentro del entorno de OpenGL. Sus diseñadores afirman que se ha hecho un gran esfuerzo para lograr altos niveles de paralelismo. Su diseño se basa en C y RenderMan.

### Pipeline de despliegue de OpenGL

En el cápitulo anterior se describío como se puede modelar de manera genérica el pipeline, a continuación se describe especificamente el pipeline de despliegue de OpenGL.

<p align="center">
  <img src ="http://3dgep.com/wp-content/uploads/2014/01/OpenGL-4.0-Programmable-Shader-Pipeline1.png" />
</p>

Diversas etapas del pipeline mostrado en la figura anterior, son programables, se listan a continuación.

* Vertex Shader

* Tessellation Control Shader

* Tessellation Evaluation Shader

* Geometry Shader

* Fragment Shader

Sin embargo, en este capítulo nos concentraremos unicamente en las siguientes etapas.

* Vertex Shader: También conocido como procesador de vertices, se encarga de llevar a cabo todas las operaciones sobre los vértices pertenecientes a los modelos que componen una escena dentro de una aplicación.

* Fragment Shader: En este shader es donde el programador tiene control total sobre cada uno de los fragmentos de la pantalla y toma la decisiones acerca de que color va a tener cada uno de ellos.

Una vez que se haya decidido cuales etapas se van a manejar, se deben tomar cada uno de estos shaders asociados a dichas etapas escritos en GLSL, para cargarlos en la aplicación como un `string`, compilarlos y adjuntarselos a un programa que será el que posteriormente enlazaremos dentro de nuestra aplicación, para enviar los datos al pipeline gráfico. La clase encargada de representar al programa se llama `CGLSLProgram`.

Inicialización
```c++
bool initGlew()
{
  // ...
  
  glslProgram = new CGLSLProgram();
  glslProgram->loadFromFile("../shaders/Color.vert");
  glslProgram->loadFromFile("../shaders/Color.frag");
  glslProgram->create();
  glslProgram->loadUniformVariables();
  glslProgram->loadAttributeVariables();
  
  // ...
}
```

Uso
```c++
void display()
{
  // ...
  
  glslProgram->enable();
  
    // ...
    
  glslProgram->disable();
  
  // ...
}
```
### Requerimientos
* GLFW
* AntTweakBar
* GLEW
* GLM
