/*Made by Etienne PENAULT*/
/*TODO - Resize function - DONE*/

#include "head.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void windowRatio(GLFWwindow* window,int width, int height);

/*Variables about windows size, TMP for the aspect ratio*/
static float WIDTH = 1600,WIDTH_TMP = 1600;
static float HEIGHT = 1000, HEIGHT_TMP = 1000;

/*Uniform variables*/
static glm::vec2 resizeRatio = glm::vec2(1,1);
static GLfloat x,y,zoom = 1.0;

int main(int argc, char **argv){

	/*Hold no argument launching*/
	std::string selectedShader;
	if(argv[1] == nullptr){
		std::cout << "No Fragment Shader selected." << std::endl;
		std::cout << "Shaders/mandel.fs selected by default" << std::endl;
		selectedShader = "Shaders/mandel.fs";
		std::cout << "Use: ./fractal fragmentShader.fs\n" << std::endl;
	}else{
		selectedShader = argv[1];
	}

	/*Initializing our window*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    //For MacOS
#endif

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3t13nn3", NULL/*glfwGetPrimaryMonitor()*/, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*GLAD initialization*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* If screen is initialized with lower resolution than the one set : */
    {
    	GLint vp[4];
		glGetIntegerv( GL_VIEWPORT, vp);
		unsigned int width, height;
		width = vp[2];
   		height = vp[3];


		WIDTH = width;
		WIDTH_TMP = width;

		HEIGHT = height;
		HEIGHT_TMP = height;

    }

    /*Initializing shader*/
	Shader fractalShader(selectedShader, "./Shaders/fractal.vs");
	

	/*Vertices for the form where we draw*/
	float vertices[] = {
        // positions
        -1.f, -1.f, -1.f,
         1.f, -1.f, -1.f,
         1.f,  1.f, -1.f,
         1.f,  1.f, -1.f,
        -1.f,  1.f, -1.f,
        -1.f, -1.f, -1.f,
    };

	unsigned int fractalVAO, fractalVBO;

	glGenBuffers(1, &fractalVBO);

	glBindBuffer(GL_ARRAY_BUFFER, fractalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glGenVertexArrays(1, &fractalVAO);
	glBindVertexArray(fractalVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window)){

			// input
			processInput(window);

	        fractalShader.use();
	        /*Uniform variables*/
	        fractalShader.setFloat("time",glfwGetTime());
	        fractalShader.setFloat("X",x);
	        fractalShader.setFloat("Y",y);
	        fractalShader.setFloat("Zoom",zoom);
	        fractalShader.setVec2("ratio",resizeRatio);
	        fractalShader.setVec2("screenSize", glm::vec2(WIDTH, HEIGHT));
	    
	        glBindVertexArray(fractalVAO);
	        glDrawArrays(GL_TRIANGLES, 0, 6);

			glfwSwapBuffers(window);
			glfwPollEvents();
    }
	

	glDeleteVertexArrays(1, &fractalVAO);
	glDeleteBuffers(1, &fractalVBO);

    glfwTerminate();


    return 0;
}


/*Resize*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    windowRatio(window, width, height);
    glViewport(0, 0, width, height);
}


/*Handle inputs*/
void processInput(GLFWwindow* window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			x += 0.6/((zoom+600)/50.0f);
		}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			x -= 0.6/((zoom+600)/50.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			y += 0.6/((zoom+600)/50.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			y -= 0.6/((zoom+600)/50.0f);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			zoom*= 1.025;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			zoom /= 1.025;	
}

/*Keep the ratio aspect during resize*/
void windowRatio(GLFWwindow* window,int width, int height){
	WIDTH = width;
    HEIGHT = height;
    if(WIDTH_TMP < WIDTH){
    	resizeRatio.x/= WIDTH/WIDTH_TMP;    
  	}else if(WIDTH_TMP > WIDTH){
  		resizeRatio.x/= WIDTH/WIDTH_TMP;
  	}
  	if(HEIGHT_TMP < HEIGHT){
    	resizeRatio.y/= HEIGHT/HEIGHT_TMP;
  	}else if(HEIGHT_TMP > HEIGHT){
  		resizeRatio.y/= HEIGHT/HEIGHT_TMP;
  	}
  	WIDTH_TMP = WIDTH;
  	HEIGHT_TMP = HEIGHT;
  	glfwSetWindowAspectRatio(window,(width/resizeRatio.y)+1,(height/resizeRatio.x)+1);
}