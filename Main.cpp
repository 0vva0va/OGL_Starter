#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "shader_t.h"


#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720



const float padding   = 10.0f;  // imgui padding from screen edge
static bool wireframe = false;  // wireframe mode toggle



// ------------- camera setup + callbacks -------------
static Camera* gCamera     = nullptr;
static bool gCamera_active = true;

void KeyCallback(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        gCamera_active = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (gCamera) gCamera -> Reset_Mouse();
        return;
    }
    if (gCamera) gCamera -> On_Key(key, action);
}

void MouseCallback(GLFWwindow*, double x, double y) {
    if (gCamera && gCamera_active) gCamera -> On_Mouse_Move(x, y);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureMouse) {
            gCamera_active = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if (gCamera) gCamera -> Reset_Mouse();
        }
    }
}



// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

int main() {
    // -------------glfw init -------------
    if (!glfwInit()) 
    {
        std::cerr << "Failed to init GLFW\n"; 
        return -1; 
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_SAMPLES, 4);
     

    // ------------- glfw window -------------
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Main", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    // -------------glad init -------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to init GLAD\n"; 
        return -1;
    }


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);  

    
    Camera camera;
    gCamera = &camera;

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // ------------- imgui init -------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io     = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    // ------------- timing -------------
    float last_time = (float)glfwGetTime();
    float frameTime = 0.0f;

    // ------------- shader init -------------


    // ------------------------------------------
    // ------------- GLFW MAIN LOOP -------------
    while (!glfwWindowShouldClose(window)) {
        float now = (float)glfwGetTime();
        float dt  = now - last_time;
        last_time = now;
        frameTime += dt;

        glfwPollEvents();

        camera.Update(dt);

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        float aspect = (float)w / (float)h;

        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ------------- render terrain & sky -------------
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view  = camera.Get_View_Matrix();
        glm::mat4 proj  = camera.Get_Projection_Matrix(aspect);

        // ------------- imgui frame -------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImVec2 windowPos   = ImVec2(ImGui::GetIO().DisplaySize.x - padding, padding);
        ImVec2 windowPivot = ImVec2(1.0f, 0.0f);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPivot);
        ImGui::SetNextWindowSize(ImVec2(250, 0), ImGuiCond_Always);

        ImGui::Begin("Controls");

        ImGui::Separator();

        ImGui::Text("Camera");
        ImGui::SliderFloat("Speed", &camera.speed, 1.0f, 100.0f);
        ImGui::SliderFloat("FOV", &camera.fov, 30.0f, 120.0f);

        ImGui::Separator();

        ImGui::Text("Wireframe Mode");
        ImGui::Text(wireframe ? "Enabled" : "Disabled");
        if (ImGui::IsItemClicked(ImGui::Button("Use Wireframe"))) 
        {
            wireframe = !wireframe;
            wireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        ImGui::Separator();
        ImGui::Text("FPS: %.1f", 1.0f / dt);
        
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // ------------- cleanup -------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
