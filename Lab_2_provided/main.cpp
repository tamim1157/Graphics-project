
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "basic_camera.h"
#include "camera.h"
#include "pointLight.h"
#include "sphere.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinder.h"
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

using namespace std;

//function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawTableChair(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c);
void drawTable(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c);
void drawChair(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c);
//void drawAlmirahWithDoors(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c);
//void drawParabolicTable(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c);
void drawFan(unsigned int VAO, Shader lightingShader, glm::mat4 matrix);
void drawCube(unsigned int& VAO, Shader& lightingShader, glm::mat4 model, glm::vec3 color);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
//void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
//void read_file(string file_name, vector<float>& vec);
//unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector<float>& coordinates, vector<float>& normals, vector<int>& indices, vector<float>& vertices, float div);
//unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
long long nCr(int n, int r);
//void lightEffect(unsigned int VAO, Shader lightShader, glm::mat4 model, glm::vec3 color);
//void load_texture(unsigned int& texture, string image_name, GLenum format);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
void read_file(string file_name, vector<float>& vec);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector<float>& coordinates, vector<float>& normals, vector<int>& indices, vector<float>& vertices, float div);




//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//screen
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float aspectRatio = 4.0f / 3.0f;

//camera
float eyeX = 20.5f, eyeY = 4.9f, eyeZ = 40.5f;           //12,2,25 
float lookAtX = 5.0f, lookAtY = 4.5f, lookAtZ = 12.75f;
Camera camera(glm::vec3(eyeX, eyeY, eyeZ));

//timing
float deltaTime = 0.0f;     // time between current frame and last frame
float lastFrame = 0.0f;

//fan
float r = 0.0f;
bool fanOn = false;

//bird's eye view
bool birdEyeView = false;
glm::vec3 birdEyePosition(2.0f, 3.5f, 13.5f);
glm::vec3 birdEyeTarget(2.0f, 0.0f, 7.5f);
float birdEyeSpeed = 1.0f;

//rotation around a point
float theta = 0.0f; // Angle around the Y-axis
float radius = 2.0f;

//directional light
bool directionLightOn = true;
bool directionalAmbient = true;
bool directionalDiffuse = true;
bool directionalSpecular = true;

//spot light
bool spotLightOn = true;

//point light
bool point1 = true;
bool point2 = true;

//custom projection matrix
float fov = glm::radians(camera.Zoom);
float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;
float near = 0.1f;
float far = 100.0f;
float tanHalfFOV = tan(fov / 2.0f);

//flag
int flag2 = 1;

//doors and windows
bool openDoor = true;
float doorAngle = 90.0f;

float DoorAngle = 0.0f;  
//float rightDoorAngle = 0.0f; 
bool isDoorOpen = false;
float rotationSpeed = 2.0f;

bool closedoor = false;
float wdangle = 0.0f;

////bezier required

unsigned int bezierVAO, ropeVAO, rotorVAO, sliderVAO, carousalVAO, headVAO, hillVAO, pillarVAO;

vector <float> cntrlPoints, cntrlPointsRope, cntrlPointsRope2, cntrlPointsRotor, cntrlPointsCylinder, cntrlPointsCarousal, cntrlPointsHead, cntrlPointsPilar;
vector <float> coordinates, coordinatesRope, coordinatesRope2, coordinatesRotor, coordinatesCylinder, coordinatesCarousal, coordinatesHead, coordinatesPillar;
vector <float> normals, normalsRope, normalsRope2, normalsRotor, normalsCylinder, normalsCarousal, normalsHead, normalsPillar;
vector <int> indices, indicesRope, indicesRope2, indicesRotor, indicesCylinder, indicesCarousal, indicesHead, indicesPillar;
vector <float> vertices, verticesRope, verticesRotor, verticesRope2, verticesCylinder, verticesCarousal, verticesHead, verticesPillar;
//vector <float> textureCoords, textureCoordsRope, textureCoordsRope2;





//bezier
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 30;

unsigned int sphereVAO, coneVAO,basinVAO;

vector <float> cntrlPointsSphere, cntrlPointsBasin;
vector <float> coordinatesSphere, coordinatesBasin;
vector <float> normalsSphere, normalsBasin;
vector <int> indicesSphere, indicesBasin;
vector <float> verticesSphere, verticesBasin;

vector <float> cntrlPointsSphere1, cntrlPointsCone;
vector <float> coordinatesSphere1, coordinatesCone;
vector <float> normalsSphere1, normalsCone;
vector <int> indicesSphere1, indicesCone;
vector <float> verticesSphere1, verticesCone;


// texture
float extra = 4.0f;
//float TXmin = 0.0f;
//float TXmax = 1.0f;
//float TYmin = 0.0f;
//float TYmax = 1.0f;

//positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(-2.9f,  3.0f,  5.0f),
    glm::vec3(6.7f,  3.0f,  7.0f),
};

PointLight pointlight1(
    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,       // position
    0.2f, 0.2f, 0.2f,       //ambient
    0.8f, 0.8f, 0.8f,       //diffuse
    0.2f, 0.2f, 0.2f,       //specular
    1.0f,       //k_c
    0.09f,      //k_l
    0.032f,     //k_q
    1       //light number
);

PointLight pointlight2(
    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,
    0.2f, 0.2f, 0.2f,
    0.8f, 0.8f, 0.8f,
    0.2f, 0.2f, 0.2f,
    1.0f,
    0.09f,
    0.032f,
    2
);



int main()
{
    //glfw initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1907060: Assignment 4", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //glad load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //configure global opengl state
    glEnable(GL_DEPTH_TEST);

    //build and compile our shader program
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    //Shader constantShader("vertexShader.vs", "fragmentShaderV2.fs");

    //set up vertex data (and buffer(s)) and configure vertex attributes
    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ourShader.use();
    //constantShader.use();
    /**/

    read_file("slider.txt", cntrlPointsSphere);
    sphereVAO = hollowBezier(cntrlPointsSphere.data(), ((unsigned int)cntrlPointsSphere.size() / 3) - 1, coordinatesSphere, normalsSphere, indicesSphere, verticesSphere, 4.0);


    read_file("hill.txt", cntrlPoints);
    hillVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1, coordinates, normals, indices, vertices, 1.0);

    read_file("rope.txt", cntrlPointsRope);
    ropeVAO = hollowBezier(cntrlPointsRope.data(), ((unsigned int)cntrlPointsRope.size() / 3) - 1, coordinatesRope, normalsRope, indicesRope, verticesRope, 1.0);

    /*read_file("slider.txt", cntrlPointsCylinder);
    sliderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1, coordinatesCylinder, normalsCylinder, indicesCylinder, verticesCylinder, 4.0);*/

    read_file("pilar.txt", cntrlPointsPilar);
    pillarVAO = hollowBezier(cntrlPointsPilar.data(), ((unsigned int)cntrlPointsPilar.size() / 3) - 1, coordinatesPillar, normalsPillar, indicesPillar, verticesPillar, 1.0);

    //modification
    unsigned int texture, texture2, texture3;

    string ImgPath = "grass.jpg";
    texture = loadTexture(ImgPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    ImgPath = "rope.jpeg";
    texture2 = loadTexture(ImgPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    ImgPath = "wood.jpg";
    texture3 = loadTexture(ImgPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);


    //for basin at washroom
    read_file("sphere.txt", cntrlPointsSphere1);
    sphereVAO = hollowBezier(cntrlPointsSphere1.data(), ((unsigned int)cntrlPointsSphere1.size() / 3) - 1, coordinatesSphere1, normalsSphere1, indicesSphere1, verticesSphere1, 2.0);


    //for comod
    read_file("basin.txt", cntrlPointsBasin);
    basinVAO = hollowBezier(cntrlPointsBasin.data(), ((unsigned int)cntrlPointsBasin.size() / 3) - 1, coordinatesBasin, normalsBasin, indicesBasin, verticesBasin, 2.0);

  

    //floor texture
    string diffuseMapPath = "floor.jpg";
    string specularMapPath = "floor.jpg";
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 10.0f, 1.25f, 2.25f);


    //floorfront texture
    string diffuseMapPath1 = "floorfront.jpg";
    string specularMapPath1 = "floorfront.jpg";
    unsigned int diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube1 = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 1.25f, 2.25f);

    //roof texture
    string diffuseMapPath2 = "classroom_roof.jpg";
    string specularMapPath2 = "classroom_roof.jpg";
    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 2.5f, 4.5f);

    //wall texture
    string diffuseMapPath3 = "wall.jpg";
    string specularMapPath3 = "wall.jpg";
    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3 = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    //wood texture
    string diffuseMapPath4 = "wood.jpg";
    string specularMapPath4 = "wood.jpg";
    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube4 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    //wood texture 2
    string diffuseMapPath5 = "wood2.jpg";
    string specularMapPath5 = "wood2.jpg";
    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube5 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //door and window texture
    string diffuseMapPath6 = "door.jpg";
    string specularMapPath6 = "door.jpg";
    unsigned int diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube6 = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //whiteboard texture
    string diffuseMapPath7 = "board.jpg";
    string specularMapPath7 = "board.jpg";
    unsigned int diffMap7 = loadTexture(diffuseMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube7 = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //balance pillar texture
    string diffuseMapPath8 = "wood.jpg";
    string specularMapPath8 = "wood.jpg";
    unsigned int diffMap8 = loadTexture(diffuseMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube8 = Cube(diffMap8,specMap8,32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //balance floor texture
    string diffuseMapPath9 = "floorbalance.png";
    string specularMapPath9 = "floorbalance.png";
    unsigned int diffMap9 = loadTexture(diffuseMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube9 = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    //back wall texture
    string diffuseMapPath10 = "wall1.jpeg";
    string specularMapPath10 = "wall1.jpeg";
    unsigned int diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube10 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //back wall texture
    string diffuseMapPath11 = "grassf.jpg";
    string specularMapPath11 = "grassf.jpg";
    unsigned int diffMap11 = loadTexture(diffuseMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube11 = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //pillar texture
    string diffuseMapPath12 = "pilar.png";
    string specularMapPath12 = "pilar.png";
    unsigned int diffMap12 = loadTexture(diffuseMapPath12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapPath12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube12 = Cube(diffMap12, specMap12, 32.0f, 1.0f, 0.0f, 0.0f, 1.0f);


    //halfwall texture
    string diffuseMapPath13 = "half.png";
    string specularMapPath13 = "half.png";
    unsigned int diffMap13 = loadTexture(diffuseMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube13 = Cube(diffMap13,specMap13, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //outerwallrightt texture
    string diffuseMapPath14 = "rwall1.jpg";
    string specularMapPath14 = "rwall1.jpg";
    unsigned int diffMap14 = loadTexture(diffuseMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube14 = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //outerwall left texture
    string diffuseMapPath15 = "newlwall.jpeg";
    string specularMapPath15 = "newlwall.jpeg";
    unsigned int diffMap15 = loadTexture(diffuseMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube15 = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //comode texture
    string diffuseMapPath16 = "comode.jpg";
    string specularMapPath16 = "comode.jpg";
    unsigned int diffMap16 = loadTexture(diffuseMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube16 = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

   


    r = 0.0f;

    //render loop
    while (!glfwWindowShouldClose(window))
    {
        //per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input
        processInput(window);

        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //ourShader.use();
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        //point lights set up
        pointlight1.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);

        //directional light set up
        lightingShader.setVec3("directionalLight.direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setVec3("directionalLight.ambient", 0.1f, 0.1f, 0.1f);
        lightingShader.setVec3("directionalLight.diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("directionalLight.specular", 0.0f, 0.0f, 0.0f);
        lightingShader.setBool("directionLightOn", directionLightOn);

        //spot light set up
        lightingShader.setVec3("spotLight.position", 2.0f, 2.0f, 2.0f);
        lightingShader.setVec3("spotLight.direction", 0.0f, -1.0f, 0.0f);
        lightingShader.setVec3("spotLight.ambient", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("spotLight.specular", 0.2f, 0.2f, 0.2f);
        lightingShader.setFloat("spotLight.k_c", 1.0f);
        lightingShader.setFloat("spotLight.k_l", 0.09);
        lightingShader.setFloat("spotLight.k_q", 0.032);
        //lightingShader.setFloat("spotLight.cos_theta", glm::cos(glm::radians(60.0f)));
        lightingShader.setFloat("spotLight.inner_circle", glm::cos(glm::radians(7.5f)));
        lightingShader.setFloat("spotLight.outer_circle", glm::cos(glm::radians(15.0f)));
        lightingShader.setBool("spotLightOn", spotLightOn);

        //handle for changes in directional light directly from shedder
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            if (directionLightOn) {
                lightingShader.setBool("ambientLight", !directionalAmbient);
                directionalAmbient = !directionalAmbient;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
            if (directionLightOn) {
                lightingShader.setBool("diffuseLight", !directionalDiffuse);
                directionalDiffuse = !directionalDiffuse;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
            if (directionLightOn) {
                lightingShader.setBool("specularLight", !directionalSpecular);
                directionalSpecular = !directionalSpecular;
            }
        }

        glm::mat4 projection(0.0f);
        projection[0][0] = 1.0f / (aspect * tanHalfFOV);
        projection[1][1] = 1.0f / tanHalfFOV;
        projection[2][2] = -(far + near) / (far - near);
        projection[2][3] = -1.0f;
        projection[3][2] = -(2.0f * far * near) / (far - near);
        
        lightingShader.setMat4("projection", projection);

        

        glm::mat4 view;

        //check for bird's eye view and normal view
        if (birdEyeView) {
            glm::vec3 up(0.0f, 1.0f, 0.0f);
            view = glm::lookAt(birdEyePosition, birdEyeTarget, up);
        }
        else {
            view = camera.GetViewMatrix();
        }
        
        lightingShader.setMat4("view", view);

        //define matrices and vectors needed
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, RotateTranslateMatrix, InvRotateTranslateMatrix;
        glm::vec3 color;
        
        //initialize all elements as non-emissive
        lightingShader.setVec3("material.emissive", glm::vec3(0.0f, 0.0f, 0.0f));
        
        float z = 0.0f;
        
        if (openDoor) {
            if (doorAngle < 90.0f) {
                doorAngle += 0.35;
            }
        }

        if (!openDoor) {
            if (doorAngle > 0.0f) {
                doorAngle -= 0.35;
            }
        }

        //almirah rotatespeed
        if (isDoorOpen) {
            if (DoorAngle < 90.0f) {
                DoorAngle += 0.45;
            }
        }

        if (!isDoorOpen) {
            if (DoorAngle > 0.0f) {
                DoorAngle -= 0.45;
            }
        }

        //washroom door
         //
        if (closedoor) {
            if (wdangle < 90.0f) {
                wdangle += 0.45;
            }
        }

        if (!closedoor) {
            if (wdangle > 0.0f) {
                wdangle -= 0.45;
            }
        }

        //draw fans with rotations
        z = 0.0f;
        for (int i = 0; i < 2; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, z));
            drawFan(VAO, lightingShader, translateMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.60f, 0.0f, z));
            drawFan(VAO, lightingShader, translateMatrix);

            z += 7.5;
        }

        //draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        //we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);

        for (unsigned int i = 0; i < 2; i++)
        {
            translateMatrix = glm::translate(identityMatrix, pointLightPositions[i]);
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -0.2f, 0.2f));
            model = translateMatrix * scaleMatrix;
            ourShader.setMat4("model", model);
            ourShader.setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        //point lights set up
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);

        //directional light set up
        lightingShaderWithTexture.setVec3("directionalLight.direction", 0.0f, -1.0f, 0.0f);
        lightingShaderWithTexture.setVec3("directionalLight.ambient", 0.1f, 0.1f, 0.1f);
        lightingShaderWithTexture.setVec3("directionalLight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShaderWithTexture.setVec3("directionalLight.specular", 0.0f, 0.0f, 0.0f);
        lightingShaderWithTexture.setBool("directionLightOn", directionLightOn);

        //spot light set up
        lightingShaderWithTexture.setVec3("spotLight.position", 2.0f, 2.0f, 2.0f);
        lightingShaderWithTexture.setVec3("spotLight.direction", 0.0f, -1.0f, 0.0f);
        lightingShaderWithTexture.setVec3("spotLight.ambient", 0.5f, 0.5f, 0.5f);
        lightingShaderWithTexture.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShaderWithTexture.setVec3("spotLight.specular", 0.2f, 0.2f, 0.2f);
        lightingShaderWithTexture.setFloat("spotLight.k_c", 1.0f);
        lightingShaderWithTexture.setFloat("spotLight.k_l", 0.09);
        lightingShaderWithTexture.setFloat("spotLight.k_q", 0.032);
        //lightingShaderWithTexture.setFloat("spotLight.cos_theta", glm::cos(glm::radians(30.0f)));
        lightingShaderWithTexture.setFloat("spotLight.inner_circle", glm::cos(glm::radians(7.5f)));
        lightingShaderWithTexture.setFloat("spotLight.outer_circle", glm::cos(glm::radians(15.0f)));
        lightingShaderWithTexture.setBool("spotLightOn", spotLightOn);

        //floor1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -20.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, -0.1f, 68.2f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube.drawCubeWithTexture(lightingShader, model);
        }


        //2nd floor office
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, -0.1f, 10.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube.drawCubeWithTexture(lightingShader, model);
        }


        //2nd floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, -0.1f, 52.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube.drawCubeWithTexture(lightingShader, model);
        }

        //floor front
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, -3.15f, -22.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(16.0f,2.0f,71.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube1.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube1.drawCubeWithTexture(lightingShader, model);
        }
  
       // cube1.drawCubeWithTexture(lightingShaderWithTexture, model);


        //field of school
      
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -3.0f, -32.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, -0.1f, 90.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube11.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube11.drawCubeWithTexture(lightingShader, model);
        }

        //boundary back
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -3.0f, -32.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 6.5f, 90.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //boundary left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -3.0f, -32.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 6.5f, 0.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube14.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube14.drawCubeWithTexture(lightingShader, model);
        }

        //boundary right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -3.0f, 57.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 6.5f, 0.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube14.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube14.drawCubeWithTexture(lightingShader, model);
        }


        //boundary front 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(51.0f, -3.0f, 33.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 6.5f, 23.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //boundary front 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(51.0f, -3.0f, -32.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 6.5f, 50.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //pillar1 front outer wall sec1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50.6f, -3.0f, 17.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.1f, 8.4f, 1.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //pillar2 front outer wall sec2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50.6f, -3.0f, 32.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.1f, 8.4f, 1.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }
        

        //upper pilar front
           
        translateMatrix = glm::translate(identityMatrix, glm::vec3(50.6f, 5.4f, 33.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.1f, 3.1f, -16.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //roof ROOM 1

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.5f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.9f, 0.1f, 18.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

          //staircase forward roof 

        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.5f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.9f, 0.1f, 8.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);


        //roof room2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.5f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.9f, 0.1f, 18.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //roof room3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.5f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.9f, 0.1f, 17.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //roof office room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.5f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.9f, 0.1f, 10.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);


         //2nd floor roof ROOM 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 8.0f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.7f, 0.1f, 24.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);


        //roof2nd floor room2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 8.0f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.7f, 0.1f, 18.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //roof room3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 8.0f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.7f, 0.1f, 17.2f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //roof office room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 8.0f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.7f, 0.1f, 10.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //drawCube(VAO, lightingShader, model, color);

        if (flag2 == 1)
        {
            cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube2.drawCubeWithTexture(lightingShader, model);
        }
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

       //staircase
        
        for (int i = 0; i < 7; i++)
        {

        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f - i * 0.9f, -1.0 + i * 0.37f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.4f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        } 

        }

        //staircase field

        for (int i = 0; i < 4; i++)
        {

            translateMatrix = glm::translate(identityMatrix, glm::vec3(15.1f - i * 0.9f, -3.15 + i * 0.48f, 15.225f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.65f, 15.0f));
            model = translateMatrix * scaleMatrix;
            //color = glm::vec3(0.659f, 0.820f, 0.843f);
            //drawCube(VAO, lightingShader, model, color);
            if (flag2 == 1)
            {
                cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
            }
            else
            {
                cube6.drawCubeWithTexture(lightingShader, model);
            }

        }

        //UPPER floor staircase

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f,1.2f,-10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.1f, 0.4f, 6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        //staircase upper 

        for (int i = 0; i <9; i++)
        {

            translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.9f + i * 0.9f, 1.2 + i * 0.26f, -6.5f));
            //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.38f, 2.5f));
            model = translateMatrix * scaleMatrix;
            //color = glm::vec3(0.659f, 0.820f, 0.843f);
            //drawCube(VAO, lightingShader, model, color);
            if (flag2 == 1)
            {
                cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
            }
            else
            {
                cube6.drawCubeWithTexture(lightingShader, model);
            }

        }
      


        //front wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }
       // cube10.drawCubeWithTexture(lightingShaderWithTexture, model);

        //pillar1 right 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 9.2f, 0.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //pillar2  right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 9.2f, 0.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //pilla3  right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, -3.8f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 9.2f, 0.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //pilla4  right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 9.2f, 0.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //pillr5  right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 9.2f, 0.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //pillr6  right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, 47.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 9.2f, 0.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }



        //washroom 2nd floor
        
        //stand  basin1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.2f, 3.7f, -11.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.5f, 1.2f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }

        //stand  basin2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 3.7f, -11.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.5f, 1.2f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }


        //stand  basin3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.8f, 3.7f, -11.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 1.5f, 1.2f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube12.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube12.drawCubeWithTexture(lightingShader, model);
        }


        //1st floor semi boundary sec 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, 48.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.8f, 2.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }
        

        //1st floor semi boundary sec 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, -1.1f, 48.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -17.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //1st floor semi boundary sec 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, -1.1f, 13.7f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -17.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //1st floor semi boundary sec 4
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, -1.1f, -3.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -16.3f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //1st floor semi boundary sec 5
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, -1.1f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.9f, 2.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }


        //2ND FLOOR
        // 
        //2ND floor semi boundary sec 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, 3.5f, 48.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.8f, 2.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }


        //2nd floor semi boundary sec 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, 3.5f, 48.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -17.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor semi boundary sec 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, 3.5f, 32.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -18.3f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor semi boundary sec 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, 3.5f, 13.7f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -17.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor semi boundary sec 4
        translateMatrix = glm::translate(identityMatrix, glm::vec3(12.2f, 3.5f, -3.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -16.3f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor semi boundary sec 5
        translateMatrix = glm::translate(identityMatrix, glm::vec3(11.7f, 3.5f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.9f, 2.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube13.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube13.drawCubeWithTexture(lightingShader, model);
        }


        //front wall office
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }
        // cube10.drawCubeWithTexture(lightingShaderWithTexture, model);


        //front wall washroom/office 2nd floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }


        //left wall section siri
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 9.2f, -6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


          //left wall section office room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 3.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section  2 office room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, -3.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


         //left wall window 2 down section office
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 up section office
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        //left wall office window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.49f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall office window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, -13.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.49f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //office room right wall section 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 7.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall office room  door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.5f, -13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //door office room 
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, -10.15f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.5f, -3.00f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        // 2nd floor left wall section office/wash room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 3.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section  2 office room
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, -3.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


         //left wall window 2 down section office
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 up section office
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        //left wall office window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.49f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall office window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, -13.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.49f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //office room right wall section 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 7.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //office room right wall divider
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.4f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //office room right wall divider2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.4f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //door wash room inside1 room 
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(wdangle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.9f, 3.7f, -17.00f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 3.6f, -0.1f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }
        //door wash room inside2 room 
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(wdangle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 3.7f, -17.00f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 3.6f, -0.1f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        //door wash room inside3 room 
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(wdangle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 3.7f, -17.00f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 3.6f, -0.1f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        //office room right wall divider3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 3.7f, -20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.4f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        ////toilet section
        ////toilet
       // translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 3.7f, -19.0f));
       // scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.4f, 1.0f));
       // model = translateMatrix * scaleMatrix;
       // color = glm::vec3(0.494f, 0.514f, 0.541f);
       // Cylinder c1 = Cylinder(0.5f, 36, 10, color, color, color, 32.0f);
       // c1.drawSphereTexture(lightingShaderWithTexture, model, diffMap7, specMap7);

       // ////toilet using bezier curve
       // translateMatrix = glm::translate(identityMatrix, glm::vec3(5.6f, 4.55f, -19.0));
       // scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75, 0.75, 0.75));
       //// rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
       // rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
       // model = translateMatrix * scaleMatrix* rotateYMatrix;
       // lightingShaderWithTexture.setInt("material.diffuse", 0);
       // lightingShaderWithTexture.setInt("material.specular", 1);
       // lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
       // glActiveTexture(GL_TEXTURE0);
       // glBindTexture(GL_TEXTURE_2D, diffMap7);
       // glActiveTexture(GL_TEXTURE1);
       // glBindTexture(GL_TEXTURE_2D, specMap7);
       // glBindVertexArray(basinVAO);
       // lightingShaderWithTexture.setMat4("model", model);
       // glDrawElements(GL_TRIANGLES, (unsigned int)indicesBasin.size(), GL_UNSIGNED_INT, (void*)0);

        //// Base of the commode
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 3.7f, -19.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.70f, 0.75f));
        //model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //Cylinder base = Cylinder(0.5f, 36, 10, color, color, color, 32.0f);
        //base.drawSphereTexture(lightingShaderWithTexture, model, diffMap6, specMap6);

        //// Bowl of the commode
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 4.2f, -19.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, 0.50f, 0.75f));
        //model = translateMatrix * scaleMatrix;
        //Sphere bowl = Sphere(0.5f, 36, 18, color);
        //bowl.drawSphereTexture(lightingShaderWithTexture, model, diffMap6, specMap6);

        //// Back of the commode
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(5.8f, 4.2f, -18.7f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.7f, 0.1f));
        //model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.494f, 0.514f, 0.541f);
        //Cylinder back = Cylinder(0.5f, 36, 10, color, color, color, 32.0f);
        //back.drawSphereTexture(lightingShaderWithTexture, model, diffMap7, specMap7);

        //// Seat of the commode
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 4.5f, -18.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
        //model = translateMatrix * scaleMatrix;
        //Sphere seat = Sphere(0.5f, 36, 18, color);
        //seat.drawSphereTexture(lightingShaderWithTexture, model, diffMap7, specMap7);

        //// Lid of the commode
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 5.0f, -18.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.05f, 1.0f));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = translateMatrix * rotateXMatrix * scaleMatrix;
        //Sphere lid = Sphere(0.5f, 36, 18, color);
        //lid.drawSphereTexture(lightingShaderWithTexture, model, diffMap7, specMap7);

        //test
        // Base (Main Bowl)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 3.7f, -18.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.75f, 1.0f)); // Taller base
        model = translateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f); // White
        Cylinder base = Cylinder(0.5f, 36, 10, color, color, color, 32.0f);
        base.drawSphereTexture(lightingShaderWithTexture, model, diffMap16, specMap16);

        // Back (Curved Backrest)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 4.55f, -18.20f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.5f, 0.3f)); // Taller and thinner
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f); // Same white
        Sphere back = Sphere(0.5f, 36, 18, color);
        back.drawSphereTexture(lightingShaderWithTexture, model, diffMap16, specMap16);

        // Seat (Flat Surface)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 4.55f, -18.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9f, 0.05f, 0.9f)); // Thin flat surface
        model = translateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        Sphere seat = Sphere(0.5f, 36, 18, color);
        seat.drawSphereTexture(lightingShaderWithTexture, model, diffMap6, specMap6);

        // Lid (Tilted Top Surface)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5f, 4.6f, -18.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9f, 0.05f, 0.9f)); // Thin and similar to seat
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Tilted backward
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        Sphere lid = Sphere(0.5f, 36, 18, color);
        lid.drawSphereTexture(lightingShaderWithTexture, model, diffMap16, specMap16);

        



        //right wall office room  door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 7.2f, -13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //door office room 
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, -10.15f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.5f, -3.00f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }




        //room1 1st floor
        //left wall section 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 0.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, 0.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
       // cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall section 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall section 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);



        //room2 left wall section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 11 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 17.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 11 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, 17.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        // cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 21 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 24.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 21 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, 24.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall section 31
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 27.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        


        //room3 left wall section 12
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 12 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 35.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 12 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, 35.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        // cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section 22
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 38.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 22 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 42.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 22 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 2.5f, 42.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////left wall section 32
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 45.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //back wall 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }



        //room 1 right wall section 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window down section 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window up section 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.5f, 2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall section 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 4.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.0f, 11.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall section 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        //2nd room right wall section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window down section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 19.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window up section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.5f, 19.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall section 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 21.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.0f, 28.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        ////right wall section 31
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 30.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);



        ////ROOM 3 right section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall window down section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 37.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall window up section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.5f, 37.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall section 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 39.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 2.0f, 46.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //////right wall section 31
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 48.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 1.0f));
        //model = translateMatrix * scaleMatrix;
        ////color = glm::vec3(0.659f, 0.820f, 0.843f);
        ////drawCube(VAO, lightingShader, model, color);
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);



        //2nd floor all
// 
         //left wall section 1 room 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }

        //left wall window 1 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 0.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, 0.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        // cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall section 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        //front wall 2nd floor room1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //back wall room1 2nd floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f,3.7f, 14.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor room1 right wall section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window down section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window up section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 7.2f, 2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall section 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 4.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 6.7f, 11.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall section 31
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);



        //2nd room 2nd floor
          //left wall section 1 room 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 14.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }

        //left wall window 1 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 18.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, 18.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        // cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 21.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 25.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, 25.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall section 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 28.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        ////front wall 2nd floor room1
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 14.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, 0.1f));
        //model = translateMatrix * scaleMatrix;
        ////color = glm::vec3(0.659f, 0.820f, 0.843f);
        ////drawCube(VAO, lightingShader, model, color);
        //if (flag2 == 1)
        //{
        //    cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube10.drawCubeWithTexture(lightingShader, model);
        //}

        //back wall room1 2nd floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor room1 right wall section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 14.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 5.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window down section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 19.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window up section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 7.2f, 19.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall section 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 21.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 6.7f, 28.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall section 31
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 30.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 1.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        //room3 2nd floor
         //room3 left wall section 12
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 12 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 35.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 12 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, 35.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube3.drawCubeWithTexture(lightingShader, model);
        }
        // cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

         //left wall section 22
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 38.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 4.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 22 down section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 42.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 22 up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 7.2f, 42.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////left wall section 32
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 45.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.5f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);


        ////ROOM 3 right section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 31.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall window down section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 37.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall window up section 11
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 7.2f, 37.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.0f, 2.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall section 21
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 39.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 4.5f, 6.5f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right wall door up section
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 6.7f, 46.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 1.5f, 2.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, model);

        //back wall room3 2nd floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, 48.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }




        //back wall 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 14.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }
       // cube10.drawCubeWithTexture(lightingShaderWithTexture, model);

        //back wall 2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, 48.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }
        

        //back wall 3
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.0f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //back wall 2nd floor
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 3.7f, -10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 4.5f, -0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube10.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube10.drawCubeWithTexture(lightingShader, model);
        }

        //ROOM1
        //left wall window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 0.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);


        //ROOM1 2ND floor
       //left wall window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 0.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 7.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);



        //room2 left window
        //left wall window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 17.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 20.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 24.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 27.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);


        //2nd floor room2
               
        //left wall window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 18.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 21.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 25.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall window 2 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 28.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

       // //room3 left window
       //left wall window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 35.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

       // //left wall window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 38.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

       // //left wall window 2 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 42.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

       // //left wall window 2 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.5f, 45.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);


        //2nd floor room 3
        
       //left wall window 1 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 35.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        // //left wall window 1 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 38.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        // //left wall window 2 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 42.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        // //left wall window 2 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 5.2f, 45.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);


        //room 1 1st floor
        //right wall window 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.5f, 2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.5f, 4.50f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //room 1 2nd floor
       //right wall window 1
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 5.2f, 2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 5.2f, 4.50f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //room 2 right window
         //right wall window 11
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.5f, 19.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window 21
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.5f, 21.50f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //room 2  2nd floor right window
         //right wall window 11
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 5.2f, 19.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window 21
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 5.2f, 21.50f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //room 3 right window
         //right wall window 11
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.5f, 37.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window 21
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.5f, 39.50f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //room 3  2nd floor right window
        //right wall window 11
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 5.2f, 37.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, 1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall window 21
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 5.2f, 39.50f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 2.0f, -1.25f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, model);



        //door room1 1st floor
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.0f, -2.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }
        //cube6.drawCubeWithTexture(lightingShaderWithTexture, model);

         //door room1 2nd floor
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.0f, -2.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }
        


        //door room 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 30.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.0f, -2.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor door room 2
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 30.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.0f, -2.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        //door room 3
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, -1.0f, 47.88f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.0f, -2.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }

        //2nd floor door room 3
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(doorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 3.7f, 47.88f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.1f, 3.0f, -2.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        //color = glm::vec3(0.404f, 0.353f, 0.325f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube6.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube6.drawCubeWithTexture(lightingShader, model);
        }


        z = 0.0f;
        //draw tables and chairs room1
        for (int j = 0; j < 4; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);
            }

            z += 2.25;
        }

        z = 18.25f;
        //draw tables and chairs room2 
        for (int j = 0; j < 4; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);
            }

            z += 2.25;
        }

        z = 36.25f;
        //draw tables and chairs room3
        for (int j = 0; j < 4; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);
            }

            z += 2.25;
        }


        //2nd floor room 1 chair table
        z = 0.0f;
       float y = 4.7f; // Set y for the 2nd floor
        // Draw tables and chairs for the 2nd floor
        for (int j = 0; j < 4; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, y, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, y, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);
            }

            z += 2.25;
        }

        //2nd floor room 2 chair table
        z = 18.25f;
        y = 4.7f; // Set y for the 2nd floor
        // Draw tables and chairs for the 2nd floor
        for (int j = 0; j < 4; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, y, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, y, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);
            }

            z += 2.25;
        }
       

        //2nd floor room 3 chair table
        z = 36.25f;
         y = 4.7f; // Set y for the 2nd floor
        // Draw tables and chairs for the 2nd floor
        for (int j = 0; j < 4; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, y, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(-1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);
            }

            translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, y, z));
            drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube4);

            for (int i = 0; i < 2; i++) {
                translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(1.25f, 0.0f, 0.0f));
                drawTableChair(VAO, lightingShaderWithTexture, translateMatrix, cube9);
            }

            z += 2.25;
        }

        //faculty table
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5f, 0.0f, -0.75f));
        drawTableChair(VAO, lightingShaderWithTexture, translateMatrix * rotateYMatrix, cube9);


        //faculty table office room
       // rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(-2.0f, -1.1f, -17.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25f, 0.1f, -16.5f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 1.0f, 2.0f));
        drawTable(VAO, lightingShaderWithTexture, translateMatrix * scaleMatrix, cube9);
        //drawChair(VAO,  lightingShaderWithTexture, translateMatrix* scaleMatrix,  cube9);
        
        
        //chair draw
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.30f, 0.4f, -16.8f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        ////drawTable(VAO, lightingShaderWithTexture, translateMatrix* scaleMatrix, cube9);
        //drawChair(VAO, lightingShaderWithTexture, translateMatrix* scaleMatrix, cube9);
        for (int i = 0; i < 3; ++i) {
            glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.30f + i * 1.55f, 0.4f, -16.3f));
            glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
            drawChair(VAO, lightingShaderWithTexture, translateMatrix * scaleMatrix, cube9);
        }
       

        //chair draw 2
        for (int i = 0; i < 3; ++i) {
            glm::mat4 translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2f + i * 1.55f, 0.4f, -15.3f));
            glm::mat4 scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            drawChair(VAO, lightingShaderWithTexture, translateMatrix * scaleMatrix* rotateYMatrix, cube9);
        }

        //almirah
       // translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.4f, -2.0f, -11.5f));//-0.4f, -2.0f, -11.5f
       // scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 2.0f));
       //// rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
       // drawAlmirahWithDoors(VAO, lightingShaderWithTexture, translateMatrix* scaleMatrix, cube9);

        //back wall almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, -1.0f, -13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.0f, 2.7f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, -1.0f, -10.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 4.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

        //middlw wall almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, -1.0f, -11.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 4.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right wall almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, -1.0f, -13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 4.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

        //roof almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, 3.0f, -13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 2.8f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////floor almirah
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, -1.0f, -13.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 2.8f));
        //model = translateMatrix * scaleMatrix;
        ////color = glm::vec3(0.659f, 0.820f, 0.843f);
        ////drawCube(VAO, lightingShader, model, color);
        //cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////left door almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -1.0f, -10.2f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-DoorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.1f, -1.4f));
       // rotateYMatrix = glm::rotate(identityMatrix, glm::radians(leftDoorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix *rotateYMatrix* scaleMatrix  ;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

        ////right door almirah
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -1.0f, -13.0f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(DoorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -1.0f, -13.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.1f, 1.37f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-rightDoorAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        //color = glm::vec3(0.659f, 0.820f, 0.843f);
        //drawCube(VAO, lightingShader, model, color);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, model);


      


        //shelves
        /*glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 translateMatrix, scaleMatrix, model;*/

        float shelfHeight = 1.0f; // Distance between shelves

        for (int i = 0; i < 4; ++i) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, -1.0f + i * shelfHeight, -13.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.1f, 2.7f));
            model = translateMatrix * scaleMatrix;

            // Draw the shelf
            cube9.drawCubeWithTexture(lightingShaderWithTexture, model);
        }

        //standing structure top
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -0.5f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, 0.1f, 3.0f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.624f, 0.416f, 0.310f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube5.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube5.drawCubeWithTexture(lightingShader, model);
        }
        //cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

        //standing structure back left leg
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -0.5f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.455f, 0.235f, 0.102f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube5.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube5.drawCubeWithTexture(lightingShader, model);
        }
        //cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

        //standing structure front left leg
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, -0.5f, -1.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.455f, 0.235f, 0.102f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube5.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube5.drawCubeWithTexture(lightingShader, model);
        }
        //cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

        //standing structure back right leg
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.9f, -0.5f, -4.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.455f, 0.235f, 0.102f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube5.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube5.drawCubeWithTexture(lightingShader, model);
        }
        //cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

        //standing structure front right leg
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.9f, -0.5f, -1.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(0.455f, 0.235f, 0.102f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube5.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube5.drawCubeWithTexture(lightingShader, model);
        }
        //cube5.drawCubeWithTexture(lightingShaderWithTexture, model);

        //whiteboard room 1
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, -3.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 2.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(1.0f, 1.0f, 1.0f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube7.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube7.drawCubeWithTexture(lightingShader, model);
        }
        //cube7.drawCubeWithTexture(lightingShaderWithTexture, model);


        //whiteboard room2
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, 14.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 2.0f, 0.1f));
        model = translateMatrix * scaleMatrix;
        //color = glm::vec3(1.0f, 1.0f, 1.0f);
        //drawCube(VAO, lightingShader, model, color);
        if (flag2 == 1)
        {
            cube7.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube7.drawCubeWithTexture(lightingShader, model);
        }



        //leg1
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, -1.0f, 20.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 3.0f, 0.2f));
        //model = translateMatrix * scaleMatrix;
        ////drawCube(cubeVAO, ourShader, model, glm::vec4(0.169, 0.078, 0.024, 1.0));
        ////lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.169, 0.078, 0.024));
        //if (flag2 == 1)
        //{
        //    cube8.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube8.drawCubeWithTexture(lightingShader, model);
        //}
        //cube8.drawCubeWithTexture(lightingShaderWithTexture, model);

        //leg2
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, -1.0f, 19.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 3.0f, 0.2f));
        //model = translateMatrix * scaleMatrix;
        ////drawCube(cubeVAO, ourShader, model, glm::vec4(0.169, 0.078, 0.024, 1.0));
        ////lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.169, 0.078, 0.024));
        //if (flag2 == 1)
        //{
        //    cube8.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube8.drawCubeWithTexture(lightingShader, model);
        //}
        //cube8.drawCubeWithTexture(lightingShaderWithTexture, model);

        //leg3
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.0f, 20.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 3.0f, 0.2f));
        //model = translateMatrix * scaleMatrix;
        ////drawCube(cubeVAO, ourShader, model, glm::vec4(0.169, 0.078, 0.024, 1.0));
        ////lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.169, 0.078, 0.024));
        //if (flag2 == 1)
        //{
        //    cube8.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube8.drawCubeWithTexture(lightingShader, model);
        //}
        //cube8.drawCubeWithTexture(lightingShaderWithTexture, model);

        //leg4
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.0f, 19.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 3.0f, 0.2f));
        //model = translateMatrix * scaleMatrix;
        ////drawCube(cubeVAO, ourShader, model, glm::vec4(0.169, 0.078, 0.024, 1.0));
        ////lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.169, 0.078, 0.024));
        //if (flag2 == 1)
        //{
        //    cube8.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube8.drawCubeWithTexture(lightingShader, model);
        //}
        //cube8.drawCubeWithTexture(lightingShaderWithTexture, model);

        //slider floor
      /*  translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0, 2.0, 19.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2f, -0.1f, 1.2f));
        model = translateMatrix * scaleMatrix;
        if (flag2 == 1)
        {
            cube9.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else
        {
            cube9.drawCubeWithTexture(lightingShader, model);
        }*/
        //cube9.drawCubeWithTexture(lightingShaderWithTexture, model);
        //drawCube(cubeVAO, ourShader, model, glm::vec4(0.098, 0.114, 0.125, 1.0));
       // lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.098, 0.114, 0.125));

        //balance piller1
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.0f, 23.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.7f, 0.2f));
        //model = translateMatrix * scaleMatrix;
        ////drawCube(cubeVAO, ourShader, model, glm::vec4(0.169, 0.078, 0.024, 1.0));
        ////lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.169, 0.078, 0.024));
        //if (flag2 == 1)
        //{
        //    cube8.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube8.drawCubeWithTexture(lightingShader, model);
        //}
        //cube8.drawCubeWithTexture(lightingShaderWithTexture, model);

        //balance pilar2
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.0f, 23.5f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.7f, 0.2f));
        //model = translateMatrix * scaleMatrix;
        ////drawCube(cubeVAO, ourShader, model, glm::vec4(0.169, 0.078, 0.024, 1.0));
        ////lightEffect(cubeVAO, lightingShader, model, glm::vec3(0.169, 0.078, 0.024));
        //if (flag2 == 1)
        //{
        //    cube8.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube8.drawCubeWithTexture(lightingShader, model);
        //}
        //cube8.drawCubeWithTexture(lightingShaderWithTexture, model);

        //balance floor
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, -0.2, 23.0));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, -0.1f, 0.7f));
        //model = translateMatrix * scaleMatrix;
        //if (flag2 == 1)
        //{
        //    cube9.drawCubeWithTexture(lightingShaderWithTexture, model);
        //}
        //else
        //{
        //    cube9.drawCubeWithTexture(lightingShader, model);
        //}
        ////cube9.drawCubeWithTexture(lightingShaderWithTexture, model);

       
        //rope 1
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.8, -1.0, 20.0));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 1.0, 0.5));
        //model = translateMatrix * scaleMatrix;
        //lightingShaderWithTexture.setInt("material.diffuse", 0);
        //lightingShaderWithTexture.setInt("material.specular", 1);
        //lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
        //lightingShaderWithTexture.setMat4("model", model);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture2);
        //glBindVertexArray(ropeVAO);
        //glDrawElements(GL_TRIANGLES, (unsigned int)indicesRope.size(), GL_UNSIGNED_INT, (void*)0);

        ////rope2
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.8, -1.0, 19.3));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 1.0, 0.5));
        //model = translateMatrix * scaleMatrix;
        //lightingShaderWithTexture.setInt("material.diffuse", 0);
        //lightingShaderWithTexture.setInt("material.specular", 1);
        //lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
        //lightingShaderWithTexture.setMat4("model", model);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, texture2);
        //glBindVertexArray(ropeVAO);
        //glDrawElements(GL_TRIANGLES, (unsigned int)indicesRope.size(), GL_UNSIGNED_INT, (void*)0);

        

        /*translateMatrix = identityMatrix;
        float y = 0;
        for (int i = 0; i < 3; i++)
        {
            translateMatrix = translateMatrix * glm::translate(identityMatrix, glm::vec3(0.65, -0.5, 19.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.4f, 1.3f));
            model = translateMatrix * scaleMatrix;
            lightingShaderWithTexture.setInt("material.diffuse", 0);
            lightingShaderWithTexture.setInt("material.specular", 1);
            lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
            lightingShaderWithTexture.setMat4("model", model);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture3);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            y += 1.0;
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, y, 0.0));

        }*/

        //basin using baziercurve
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.2, 5.45, -10.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 1.4, 1.5));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix* rotateYMatrix;
        lightingShaderWithTexture.setInt("material.diffuse", 0);
        lightingShaderWithTexture.setInt("material.specular", 1);
        lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffMap13);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specMap13);
        glBindVertexArray(sphereVAO);
        lightingShaderWithTexture.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, (unsigned int)indicesSphere1.size(), GL_UNSIGNED_INT, (void*)0);



        //basin2 using baziercurve
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2, 5.45, -10.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 1.4, 1.5));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix * rotateYMatrix;
        lightingShaderWithTexture.setInt("material.diffuse", 0);
        lightingShaderWithTexture.setInt("material.specular", 1);
        lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffMap13);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specMap13);
        glBindVertexArray(sphereVAO);
        lightingShaderWithTexture.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, (unsigned int)indicesSphere1.size(), GL_UNSIGNED_INT, (void*)0);



        //basin3 using baziercurve
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.8, 5.45, -10.75));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 1.4, 1.5));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix * rotateYMatrix;
        lightingShaderWithTexture.setInt("material.diffuse", 0);
        lightingShaderWithTexture.setInt("material.specular", 1);
        lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffMap13);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specMap13);
        glBindVertexArray(sphereVAO);
        lightingShaderWithTexture.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, (unsigned int)indicesSphere1.size(), GL_UNSIGNED_INT, (void*)0);

    

        //slider using bezier curve
       // translateMatrix = glm::translate(identityMatrix, glm::vec3(3.7, -0.6, 19.5));
       // scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.4, 0.5, 0.5));
       //// rotateYMatrix = glm::rotate(identityMatrix, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
       // rotateZMatrix = glm::rotate(identityMatrix, glm::radians(111.5f), glm::vec3(0.0f, 0.0f, 1.0f)); 
       //// rotateYMatrix = glm::rotate(rotateZMatrix, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
       // model = translateMatrix *  rotateZMatrix * scaleMatrix;
       // lightingShaderWithTexture.setInt("material.diffuse", 0);
       // lightingShaderWithTexture.setInt("material.specular", 1);
       // lightingShaderWithTexture.setFloat("material.shininess", 32.0f);
       // glActiveTexture(GL_TEXTURE0);
       // glBindTexture(GL_TEXTURE_2D, diffMap6);
       // glActiveTexture(GL_TEXTURE1);
       // glBindTexture(GL_TEXTURE_2D, specMap6);
       // glBindVertexArray(sphereVAO);
       // lightingShaderWithTexture.setMat4("model", model);
       // glDrawElements(GL_TRIANGLES, (unsigned int)indicesSphere.size(), GL_UNSIGNED_INT, (void*)0);

        //glfw swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    //optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //glfw terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}

void drawFan(unsigned int VAO, Shader lightingShader, glm::mat4 matrix) {
    //define matrices and vectors needed
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, RotateTranslateMatrix, InvRotateTranslateMatrix;
    glm::vec3 color;

    //when fan is on
    if (fanOn) {
        //fan rod
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.28f, 3.5f, 1.61f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.75f, 0.1f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(0.0f, 0.0f, 0.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan middle
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.13f, 2.75f, 1.46f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.0f, -0.2f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.0f, 0.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, -0.1f, 0.4f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        color = glm::vec3(0.0f, 0.0f, 0.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.13f, 2.75f, 1.56f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.0f, -0.1f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.0f, 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.75f, -0.1f, 0.2f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.53f, 2.75f, 1.56f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.0f, -0.1f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.0f, 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, -0.1f, 0.2f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars up
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.23f, 2.75f, 1.46f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.0f, -0.2f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.0f, 0.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -0.1f, -0.75f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars down
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.23f, 2.75f, 1.86f));
        RotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, 0.0f, 0.2f));
        InvRotateTranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 0.0f, -0.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -0.1f, 0.75f));
        model = matrix * translateMatrix * InvRotateTranslateMatrix * rotateYMatrix * RotateTranslateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        r += 1.0f;
    }

    //when fan is off
    else {
        //fan rod
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.28f, 3.5f, 1.61f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.75f, 0.1f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(0.0f, 0.0f, 0.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan middle
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.13f, 2.75f, 1.46f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, -0.1f, 0.4f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(0.0f, 0.0f, 0.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars left
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.13f, 2.75f, 1.56f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.75f, -0.1f, 0.2f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.53f, 2.75f, 1.56f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.75f, -0.1f, 0.2f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars up
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.23f, 2.75f, 1.46f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -0.1f, -0.75f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);

        //fan propelars down
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.23f, 2.75f, 1.86f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, -0.1f, 0.75f));
        model = matrix * translateMatrix * scaleMatrix;
        color = glm::vec3(1.0f, 1.0f, 1.0f);
        drawCube(VAO, lightingShader, model, color);
    }
}

void drawTableChair(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c) {
    //define matrices and vectors needed
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    glm::vec3 color;

    //table top
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
    model = matrix * scaleMatrix;
    color = glm::vec3(0.882f, 0.710f, 0.604f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //table left leg back
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -1.0f, 0.1f));
    model = matrix * scaleMatrix;
    //color = glm::vec3(0.647f, 0.408f, 0.294f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //table right leg back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -1.0f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.647f, 0.408f, 0.294f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //table leg left front
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -1.0f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.647f, 0.408f, 0.294f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //table leg right front
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.0f, 0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -1.0f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.647f, 0.408f, 0.294f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //chair mid section
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.5f, 1.15f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.1f, 0.5f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.455f, 0.235f, 0.102f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //chair leg back left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.5f, 1.15f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.329f, 0.173f, 0.110f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //chair leg front left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.5f, 1.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.329f, 0.173f, 0.110f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //chair leg front right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, -0.5f, 1.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.329f, 0.173f, 0.110f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //chair leg back right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, -0.5f, 1.15f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    //color = glm::vec3(0.329f, 0.173f, 0.110f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    //chair upper piller left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.4f, 1.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.65f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    color = glm::vec3(0.329f, 0.173f, 0.110f);
    //drawCube(VAO, lightingShader, model, color);
    c.drawCubeWithTexture(lightingShaderWithTexture, model);
}

//Table
void drawTable(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, scaleMatrix, model;

    // Table top
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
    model = matrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Table left leg back
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, -1.0f, 0.05f));
    model = matrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Table right leg back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, -1.0f, 0.05f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Table leg left front
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, -1.0f, 0.05f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Table leg right front
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.9f, 0.0f, 0.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, -1.0f, 0.05f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);
}



//Chair
void drawChair(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, scaleMatrix, model;

    // Chair mid section
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.5f, 1.15f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.1f, 0.5f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Chair leg back left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.5f, 1.15f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Chair leg front left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.5f, 1.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Chair leg front right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, -0.5f, 1.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Chair leg back right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.65f, -0.5f, 1.15f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -0.5f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);

    // Chair upper pillar left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, -0.4f, 1.55f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.65f, 0.1f));
    model = matrix * translateMatrix * scaleMatrix;
    c.drawCubeWithTexture(lightingShaderWithTexture, model);
}




//almirah code
//void drawAlmirahWithDoors(unsigned int VAO, Shader lightingShaderWithTexture, glm::mat4 matrix, Cube c) {
//    glm::mat4 identityMatrix = glm::mat4(1.0f);
//    glm::mat4 translateMatrix, scaleMatrix, rotateMatrix, model;
//
//    // Main body of the almirah
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f, 0.0f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 3.0f, 0.5f));
//    model = matrix * translateMatrix * scaleMatrix;
//    c.drawCubeWithTexture(lightingShaderWithTexture, model);
//
//    // Left door
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.75f, 0.5f, 0.25f)); // Translate to hinge position
//    rotateMatrix = glm::rotate(identityMatrix, glm::radians(leftDoorAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
//    translateMatrix = glm::translate(translateMatrix, glm::vec3(0.35f, 0.0f, 0.0f)); // Offset the door
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 2.8f, 0.02f));
//    model = matrix * translateMatrix * rotateMatrix * scaleMatrix;
//    c.drawCubeWithTexture(lightingShaderWithTexture, model);
//
//    // Right door
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75f, 0.5f, 0.25f)); // Translate to hinge position
//    rotateMatrix = glm::rotate(identityMatrix, glm::radians(-rightDoorAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
//    translateMatrix = glm::translate(translateMatrix, glm::vec3(-0.35f, 0.0f, 0.0f)); // Offset the door
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 2.8f, 0.02f));
//    model = matrix * translateMatrix * rotateMatrix * scaleMatrix;
//    c.drawCubeWithTexture(lightingShaderWithTexture, model);
//
//    // Shelves inside the almirah
//    for (int i = 0; i < 3; ++i) {
//        float yOffset = -0.5f + i * 1.0f; // Adjust vertical position
//        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, yOffset, 0.0f));
//        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 0.05f, 0.4f));
//        model = matrix * translateMatrix * scaleMatrix;
//        c.drawCubeWithTexture(lightingShaderWithTexture, model);
//    }
//}



//bezier function definition
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}




//hollowbezier function definition
unsigned int hollowBezier(GLfloat ctrlpoints[], int L, vector<float>& coordinates, vector<float>& normals, vector<int>& indices, vector<float>& vertices, float div = 1.0)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal

    const float dtheta = (2 * pi / ntheta) / div;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];
    vector<float> textureCoords;

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            // Calculate (x, y, z) coordinates using parametric equations
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = -(x - 0) * lengthInv;
            ny = -(y - y) * lengthInv;
            nz = -(z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            // Texture coordinates (u, v)
            float u = float(j) / float(ntheta); // Around the circle
            float v = float(i) / float(nt);     // Along the curve
            textureCoords.push_back(u);
            textureCoords.push_back(v);

            // Increment theta for next iteration
            theta += dtheta;
        }
    }

    // Generate index list of triangles
    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // Create two triangles for each segment
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    // Store the vertex data (positions, normals, texture coordinates)
    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);

        // Add texture coordinates
        vertices.push_back(textureCoords[i / 3 * 2]);
        vertices.push_back(textureCoords[i / 3 * 2 + 1]);
    }

    // Create VAO, VBO, and EBO for OpenGL rendering
    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // Create VBO to copy vertex data to GPU
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // For vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // Target
        (unsigned int)vertices.size() * sizeof(float), // Size in bytes
        vertices.data(),   // Pointer to vertex data
        GL_STATIC_DRAW);                   // Usage

    // Create EBO to copy index data to GPU
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // For index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // Target
        (unsigned int)indices.size() * sizeof(unsigned int),             // Size in bytes
        indices.data(),               // Pointer to index data
        GL_STATIC_DRAW);                   // Usage

    // Enable vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Set attribute pointers
    int stride = 32;     // Should be 32 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);            // Vertex position
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3)); // Normal
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float))); // Texture Coord

    // Unbind VAO, VBO, and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}


//read file
void read_file(string file_name, vector<float>& vec)
{
    ifstream file(file_name);
    float number;

    while (file >> number)
        vec.push_back(number);

    file.close();
}


//texture
void load_texture(unsigned int& texture, string image_name, GLenum format)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture " << image_name << endl;
    }
    stbi_image_free(data);
}

//ncr

long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//lightingeffect
void lightEffect(unsigned int VAO, Shader lightShader, glm::mat4 model, glm::vec3 color)
{
    lightShader.use();
    lightShader.setVec3("material.ambient", color);
    lightShader.setVec3("material.diffuse", color);
    lightShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightShader.setFloat("material.shininess", 32.0f);

    lightShader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}


void drawCube(unsigned int& VAO, Shader& lightingShader, glm::mat4 model, glm::vec3 color)
{
    //use the shadder
    lightingShader.use();

    //define lighting properties
    lightingShader.setVec3("material.ambient", color);
    lightingShader.setVec3("material.diffuse", color);
    lightingShader.setVec3("material.specular", color);
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

//process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if(!birdEyeView)
            camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(UP, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(P_UP, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(P_DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(R_LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        if (!birdEyeView)
            camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        fanOn = !fanOn;
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        birdEyeView = !birdEyeView;
    }

    if (birdEyeView) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            birdEyePosition.z -= birdEyeSpeed * deltaTime; // Move forward along Z
            birdEyeTarget.z -= birdEyeSpeed * deltaTime;
            if (birdEyePosition.z <= 2.0) {
                birdEyePosition.z = 2.0;
            }
            if (birdEyeTarget.z <= -4.0) {
                birdEyeTarget.z = -4.0;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            birdEyePosition.z += birdEyeSpeed * deltaTime; // Move backward along Z
            birdEyeTarget.z += birdEyeSpeed * deltaTime;
            if (birdEyePosition.z >= 13.5) {
                birdEyePosition.z = 13.5;
            }
            if (birdEyeTarget.z >= 7.5) {
                birdEyeTarget.z = 7.5;
            }
        }
    }

    /*
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {   
        if (!birdEyeView) {
            theta += 0.01f;
            camera.Position.x = lookAtX + radius * sin(theta);
            camera.Position.y = lookAtY;
            camera.Position.z = lookAtZ + radius * cos(theta);
        }
    }
    */

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        if (pointlight1.ambientOn > 0 && pointlight1.diffuseOn > 0 && pointlight1.specularOn > 0) {
            pointlight1.turnOff();
            point1 = false;
        }    
        else {
            pointlight1.turnOn();
            point1 = true;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        if (pointlight2.ambientOn > 0 && pointlight2.diffuseOn > 0 && pointlight2.specularOn > 0) {
            pointlight2.turnOff();
            point2 = false;
        }            
        else {
            pointlight2.turnOn();
            point2 = true;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        directionLightOn = !directionLightOn;
    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        spotLightOn = !spotLightOn;
    }

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        if (pointlight1.ambientOn > 0 || pointlight2.ambientOn > 0) {
            if(point1)
                pointlight1.turnAmbientOff();
            if(point2)
                pointlight2.turnAmbientOff();
        }
        else {
            if(point1)
                pointlight1.turnAmbientOn();
            if(point2)
                pointlight2.turnAmbientOn();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        if (flag2 == 1)
        {
            flag2 = 0;
        }
        else
        {
            flag2 = 1;
        }
    }


    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        if (pointlight1.diffuseOn > 0 || pointlight2.diffuseOn > 0) {
            if (point1)
                pointlight1.turnDiffuseOff();
            if (point2)
                pointlight2.turnDiffuseOff();
        }
        else {
            if (point1)
                pointlight1.turnDiffuseOn();
            if (point2)
                pointlight2.turnDiffuseOn();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        if (pointlight1.specularOn > 0 || pointlight2.specularOn > 0) {
            if (point1)
                pointlight1.turnSpecularOff();
            if (point2)
                pointlight2.turnSpecularOff();
        }
        else {
            if (point1)
                pointlight1.turnSpecularOn();
            if (point2)
                pointlight2.turnSpecularOn();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        openDoor = true;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        openDoor = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        isDoorOpen = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        isDoorOpen = false;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        closedoor = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        closedoor = false;
    }

   

}

//glfw whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //make sure the viewport matches the new window dimensions; note that width and height will be significantly larger than specified on retina displays.
    float aspectRatio = 4.0f / 3.0f;
    int viewWidth, viewHeight;

    if (width / (float)height > aspectRatio) {
        //Window is too wide, fit height and adjust width
        viewHeight = height;
        viewWidth = (int)(height * aspectRatio);
    }
    else {
        //Window is too tall, fit width and adjust height
        viewWidth = width;
        viewHeight = (int)(width / aspectRatio);
    }

    //Center the viewport
    int xOffset = (width - viewWidth) / 2;
    int yOffset = (height - viewHeight) / 2;

    glViewport(xOffset, yOffset, viewWidth, viewHeight);
    //glViewport(0, 0, width, height);
}

//glfw whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;       //reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

//glfw whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format{};
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


