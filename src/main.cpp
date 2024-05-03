#include "opengl-framework/opengl-framework.hpp" // Inclue la librairie qui va nous servir à faire du rendu

int main()
{
    // Initialisation
    gl::init("TPs de Rendering"); // On crée une fenêtre et on choisit son nom
    gl::maximize_window(); // On peut la maximiser si on veut
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
        // Rendu à chaque frame
        glClearColor(0.f, 0.f, 1.f, 1.f); // Choisis la couleur à utiliser. Les paramètres sont R, G, B, A avec des valeurs qui vont de 0 à 1
        glClear(GL_COLOR_BUFFER_BIT); // Exécute concrètement l'action d'appliquer sur tout l'écran la couleur choisie au-dessus
        shader.bind();
        triangle_mesh.draw();
    }
}