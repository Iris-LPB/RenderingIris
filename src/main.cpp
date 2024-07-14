#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu
#include <iostream>
#include "glm/ext/matrix_clip_space.hpp"

int main()
{
    // Initialisation
   
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut
    
    //glEnable(GL_BLEND);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE); // On peut configurer l'équation qui mélange deux couleurs, comme pour faire différents blend mode dans Photoshop. Cette équation-ci donne le blending "normal" entre pixels transparents.
    auto camera = gl::Camera{};
    gl::set_events_callbacks({
        camera.events_callbacks(), 
        {
            .on_mouse_pressed = [&](gl::MousePressedEvent const& e) {
            std::cout << "Mouse pressed at " << e.position.x << " " << e.position.y << '\n';
        },
    },
    });

    auto const triangle_mesh = gl::Mesh{{
        .vertex_buffers = {{
            .layout = {gl::VertexAttribute::Position2D{0}},
            .data   = {
                -0.5f, -0.5f,    
                -0.5f, 0.5f,
                0.5f, 0.5f,  
                0.5f, -0.5f,
            },
        }},
        .index_buffer   = {
            0, 1, 2,
            0, 2, 3
        },
    }};

    auto const shader = gl::Shader{{
        .vertex     = gl::ShaderSource::File{"res/vertex.glsl"},
        .fragment   = gl::ShaderSource::File{"res/fragment.glsl"},
    }};


    while (gl::window_is_open())
    {
        glm::mat4 const view_matrix = camera.view_matrix();
        glm::mat4 const projection_matrix = glm::infinitePerspective(90.f /*field of view in radians*/, gl::framebuffer_aspect_ratio() /*aspect ratio*/, 0.001f /*near plane*/);
        glm::mat4 combined_matrix = projection_matrix * view_matrix;
        glClearColor(0.2,0.,0.2, 0.1); 
        glClear(GL_COLOR_BUFFER_BIT);
        // Rendu à chaque frame
        shader.bind();
        shader.set_uniform("time_elapsed", gl::time_in_seconds());
        shader.set_uniform("view_projection_matrix", combined_matrix);
        triangle_mesh.draw();     
    }
}