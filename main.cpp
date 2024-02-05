
#include <kite.hpp> // main wrapper functions
#include "stb_image.h" // stbi_load, stbi_image_free, stbi_flip_vertically_on_load


static int WINDOW_WIDTH  = 800;
static int WINDOW_HEIGHT = 600;

int main() {

    // initialize kite and make a window

    kite::init();
    kite::window(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL window");


    // make a projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 10.0f); 
    projection *= glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),  // camera pos
                              glm::vec3(0.0f, 0.0f, 0.0f),  // camera lookat
                              glm::vec3(0.0f, 1.0f, 0.0f)); // camera up


    // load an image using stb_image
    int w, h, n;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/cat.jpg", &w, &h, &n, 0);
    Texture tex(w, h, false, data);
    stbi_image_free(data);

    // initialize models to be used
    Plane flat; // a plane which fills the entire window, used to draw final image, it is 3d, put is initialized to fill the viewport
    Cube cube; // a simple unit cube

    // initialize shaders, dither is post-process, normal is a standard shader.
    Shader dither("shaders/dither.vs", "shaders/dither.fs", {"in_Quad", "in_Tex"});
    Shader normal("shaders/cube.vs", "shaders/cube.fs", {"in_Quad", "in_Tex"});

    // make a render target to draw the cube before applying the dither effect
    Billboard draw(WINDOW_WIDTH, WINDOW_HEIGHT);

    // main loop
    while(kite::running()) {

        kite::poll();



        draw.target(true); // all draw calls are now to the render target texture

        normal.use(); // use a normal shader, no fancy stuff here, just draws
        normal.uniform("projection", projection); // set uniforms
        normal.texture("imageTexture", tex);
        // apply a rotation over time
        // TODO: remove glfwgettime
        cube.model = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime()*50), glm::vec3(1.0, 0.3, 0.5));
        normal.uniform("model", cube.model); // make the shader use the model
        cube.render(); // render the cube

        // switch back to drawing on window
        kite::targetwindow();

        // swap to dither shader
        dither.use();
        dither.uniform("pres", 8);  // set uniforms
		dither.uniform("cres", 32);
        dither.texture("imageTexture", draw.texture);   // use the texture we just drew on
        dither.uniform("model", glm::mat4(1.0f));       // use identities to make sure the plane fills the entire screen
        dither.uniform("projection", glm::mat4(1.0f));  
        flat.render(); // render the plane

        // finalize all drawing
        kite::end_draw();
    }

    kite::close();

    return 0;

}