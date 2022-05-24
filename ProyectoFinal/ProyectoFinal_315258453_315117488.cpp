#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "modelAnim.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();
void Sali();
void recorridoS();
void recorridoS2();
void recorrido3S();

// Window dimensions
const GLuint WIDTH = 1366, HEIGHT = 780;
int SCREEN_WIDTH, SCREEN_HEIGHT;

/*--------------------Posicion de la camara----------------------------*/

Camera  camera(glm::vec3(100.0f, 30.0f, 50.0f));

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float puerta = 0.0f;
float tiempo;
float rot1 = 0.0f;
float rot2 = 0.0f;
float mov1 = 0.0f;
bool anim = false;
bool anim1 = false;
bool anim2 = false;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni1(0.0f,0.0f,0.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;

//Recorridos

float movKitXa = 0.0;
float movKitZa = 0.0;
float rotKita = 0.0;

bool circuitoa = false;
bool recorridoa1 = true;
bool recorridoa2 = false;
bool recorridoa3 = false;
bool recorridoa4 = false;
bool recorridoa5 = false;

float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;

float movKitXb = 0.0;
float movKitZb = 0.0;
float rotKitb = 0.0;

bool circuitob = false;
bool recorridob1 = true;
bool recorridob2 = false;
bool recorridob3 = false;
bool recorridob4 = false;
bool recorridob5 = false;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

GLfloat deltaTime1 = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame1 = 0.0f;  	// Time of last frame



// Keyframes
float posX =PosIni.x, posY = PosIni.y, posZ = PosIni.z, posX1 = PosIni1.x, posY1 = PosIni1.y, posZ1 = PosIni1.z, rotRodIzq = 0, rotRodDer, rotBraDer, rotBraIzq, rot1RodIzq = 0, rot1RodDer, rot1BraDer, rot1BraIzq;

#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
int i_max_steps1 = 190;
int i_curr_steps1 = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ

	float rotRodIzq;
	float rotInc;

	float rotRodDer;
	float rotInc2;

	float rotBraIzq;
	float rotInc3;

	float rotBraDer;
	float rotInc4;

	float posX1;		//Variable para PosicionX
	float posY1;		//Variable para PosicionY
	float posZ1;		//Variable para PosicionZ
	float incX1;		//Variable para IncrementoX
	float incY1;		//Variable para IncrementoY
	float incZ1;		//Variable para IncrementoZ

	float rot1RodIzq;
	float rot1Inc;

	float rot1RodDer;
	float rot1Inc2;

	float rot1BraIzq;
	float rot1Inc3;

	float rot1BraDer;
	float rot1Inc4;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
FRAME KeyFrame1[MAX_FRAMES];
int FrameIndex = 0;	
int FrameIndex1 = 0;	
bool play = false;
int playIndex = 0;
int playIndex1 = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0,0,0),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0)
};

glm::vec3 LightP1;
glm::vec3 LightP2;
glm::vec3 LightP3;
glm::vec3 LightP4;

/*--------------------------------Aqui esta la animacion por keyframes-------------------------------*/

void Sali(void) {

	KeyFrame[0].posZ = -1;
	KeyFrame[0].incX = 0;
	KeyFrame[0].incY = 0;
	KeyFrame[0].incZ = 0;

	KeyFrame[0].rotRodIzq = -20;
	KeyFrame[0].rotInc = 0;
	KeyFrame[0].rotRodDer = 20;
	KeyFrame[0].rotInc2 = 0;
	KeyFrame[0].rotBraIzq = 20;
	KeyFrame[0].rotInc3 = 0;
	KeyFrame[0].rotBraDer = -20;
	KeyFrame[0].rotInc4 = 0;

	FrameIndex = 0;
	i_curr_steps = 0;

	KeyFrame[1].posZ = 1;
	KeyFrame[1].incX = 0;
	KeyFrame[1].incY = 0;
	KeyFrame[1].incZ = 0;

	KeyFrame[1].rotRodIzq = 20;
	KeyFrame[1].rotInc = 0;
	KeyFrame[1].rotRodDer = -20;
	KeyFrame[1].rotInc2 = 0;
	KeyFrame[1].rotBraIzq = -20;
	KeyFrame[1].rotInc3 = 0;
	KeyFrame[1].rotBraDer = 20;
	KeyFrame[1].rotInc4 = 0;

	FrameIndex = 1;
	i_curr_steps = 1;
	
	KeyFrame[2].posZ = -1;
	KeyFrame[2].incX = 0;
	KeyFrame[2].incY = 0;
	KeyFrame[2].incZ = 0;

	KeyFrame[2].rotRodIzq = -20;
	KeyFrame[2].rotInc = 0;
	KeyFrame[2].rotRodDer = 20;
	KeyFrame[2].rotInc2 = 0;
	KeyFrame[2].rotBraIzq = 20;
	KeyFrame[2].rotInc3 = 0;
	KeyFrame[2].rotBraDer = -20;
	KeyFrame[2].rotInc4 = 0;

	FrameIndex = 2;
	i_curr_steps = 2;

	KeyFrame[3].posZ = 1;
	KeyFrame[3].incX = 0;
	KeyFrame[3].incY = 0;
	KeyFrame[3].incZ = 0;

	KeyFrame[3].rotRodIzq = 20;
	KeyFrame[3].rotInc = 0;
	KeyFrame[3].rotRodDer = -20;
	KeyFrame[3].rotInc2 = 0;
	KeyFrame[3].rotBraIzq = -20;
	KeyFrame[3].rotInc3 = 0;
	KeyFrame[3].rotBraDer = 20;
	KeyFrame[3].rotInc4 = 0;

	FrameIndex = 3;
	i_curr_steps = 3;

	KeyFrame[4].posZ = -1;
	KeyFrame[4].incX = 0;
	KeyFrame[4].incY = 0;
	KeyFrame[4].incZ = 0;

	KeyFrame[4].rotRodIzq = -20;
	KeyFrame[4].rotInc = 0;
	KeyFrame[4].rotRodDer = 20;
	KeyFrame[4].rotInc2 = 0;
	KeyFrame[4].rotBraIzq = 20;
	KeyFrame[4].rotInc3 = 0;
	KeyFrame[4].rotBraDer = -20;
	KeyFrame[4].rotInc4 = 0;

	FrameIndex = 4;
	i_curr_steps = 4;

	KeyFrame[5].posZ = 1;
	KeyFrame[5].incX = 0;
	KeyFrame[5].incY = 0;
	KeyFrame[5].incZ = 0;

	KeyFrame[5].rotRodIzq = 20;
	KeyFrame[5].rotInc = 0;
	KeyFrame[5].rotRodDer = -20;
	KeyFrame[5].rotInc2 = 0;
	KeyFrame[5].rotBraIzq = -20;
	KeyFrame[5].rotInc3 = 0;
	KeyFrame[5].rotBraDer = 20;
	KeyFrame[5].rotInc4 = 0;

	FrameIndex = 5;
	i_curr_steps = 5;

	KeyFrame[6].posZ = -1;
	KeyFrame[6].incX = 0;
	KeyFrame[6].incY = 0;
	KeyFrame[6].incZ = 0;

	KeyFrame[6].rotRodIzq = -20;
	KeyFrame[6].rotInc = 0;
	KeyFrame[6].rotRodDer = 20;
	KeyFrame[6].rotInc2 = 0;
	KeyFrame[6].rotBraIzq = 20;
	KeyFrame[6].rotInc3 = 0;
	KeyFrame[6].rotBraDer = -20;
	KeyFrame[6].rotInc4 = 0;

	FrameIndex = 6;
	i_curr_steps = 6;

	KeyFrame[7].posZ = 1;
	KeyFrame[7].incX = 0;
	KeyFrame[7].incY = 0;
	KeyFrame[7].incZ = 0;

	KeyFrame[7].rotRodIzq = 20;
	KeyFrame[7].rotInc = 0;
	KeyFrame[7].rotRodDer = -20;
	KeyFrame[7].rotInc2 = 0;
	KeyFrame[7].rotBraIzq = -20;
	KeyFrame[7].rotInc3 = 0;
	KeyFrame[7].rotBraDer = 20;
	KeyFrame[7].rotInc4 = 0;
	FrameIndex = 7;
	i_curr_steps = 7;

	KeyFrame[8].posZ = -1;
	KeyFrame[8].incX = 0;
	KeyFrame[8].incY = 0;
	KeyFrame[8].incZ = 0;

	KeyFrame[8].rotRodIzq = -20;
	KeyFrame[8].rotInc = 0;
	KeyFrame[8].rotRodDer = 20;
	KeyFrame[8].rotInc2 = 0;
	KeyFrame[8].rotBraIzq = 20;
	KeyFrame[8].rotInc3 = 0;
	KeyFrame[8].rotBraDer = -20;
	KeyFrame[8].rotInc4 = 0;
	FrameIndex = 8;
	i_curr_steps = 8;

}



void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex1);
	
	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	
	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotBraIzq = rotBraIzq;
	KeyFrame[FrameIndex].rotBraDer = rotBraDer;

	FrameIndex++;

}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;

	rotBraIzq = KeyFrame[0].rotBraIzq;
	rotBraDer = KeyFrame[0].rotBraDer;
}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;

}




int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3125258453_315117488_ProyectoFinal", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*__________________________Shaders_________________________________*/

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");
	Shader animShader2("Shaders/anim2.vs", "Shaders/anim2.frag");

	/*---------------------------Animales------------------------------*/

	Model Head((char*)"Models/Braq/Head.obj");
	Model Body((char*)"Models/Braq/Body.obj");
	Model L_braq((char*)"Models/Braq/L_braq.obj");
	Model LB_braq((char*)"Models/Braq/LB_braq.obj");
	Model R_braq((char*)"Models/Braq/R_braq.obj");
	Model RB_braq((char*)"Models/Braq/RB_braq.obj");
	
	Model BbocaRex((char*)"Models/Rex/source1/BbocaRex.obj");
	Model BodyRex((char*)"Models/Rex/source1/BodyRex.obj");

	Model BodyH((char*)"Models/Indo/Body_H.obj");
	Model R_ArmH((char*)"Models/Indo/R_ArmH.obj");
	Model L_ArmH((char*)"Models/Indo/L_ArmH.obj");

	Model Acuatico((char*)"Models/DinoAgua/DinoAgua.obj");
	/*------------------------Ambientacion------------------------*/

	Model Agua((char*)"Models/Sea/Sea.obj");
	Model Gate((char*)"Models/Gate/Body_Gate.obj");
	Model L_Gate((char*)"Models/Gate/L_Gate.obj");
	Model R_Gate((char*)"Models/Gate/R_Gate.obj");
	Model Piso((char*)"Models/Piso/Piso3D.obj");
	Model Platform((char*)"Models/Braq/Platform.obj");

	/*-----------------------Habitats--------------------------*/

	Model Pool((char*)"Models/Pool/Pool.obj");
	Model H_Rex((char*)"Models/H_Rex/H_Rex.obj");
	Model Lab((char*)"Models/Lab/Lab.obj");

	/*-----------Carga de modelos en carpeta formato .dae----------*/
	// Build and compile our shader program
	//Modelo de animación
	ModelAnim animacionPersonaje4("Animaciones/Personaje4/Knee.dae");
	//ModelAnim animacionPersonaje("Animaciones/Personaje4/MacarenaDance.dae");
	animacionPersonaje4.initShaders(animShader.Program);
	
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame1[i].posX1 = 0;
		KeyFrame1[i].incX1 = 0;
		KeyFrame1[i].incY1 = 0;
		KeyFrame1[i].incZ1 = 0;
		KeyFrame1[i].rot1RodIzq = 0;
		KeyFrame1[i].rot1Inc = 0;

	}

	ModelAnim animacionPersonaje3("Animaciones/Personaje3/Jog.dae");
	animacionPersonaje3.initShaders(animShader.Program);
	for (int l = 0; l < MAX_FRAMES; l++)
	{
		KeyFrame[l].posX = 0;
		KeyFrame[l].incX = 0;
		KeyFrame[l].incY = 0;
		KeyFrame[l].incZ = 0;
		KeyFrame[l].rotRodIzq = 0;
		KeyFrame[l].rotInc = 0;

	}

	/*ModelAnim animacionPersonaje5("Animaciones/Personaje5/dinoAgua.dae");
	animacionPersonaje5.initShaders(animShader.Program);
	for (int j = 0; j < MAX_FRAMES; j++)
	{
		KeyFrame[j].posX = 0;
		KeyFrame[j].incX = 0;
		KeyFrame[j].incY = 0;
		KeyFrame[j].incZ = 0;
		KeyFrame[j].rotRodIzq = 0;
		KeyFrame[j].rotInc = 0;

	}*/

	ModelAnim animacionPersonaje6("Animaciones/Personaje6/ptero.dae");
	animacionPersonaje6.initShaders(animShader.Program);
	for (int k = 0; k < MAX_FRAMES; k++)
	{
		KeyFrame1[k].posX1 = 0;
		KeyFrame1[k].incX1 = 0;
		KeyFrame1[k].incY1 = 0;
		KeyFrame1[k].incZ1 = 0;
		KeyFrame1[k].rot1RodIzq = 0;
		KeyFrame1[k].rot1Inc = 0;

	}

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	/*---------------SkyBox----------------*/
	vector<const GLchar*> faces;
	/*faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");*/

	faces.push_back("SkyBox/right.png");
	faces.push_back("SkyBox/left.png");
	faces.push_back("SkyBox/top.png");
	faces.push_back("SkyBox/bottom.png");
	faces.push_back("SkyBox/back.png");
	faces.push_back("SkyBox/front.png");
	
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		GLfloat currentFrame1 = glfwGetTime();
		deltaTime1 = currentFrame1 - lastFrame1;
		lastFrame1 = currentFrame1;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();
		
		//Sali();
		recorridoS();
		recorridoS2();
		recorrido3S();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);


		/*-------------------------------------Modelos-------------------------------------*/
		glm::mat4 tmp = glm::mat4(1.0f); //Temp

		//Carga de modelo 
		//Personaje
		view = camera.GetViewMatrix();
		glm::mat4 model(1);
		tmp = model = glm::translate(model, glm::vec3(0, 1, 0));

		/*-------------------------------------Trex1-------------------------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-60.0f, 13.5f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mov1));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BodyRex.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-60.0f, 13.5f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mov1));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rot1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BbocaRex.Draw(lightingShader);

		/*-------------------------------------Indominus------------------------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.5f, -25.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BodyH.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.0f, 7.5f, -25.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, glm::radians(40.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rot1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		L_ArmH.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.0f, 7.5f, -25.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, glm::radians(40.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rot1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		R_ArmH.Draw(lightingShader);
		/*---------------------------------------Acuatico--------------------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 74.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Acuatico.Draw(lightingShader);

		/*------------------------------Braquiosaurio Keyframes---------------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(30.0f,10.0f,0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Body.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(36.0f, 12.8f, -1.3f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotBraIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		L_braq.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(36.0f, 12.5f, 1.4f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotBraDer), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		R_braq.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(27.5f, 13.2f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotRodDer), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		RB_braq.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(27.7f, 13.2f, -1.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LB_braq.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(36.5f, 16.7f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Head.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(35.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Platform.Draw(lightingShader);

		/*------------------------------Habitats-------------------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 21.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pool.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Lab.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		H_Rex.Draw(lightingShader);

		/*--------------------------------------Piso------------------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.045f,0.025f, 0.025f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		/*---------------------------------------Puerta Principal-----------------------------*/

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		model = glm::translate(model, glm::vec3(2.5f, 0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Gate.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		model = glm::translate(model, glm::vec3(2.5f, 0.5f, 0.01f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.02f, 0.0f, 0.5));
		model = glm::rotate(model, glm::radians(-puerta), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		L_Gate.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		model = glm::translate(model, glm::vec3(2.5f, 0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-0.02f, 0.0f, -0.5f));
		model = glm::rotate(model, glm::radians(puerta), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		R_Gate.Draw(lightingShader);

		glBindVertexArray(0);
		/*-------------------------------Agua en movimiento--------------------------*/
		animShader2.Use();
		tiempo = glfwGetTime();//variable para dejar todo el tiempo moviendo el agua
		//definimos nuevamente el shader para trabajar con el 
		modelLoc = glGetUniformLocation(animShader2.Program, "model");
		viewLoc = glGetUniformLocation(animShader2.Program, "view");
		projLoc = glGetUniformLocation(animShader2.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(animShader2.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(animShader2.Program, "material.shininess"), 32.0f);
		glUniform3f(glGetUniformLocation(animShader2.Program, "light.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(animShader2.Program, "light.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(animShader2.Program, "light.specular"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(animShader2.Program, "light.direction"), 0.0f, -1.0f, -1.0f);
		view = camera.GetViewMatrix();

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-8.5f,0.0f,71.0f));
		model = glm::scale(model, glm::vec3(0.55f,0.55f,0.55f));	
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(animShader2.Program, "time"), tiempo);//añadimos animacion de movimiento
		Agua.Draw(animShader2);

		glBindVertexArray(0);

		/*_______________________________Personaje Animado___________________________*/
		animShader.Use();
		modelLoc = glGetUniformLocation(animShader.Program, "model");
		viewLoc = glGetUniformLocation(animShader.Program, "view");
		projLoc = glGetUniformLocation(animShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform3f(glGetUniformLocation(animShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(animShader.Program, "material.shininess"), 32.0f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.specular"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(animShader.Program, "light.direction"),0.0f, -1.0f, -1.0f);
		view = camera.GetViewMatrix();

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-50.0f,0.0f,-15.0f));
		model = glm::scale(model, glm::vec3(0.02f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		animacionPersonaje4.Draw(animShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -25.0f));
		model = glm::translate(model, glm::vec3(movKitXb, 0, movKitZb));
		model = glm::scale(model, glm::vec3(0.02f));	
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		animacionPersonaje3.Draw(animShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
		//model = glm::scale(model, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//animacionPersonaje5.Draw(animShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 50.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));//animacion de trayectoria
		model = glm::scale(model, glm::vec3(3.0f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		animacionPersonaje6.Draw(animShader);


		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void animacion()
{

		//Movimiento del personaje

		if (play)
		{
			if (i_curr_steps >= i_max_steps) //end of animation between frames?
			{
				playIndex++;
				if (playIndex>FrameIndex - 2)	//end of total animation?
				{
					printf("termina anim\n");
					playIndex = 0;
					play = false;
				}
				else //Next frame interpolations
				{
					i_curr_steps = 0; //Reset counter
									  //Interpolation
					interpolation();
				}
			}
			else
			{
				//Draw animation
				posX += KeyFrame[playIndex].incX;
				posY += KeyFrame[playIndex].incY;
				posZ += KeyFrame[playIndex].incZ;

				rotRodIzq += KeyFrame[playIndex].rotInc;
				rotRodDer += KeyFrame[playIndex].rotInc2;
				rotBraIzq += KeyFrame[playIndex].rotInc3;
				rotBraDer += KeyFrame[playIndex].rotInc4;

				i_curr_steps++;
			}

		}
	}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_M]) {
		anim1 = true;
	}

	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex >= 0))
		{

			interpolation();
			play = true;
			Sali();
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_K])
	{
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}

	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	if (keys[GLFW_KEY_Z])
	{
		active = !active;
		if (active)
			LightP2 = glm::vec3(1.0f, 1.0f, 1.0f);
		else
			LightP2 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	if (keys[GLFW_KEY_X])
	{
		active = !active;
		if (active)
			LightP3 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP3 = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	if (keys[GLFW_KEY_C])
	{
		active = !active;
		if (active)
			LightP4 = glm::vec3(1.0f, 1.0f, 0.0f);
		else
			LightP4 = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	if (anim)
	{
		if (rot1 < 15.0f ) {
			rot1 += 0.4f;

		}
		else {
			anim = false;
			anim2 = true;
		}
	}
	if (anim2)
	{
		if (rot1 > 15.0f ) {
			rot1 -= 0.4f;
		}

		else {
			anim2 = false;
			anim = true;
		}
	}

	if (keys[GLFW_KEY_O])
	{
		if (puerta < 45)
			puerta += 1.0f;

	}

	if (keys[GLFW_KEY_P])
	{
		if (puerta > -45)
			puerta -= 1.0f;

	}

	if (keys[GLFW_KEY_1])
	{
		if (rot < 45.0f)
			rot += 1.0f;

	}

	if (keys[GLFW_KEY_2])
	{
		if (rotRodIzq<45)
			rotRodIzq += 1.0f;
			
	}

	if (keys[GLFW_KEY_3])
	{
		if (rotRodIzq>-45)
			rotRodIzq -= 1.0f;
		
	}

	if (keys[GLFW_KEY_3])
	{
		if (rotRodIzq > -45)
			rotRodIzq -= 1.0f;

	}
	if (keys[GLFW_KEY_4])
	{
		if (rotRodDer < 45.0f)
			rotRodDer += 1.0f;

	}
	if (keys[GLFW_KEY_5])
	{
		if (rotRodDer > -45)
			rotRodDer -= 1.0f;

	}

	if (keys[GLFW_KEY_6])
	{
		if (rotBraDer > -45)
			rotBraDer -= 1.0f;

	}
	if (keys[GLFW_KEY_7])
	{
		if (rotBraDer < 45.0f)
			rotBraDer += 1.0f;

	}
	if (keys[GLFW_KEY_8])
	{
		if (rotBraIzq < 45.0f)
			rotBraIzq += 1.0f;

	}

	if (keys[GLFW_KEY_9])
	{
		if (rotBraIzq > -45)
			rotBraIzq -= 1.0f;

	}

	if (keys[GLFW_KEY_0])
	{
		if (rotBraDer > -45)
			rotBraDer -= 1.0f;

	}

	//Mov Personaje
	if (keys[GLFW_KEY_DOWN])
	{
		posZ += 1;
	}

	if (keys[GLFW_KEY_UP])
	{
		posZ -= 1;
	}

	if (keys[GLFW_KEY_LEFT])
	{
		posX -= 1;
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		posX += 1;
	}
	if (keys[GLFW_KEY_F])
	{
		circuito = true;
		circuitoa = true;
		circuitob = true;
	}
	if (keys[GLFW_KEY_G])
	{
		circuito = false;
		circuitoa = false;
		circuitob = false;
	}
//Pista
	if (anim1)
	{
		if (rot1 < 45.0f ) {
			rot1 += 0.4f;

		}
		else {
			anim1 = false;
			anim2 = true;
		}
	}
	if (anim2)
	{
		if (rot1 > 15.0f ) {
			rot1 -= 0.4f;
		}

		else {
			anim2 = false;
			anim1 = true;
		}
	}

	// Camera controls
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

}
void recorridoS2()
{

	if (circuitoa)
	{
		if (circuitoa)
		{
			if (recorridoa1)
			{
				movKitZa += 0.1f;
				if (movKitZa < 0)
				{
					recorridoa1 = false;
					recorridoa2 = true;
				}
			}
			if (recorridoa2)
			{
				movKitXa += 0.1f;
				if (movKitXa < 0)
				{
					recorridoa2 = false;
					recorridoa1 = true;
				}
			}

		}
	}
		
}

void recorrido3S() {
	if (circuitob)
	{
		if (recorridob1)
		{
			movKitZb += 0.1f;
			if (movKitZb > 10)
			{
				recorridob1 = false;
				recorridob2 = true;
			}
		}
		if (recorridob2)
		{
			rotKitb = -90;
			movKitXb += 0.1f;
			if (movKitXb > 10)
			{
				recorridob2 = false;
				recorridob3 = true;

			}
		}

		if (recorridob3)
		{
			rotKitb = -90;
			movKitZb -= 0.1f;
			if (movKitZb < 0)
			{
				recorridob3 = false;
				recorridob4 = true;
			}
		}

		if (recorridob4)
		{
			rotKitb = -90;
			movKitXb -= 0.1f;
			if (movKitXb < 0)
			{
				recorridob4 = false;
				recorridob5 = true;
			}
		}
		if (recorridob5)
		{
			rotKitb = 0;
			movKitZb += 0.1f;
			if (movKitZb > 0)
			{
				recorridob5 = false;
				recorridob1 = true;
			}
		}


	}
}


//Recorrido
void recorridoS()
{
	//Recorrido 1 
	if (circuito)
	{
		if (recorrido1)
		{
			movKitZ += 0.1f;
			if (movKitZ > 40)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			rotKit = -90;
			movKitX += 0.1f;
			if (movKitX > 40)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}

		if (recorrido3)
		{
			rotKit = 180;
			movKitZ -= 0.1f;
			if (movKitZ < 0)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4)
		{
			rotKit = 90;
			movKitX -= 0.1f;
			if (movKitX < 0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5)
		{
			rotKit = 0;
			movKitZ += 0.1f;
			if (movKitZ > 0)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}


	}

		//Recorrido # 3 Diagonal

	/*if (circuito)
	{
		if (recorrido1)
		{
			rotKit = 90;
			movKitX += 0.1f;//Z
			if (movKitX > 11)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			rotKit = -45;
			movKitZ += 0.1f;
			movKitX -= 0.1f;
			if (movKitZ > 6 && movKitX < 6)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}

		if (recorrido3)
		{
			rotKit = 270;
			movKitX -= 0.1f;
			if (movKitX < 0)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4)
		{
			rotKit = 180;
			movKitZ -= 0.1f;
			if (movKitZ < 0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}

		if (recorrido5)
		{
			rotKit = 0;
			movKitZ += 0.1f;
			if (movKitZ > 0)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}
	}*/

}