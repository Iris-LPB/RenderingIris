#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu

int main()
{
    // Initialisation
   
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut
    
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE); // On peut configurer l'équation qui mélange deux couleurs, comme pour faire différents blend mode dans Photoshop. Cette équation-ci donne le blending "normal" entre pixels transparents.


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
        glClearColor(0.2,0.,0.2, 0.1); 
        glClear(GL_COLOR_BUFFER_BIT);
        // Rendu à chaque frame
        shader.bind();
        shader.set_uniform("aspect_ratio", gl::framebuffer_aspect_ratio());
        shader.set_uniform("time_elapsed", gl::time_in_seconds());
        triangle_mesh.draw();     
    }
}