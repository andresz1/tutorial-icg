# Capítulo 3

### Shader

La tecnología shaders o sombreadores es cualquier unidad escrita en un lenguaje de sombreado que se puede compilar independientemente. Es una tecnología reciente y que ha experimentado una gran evolución destinada a proporcionar al programador una interacción con la unidad de procesamiento gráfico (GPU) hasta ahora imposible. Los shaders son utilizados para realizar transformaciones y crear efectos especiales, como por ejemplo iluminación, fuego o niebla. Para su programación los shaders utilizan lenguajes específicos de alto nivel que permitan la independencia del hardware.

### Lenguajes de sombreado

Para la escritura de esas instrucciones, los programadores hacen uso de lenguajes de programación diseñados específicamente para ello. Cada uno de estos lenguajes de programación necesita enlazarse mediante una API, entre otras DirectX u OpenGL. Existen otros lenguajes pero los siguientes son los más conocidos.
  * CG
  * HLSL
  * GLSL

### GLSL 

Es el lenguaje desarrollado por el grupo Khronos. Está diseñado específicamente para su uso dentro del entorno de OpenGL. Sus diseñadores afirman que se ha hecho un gran esfuerzo para lograr altos niveles de paralelismo. Su diseño se basa en C y RenderMan como modelo de lenguaje de sombreado.

### Pipeline de despliegue de OpenGL

En el cápitulo anterior se describío como se puede modelar de manera genérica el pipeline, a continuación se describe especificamente el pipeline de despliegue de OpenGL.

<p align="center">
  <img src ="http://3dgep.com/wp-content/uploads/2014/01/OpenGL-4.0-Programmable-Shader-Pipeline1.png" />
</p>

En la actualidad diversas etapas del pipeline mostrado en la figura anterior, son programables, es decir

### Requerimientos
* GLFW
* AntTweakBar
* GLEW
* GLM
