/*
 * Projeto2 - Demonstração de OpenGL com C++.
 * Copyright (C) 2025 Cleuton Sampaio <https://www.cleutonsampaio.com >
 *
 * Este programa é software livre: você pode redistribuí-lo e/ou modificá-lo
 * sob os termos da Licença Pública Geral GNU, conforme publicada pela Free Software Foundation,
 * seja a versão 3 da Licença, ou (a seu critério) qualquer versão posterior.
 *
 * Este programa é distribuído na esperança de que seja útil, mas SEM NENHUMA GARANTIA;
 * sem mesmo a garantia implícita de COMERCIABILIDADE ou ADEQUAÇÃO A UM PROPÓSITO PARTICULAR.
 * Consulte a Licença Pública Geral GNU para obter mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este programa.
 * Se não, veja <https://www.gnu.org/licenses/ >.
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// vértices do cubo (36 vértices, 6 faces × 2 triângulos × 3 vértices)
/* 
    Eu sei que você pode carregar isso de um arquivo ou gerar os elementos
    com um loop "for", mas para este exemplo simples, vamos definir os vértices diretamente.
    Cada vértice tem 3 coordenadas (x, y, z) e 3 componentes de cor (r, g, b).
    Cada face do cubo é composta por dois triângulos, totalizando 36 vértices.
*/
float cubeVertices[] = {
    // posições          // cores
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.2f, 0.3f, 0.4f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  0.2f, 0.3f, 0.4f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.2f, 0.3f, 0.4f,

     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.2f, 0.3f, 0.4f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f
};

// vertex shader com matrizes
/*  Um Vertex Shader é um programa executado pela GPU que processa cada vértice da geometria.
    Ele define posição final na tela, cor, coordenadas de textura, etc.
    Neste exemplo, o shader recebe posição e cor de cada vértice, aplica transformações (modelo-visão-projeção)
    e passa a cor para o fragment shader. */
const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;

out vec3 fragColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    fragColor = col;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}
)";

// fragment shader simples
/*
    Um Fragment Shader é um programa executado pela GPU que determina a cor final de cada pixel (fragmento).
    Neste exemplo, o shader recebe uma cor interpolada dos vértices e a aplica diretamente ao pixel.
 */
const char* fragmentShaderSrc = R"(
#version 330 core
in vec3 fragColor;
out vec4 outColor;
void main() {
    outColor = vec4(fragColor, 1.0);
}
)";

int main() {
    // init GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* win = glfwCreateWindow(800, 600, "Cubo Rotativo", nullptr, nullptr);
    if (!win) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(win);

    // init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr<<"Falha ao carregar GLAD\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    // compila shaders
    auto compile = [&](GLenum type, const char* src) {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        return s;
    };
    GLuint vs = compile(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs); glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs); glDeleteShader(fs);

    // VBO + VAO
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    // posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // cor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // local das uniformes
    GLint uniProj  = glGetUniformLocation(prog, "projection");
    GLint uniView  = glGetUniformLocation(prog, "view");
    GLint uniModel = glGetUniformLocation(prog, "model");

    // cria matriz de projeção (perspectiva)
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f, 100.0f
    );

    // loop principal
    while (!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // calcula view e model
        glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.0f));
        float t = (float)glfwGetTime();
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), t, glm::vec3(0.5f, 1.0f, 0.0f));

        // envia uniformes
        glUseProgram(prog);
        glUniformMatrix4fv(uniProj,  1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniView,  1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

        // desenha
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    // cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(prog);
    glfwTerminate();
    return 0;
}
