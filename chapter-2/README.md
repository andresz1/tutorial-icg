# Capítulo 2
En este capítulo se abordan diversos temas enfocados al despliegue 3D y se explican las funciones de OpenGL para poder llevar este proceso a cabo. Sin embargo, muchas de estas funciones se encuentran obsoletas, en el siguiente capitulos se verán las más recientes. 

### Despliegue

En informática gráfica, el despliegue se define como un proceso de generación de una imagen que representa a una escena, bien sea 2D o 3D, en un dispositivo de salida. Este proceso también se conoce con el nombre de *rendering*. Generalmente, las escenas están compuestas por un conjunto de modelos, estos se definen mediante archivos o por algoritmos que los generen. Dichas escenas suelen contener información de geometría, material, movimiento, ubicación espacial, entre otros, que lo describen. El conjunto de etapas que se realizan en dicho proceso es conocido como *pipeline gráfico*.

### Pipeline gráfico

La denominación pipeline hace referencia a que las etapas se encuentran secuenciadas y que el conjunto de ellas puede verse como una línea de producción de una fábrica. Cada operación corresponde a una estación de trabajo. Cada estación, o etapa, toma como entradas las salidas de la estación anterior, y produce salidas que sirven de entradas para la subsiguiente. Esta relación permite cierto grado de paralelismo. Las estaciones pueden estar todas trabajando simultáneamente si el pipeline es correctamente alimentado; claro esta, cada etapa sobre un conjunto de datos diferente.

El pipeline gráfico puede modelarse de manera genérica en tres etapas descritas a continuación: 
* Transformaciones
  * Mundo
  * Vista
  * Proyección
* Ensamblado, recorte y mapeo a pantalla
* Rasterización

### Matrices

#### Modelo

Se pueden aplicar varias transformaciones geométricas a un objeto utilizando matrices. Si se tiene que girar un objeto, se multiplican sus coordenadas por una matriz de rotación, lo mismo ocurre con la traslación y el escalamiento. El orden en que se aplican estas transformaciones es esencial. Se consiguen diferentes resultados si trasladamos y rotamos a un objeto, que si se empieza haciendo girar el objeto y luego se traslada el resultado.

Desde un punto de vista matemático, aplicar dos o más transformaciones a un objeto se puede hacer multiplicando las coordenadas del objeto con las matrices elementales una por una. Alternativamente, se puede utilizar una sola matriz, que contiene todas las transformaciones anteriores.

Las transformaciones básicas son:

##### Traslación (T)
##### Rotación (R)
##### Escalamiento (S)

Para generar la matriz de modelo correcta, se tendria que multiplicar en el siguiente orden las matrices anteriormente expuestas (M = T * R * S)

Tenga en cuenta que las matrices anteriores son 4x4 y no 3x3. Esto es porque la matriz de traslación no se puede escribir como una matriz 3x3 y usamos un truco matemático para expresar las transformaciones anteriores como multiplicaciones de matrices. Una consecuencia interesante de trabajar con matrices 4x4 en lugar de 3x3, es que no podemos multiplicar un vértice 3D, expresado como un vector columna 3x1, con las matrices anteriores. En su lugar vamos a utilizar las llamadas *coordenadas homogéneas*, donde un vértice 3D se puede expresar como un vector columna de 4x1. Desde nuestro punto de vista, esto simplemente significa que vamos a escribir un vértice 3D como:

#### Vista

Por defecto, en OpenGL, el espectador se coloca en el eje z, es como usar una cámara para tomar una foto. La cámara apunta al origen del sistema cartesiano. La dirección hacia arriba es paralela al eje Oy y en el sentido positivo de Oy.

La matriz de vista controla la manera en que vemos una escena. En este capítulo vamos a utilizar una matriz que simula una cámara en movimiento, por lo general llamado lookAt. Esta matriz es determinada por 3 parámetros:

* El ojo, o la posición del espectador;
* El centro, o el punto en el que la cámara tiene como objetivo;
* El up, que define la dirección de up para el espectador.

Los valores por defecto en OpenGL son: el ojo en (0, 0, -1); el centro en (0, 0, 0) y el up está dada por la dirección positiva del eje Oy (0, 1, 0).

La matriz de vista V, multiplica la matriz de modelo y, básicamente, se alinea el mundo (los objetos de una escena) a la cámara (MV = V * M)

```c++
int main(void)
{
  // ...
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  // ...
}
```

#### Proyección

Por defecto, en OpenGL, un objeto parecera tener el mismo tamaño, sin importar dónde se coloca la cámara. Esto va en contra de la experiencia cotidiana, donde un objeto más cercano a nosotros (a la cámara) se ve más grande que un objeto que se encuentra a una distancia mayor. 

Sin embargo, se puede ampliar o reducir el volumen de recorte a través del uso de una matriz de proyección, cuando el volumen de recorte tiene la forma de un paralelepípedo, o una caja, se dice que se emplea una proyección ortográfica. La proyección ortográfica no modificará el tamaño de los objetos, sin importar dónde se coloca la cámara. Esta es una característica deseable para los programas de CAD o para juegos 2D.

Otra matriz de proyección, que puede mejorar la sensación de mundo real, es la matriz de proyección en perspectiva, en este caso el volumen es un *frustum* y no un paralelepípedo.

La matriz de proyección de perspectiva se especifica generalmente a través de cuatro parámetros:

* Campo de visión (generalmente abreviado como *FOV*)
* Relación de aspecto
* Planos cerca y lejos (recorte)

La matriz de proyección P, multiplica el producto de la matriz de vista y la de modelo de modelo (MVP = P * V * M)

```c++
void reshape(GLFWwindow *window, int width, int height)
{
	// ...
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	// ...
}
```

### Modelos 3D

Un modelo 3D es la representación tridimensional de uno o varios objetos, el cual contiene información de geometría, conmumente vertices y caras. Adicionalmente un modelo 3D puede contener normales, coordenadas de texturas, tipo de material, etc. Dichos modelos pueden ser generador por algún algoritmo o estar distinguidos por un archivo. Existen varios formatos de archivo para representar modelos 3D. Unos de los formatos más conocidos y sencillos son el OFF y el OBJ.

En este tutorial se empleara una simplifación del formato OFF, llamado SOFF (creado para propositos de este tutorial). En el cual las caras siempre están compuestas por tres vertices que se encuentran especificados directamente, es decir, se podrian repetir.

A continuación se presenta un cubo en formato SOFF

```
SOFF
36
-1.0f -1.0f -1.0
-1.0f -1.0f 1.0f
-1.0f 1.0f 1.0f
1.0f 1.0f -1.0f
-1.0f -1.0f -1.0f
-1.0f 1.0f -1.0f
1.0f -1.0f 1.0f
-1.0f -1.0f -1.0f
1.0f -1.0f -1.0f
1.0f 1.0f -1.0f
1.0f -1.0f -1.0f
-1.0f -1.0f -1.0f
-1.0f -1.0f -1.0f
-1.0f 1.0f 1.0f
-1.0f 1.0f -1.0f
1.0f -1.0f 1.0f
-1.0f -1.0f 1.0f
-1.0f -1.0f -1.0f
-1.0f 1.0f 1.0f
-1.0f -1.0f 1.0f
1.0f -1.0f 1.0f
1.0f 1.0f 1.0f
1.0f -1.0f -1.0f
1.0f 1.0f -1.0f
1.0f -1.0f -1.0f
1.0f 1.0f 1.0f
1.0f -1.0f 1.0f
1.0f 1.0f 1.0f
1.0f 1.0f -1.0f
-1.0f 1.0f -1.0f
1.0f 1.0f 1.0f
-1.0f 1.0f -1.0f
-1.0f 1.0f 1.0f
1.0f 1.0f 1.0f
-1.0f 1.0f 1.0f
1.0f -1.0f 1.0f
```

Y su cargador

```c++
bool CSOff::load(string path)
{
	fstream file;
	string token;

	file.open(path, std::ios::in);

	file >> token;

	if (token != "SOFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;
		mNumOfVertices = 3 * atoi(token.c_str());
	
		mVertices = new float[mNumOfVertices];

		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> token;
			mVertices[i] = float(atof(token.c_str()));
		}
	
		file.close();
		return true;
	}
}
```

De forma similar al anterior cápitulo con las figuras, se puede crear la clase modelo `CModel`, de esta pueden heredar un cojunto de formatos de modelos (OFF, OBJ, 3DS, MDL, MD2, MD3, MD5, Collada, etc) ya que todas estas tienen atributos y metodos en común. De este modo se podrian agrupar todos los modelos en un vector `vector <CModel *> models` facilitando su manipulación. Como el metodo de carga varía según el formato, la clase modelo tiene un metodo virtual puro `load`. Sin embargo, el despliegue `display` suele ser el mismo, por lo tanto podría implementar en modelo.

```c++
void CModel::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < mNumOfVertices; i += 9)
	{
		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
			glVertex3f(mVertices[i + 3], mVertices[i + 4], mVertices[i + 5]);
			glVertex3f(mVertices[i + 6], mVertices[i + 7], mVertices[i + 8]);
		glEnd();
	}
}
```

En el metodo de despliegue se itera por cada cara del modelo, que se encuentra compuesta por tres vertices, que a su vez cada vertices se encuentra compuesto por tres coordenadas, y se dibuja empleando como primitiva triángulos.

Ahora en la funció de despliegue principal se debe hacer lo siguiente

```c++
glClearColor(0.0f, 0.0f, 0.0f, 1.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

for (int i = 0; i < models.size(); i++)
{	
	float *translation = models[i]->getTranslation();

	glPushMatrix();
		glTranslatef(translation[0], translation[1], translation[2]);
		models[i]->display();
	glPopMatrix();
}
```

En donde se recorre el vector de modelos, y por cada uno de ellos, se obtienen sus transformaciones asociadas, que van a ser aplicadas, en este caso se tiene unicamente traslanción, pero se podria tener tambien rotación y escalamiento. Como actualmente se tiene la matriz de modelo-vista asociada y adicionalmente la matriz de vista cargada en ésta, se debe salvaguardar el estado, ya que todos los modelos comparten la misma matriz de vista, para esto, empleamos la función `glPushMatrix()` que guarda en una pila el estado de la matriz asociada al momento de ser invocada. Una vez hecho esto, se aplican todas las transformaciones en el orden explicado anteriormente y luego se reestable el estado de la matriz `glPopMatrix()`, para continuar con el proceso.

### Requerimientos
* GLFW
* AntTweakBar
