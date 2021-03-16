#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<shader.h>
#include<bits/stdc++.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


glm::mat4 trans_rotate = glm::mat4(1.0f);

glm::mat4 translate_shape = glm::mat4(1.0f);
glm::vec4 object_starting_position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

double angle = 0;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void read(string file_name, float vertices[], int nums) {
    int ind = 0;

    fstream file_stream;
    file_stream.open(file_name, ios::in);
    for(int i = 0; i < nums; i++) {
        file_stream >> vertices[ind++];
    }
    return;
}

void processInput(GLFWwindow* window) {
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    /*
        moving the camera along 3 axis.
        keys: {W, A, S, D, Q, E}
    */
    const float cameraSpeed = 0.0005f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    } else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    } else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    } else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    } else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraUp;
    } else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraUp;
    }

    /*
        spinning the object about its 3 axis.
        keys: {Z, X, C}
    */
    const float rotation_speed = 0.01f;
    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        trans_rotate = glm::rotate(trans_rotate, glm::radians(rotation_speed), glm::vec3(1.0f, 0.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        trans_rotate = glm::rotate(trans_rotate, glm::radians(rotation_speed), glm::vec3(0.0f, 1.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        trans_rotate = glm::rotate(trans_rotate, glm::radians(rotation_speed), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    /*
        moving the object along 3 axis.
        keys: {I, K, J, L, U, O}
    */
    const float objectSpeed = 0.0005f;
    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        translate_shape = glm::translate(translate_shape, objectSpeed * glm::vec3(0.0f, 0.0f, -1.0f));
    } else if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        translate_shape = glm::translate(translate_shape, objectSpeed * glm::vec3(0.0f, 0.0f, 1.0f));
    } else if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        translate_shape = glm::translate(translate_shape, objectSpeed * glm::vec3(-1.0f, 0.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        translate_shape = glm::translate(translate_shape, objectSpeed * glm::vec3(1.0f, 0.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        translate_shape = glm::translate(translate_shape, objectSpeed * glm::vec3(0.0f, 1.0f, 0.0f));
    } else if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        translate_shape = glm::translate(translate_shape, objectSpeed * glm::vec3(0.0f, -1.0f, 0.0f));
    }

    /*
        moving the camera to 3 pre determined locations.
        camera will always face the object.
        keys: {B, N, M}
    */
    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        glm::vec4 object_current_position = translate_shape * object_starting_position;
        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraFront = glm::vec3(object_current_position.x - cameraPos.x, object_current_position.y - cameraPos.y, object_current_position.z - cameraPos.z);
    } else if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        glm::vec4 object_current_position = translate_shape * object_starting_position;
        cameraPos = glm::vec3(-3.0f, -4.0f, -5.0f);
        cameraFront = glm::vec3(object_current_position.x - cameraPos.x, object_current_position.y - cameraPos.y, object_current_position.z - cameraPos.z);
    } else if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        glm::vec4 object_current_position = translate_shape * object_starting_position;
        cameraPos = glm::vec3(3.0f, 3.0f, 3.0f);
        cameraFront = glm::vec3(object_current_position.x - cameraPos.x, object_current_position.y - cameraPos.y, object_current_position.z - cameraPos.z);
    }

    /*
        spinning the camera about the object.
        camera is first transfered to a place close to the object.
        key: R
    */
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        translate_shape = glm::mat4(1.0f);
        glm::vec4 object_current_position = translate_shape * object_starting_position;
        
        const float radius = 3.0f;
        // float x1 = object_current_position.x;
        // float y1 = object_current_position.y;
        // float z1 = object_current_position.z;
        // float x2 = cameraPos.x;
        // float y2 = cameraPos.y;
        // float z2 = cameraPos.z;

        // const float radius = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));

        float camX = sin(angle) * radius;
        float camZ = cos(angle) * radius;
        cameraPos = glm::vec3(object_current_position.x + camX, object_current_position.y, object_current_position.z + camZ);
        angle += 0.001;
        if(angle > 100000.0) {
            angle = 0;
        }
        cameraFront = glm::vec3(object_current_position.x - cameraPos.x, object_current_position.y - cameraPos.y, object_current_position.z - cameraPos.z);
    }

}

int main() {
    
    cout << "Enter the shape of choice (1, 2, 3):\n";
    cout << "1. Elongated Square Pyramid\n";
    cout << "2. Decagonal Prism\n";
    cout << "3. Hexagonal Dipyramid\n";
    int choice, vertices;
    cin >> choice;

    if(choice != 1 && choice != 2 && choice != 3) {
        cout << "You must enter 1 or 2 or 3\n";
        return 0;
    }
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD \n";
        return -1; 
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    /* 
        Reading the coordinates for 3 shapes along with color of each vertex    
    */
    float vertices_elongated_square_pyramid[288];
    read("../shapes/elongatedSquarePyramid.txt", vertices_elongated_square_pyramid, 288);

    float vertices_decagonal_prism[648];
    read("../shapes/decagonalPrism.txt", vertices_decagonal_prism, 648);

    float vertices_hexagonal_dipyramid[216];
    read("../shapes/hexagonalDipyramid.txt", vertices_hexagonal_dipyramid, 216);


    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if(choice == 1) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_elongated_square_pyramid), vertices_elongated_square_pyramid, GL_STATIC_DRAW);
        vertices = 48;
    } else if(choice == 2) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_decagonal_prism), vertices_decagonal_prism, GL_STATIC_DRAW);
        vertices = 108;
    } else if(choice == 3) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_hexagonal_dipyramid), vertices_hexagonal_dipyramid, GL_STATIC_DRAW);
        vertices = 36;
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    char vShaderLocation[] = "~/college/3rd_year/6th_sem/Computer_Graphics/A0/source/shader.vs";
    char fShaderLocation[] = "~/college/3rd_year/6th_sem/Computer_Graphics/A0/source/shader.fs";
    Shader ourShader(vShaderLocation, fShaderLocation);
    
    float rotate = 0.01f;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    const float radius = 10.0f;

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    ourShader.use();
    ourShader.setMat4("model", model);
    ourShader.setMat4("projection", projection);

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        ourShader.setMat4("transform", trans_rotate);
        ourShader.setMat4("translate", translate_shape);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glm::vec4 currentPosition = translate_shape * object_starting_position;
    }
    glfwTerminate();
    return 0;
}
