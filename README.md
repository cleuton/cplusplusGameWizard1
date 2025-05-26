![](../logo.png)

# C++ Game Wizard - Técnicas de programação de games com C++

[**Cleuton Sampaio**](https://linkedin.com/in/cleutonsampaio), autor do livro: 
- **Manual do Indie Game Developer**, Editora Ciência Moderna.

![](../51Fs8fPE4JL._SY342_.jpg)

Aposto que, depois de criar um compilador, o que você mais deseja é criar um **game** phodd@, certo? Algo para mostrar para a sua Mãe, seu benzinho ou para jogar na cara dos zamigos. Então tá... Bora criar um game? Mas tem que ser em **C++**!

A primeira coisa que você deve aprender é programar em C++. Não sabe? Então faça [**o meu curso**](https://cleuton-sampaio.hotmart.host/algoritmos-e-estruturas-de-dados-para-garantir-sua-vaga-top-b9c68532-9597-4403-b75b-89653db40f52)!

Agora vamos começar... Primeiramente, você tem que saber usar bibliotecas gráficas, de modo a se beneficiar da **GPU** e utilizar uma linguagem independente para desenhar. 

> **Atenção:** Vamos utilizar **Linux**, de preferência algum **Debian** like. Se você usa **MS Windows** ou **MacOS** nada posso fazer por você. Mas existem tutoriais para essas plataformas. 

## OpenGL

**OpenGL** (Open Graphics Library) é uma **API gráfica multiplataforma e de código aberto** usada para renderizar imagens 2D e 3D em computadores. Ela fornece um conjunto de funções que permitem a programação de gráficos de alto desempenho, sendo amplamente utilizada em jogos, simulações, aplicações CAD, visualizações científicas e realidade aumentada/virtual.

### **Principais vantagens do OpenGL:**

1. **Multiplataforma:**  
   Funciona em diversos sistemas operacionais (Windows, Linux, macOS, Android, iOS etc.).

2. **Desempenho elevado:**  
   Permite acesso direto à GPU, otimizando a renderização de gráficos complexos.

3. **Independência de hardware:**  
   É compatível com diferentes placas de vídeo desde que suportem o padrão OpenGL.

4. **Código aberto e padronizado:**  
   Mantido pelo Khronos Group, garantindo atualizações constantes e uso livre de royalties.

5. **Flexibilidade e controle:**  
   Oferece ao desenvolvedor controle total sobre os elementos gráficos, permitindo técnicas avançadas como shaders, iluminação dinâmica e texturas complexas.

6. **Grande comunidade e recursos disponíveis:**  
   Há muitos tutoriais, bibliotecas auxiliares (como GLFW, GLAD, GLU) e ferramentas para facilitar seu uso.

Resumindo, **OpenGL é uma ferramenta poderosa e versátil** para desenvolvimento de aplicações gráficas, especialmente quando se busca performance e portabilidade entre plataformas.

## Para usar OpenGL no C++

Para usar **OpenGL** em **C++**, é necessário configurar um ambiente adequado, já que o OpenGL puro não gerencia janelas nem entrada de usuário. Assim, utilizam-se bibliotecas auxiliares como **GLFW**, **GLAD** e **GLM**.

### O que é necessário:

1. **GLFW**  
   É uma biblioteca que cria janelas, gerencia contexto OpenGL e lida com eventos de teclado, mouse e temporização (como o tempo entre frames). Ela permite inicializar uma janela onde os gráficos serão renderizados.

2. **GLAD**  
   É responsável por carregar as funções do OpenGL para o programa. Como diferentes sistemas e placas oferecem versões distintas das comandos do OpenGL, o GLAD carrega dinamicamente essas funções no início da execução.

3. **GLM (OpenGL Mathematics)**  
   Uma biblioteca matemática usada para manipular vetores, matrizes e transformações geométricas, comuns em gráficos 3D. Ela segue a sintaxe semelhante ao shading language do OpenGL (GLSL), facilitando seu uso em shaders.

### Resumo:
- Use **GLFW** para criar a janela e gerenciar entradas.
- Use **GLAD** para carregar as funções do OpenGL.
- Use **GLM** para realizar cálculos matemáticos necessários à renderização 3D.

Essas ferramentas juntas permitem configurar e começar a desenvolver aplicações gráficas com OpenGL em C++.

## Instalando a bagaça toda

Para começar, você precisa do [**GLFW**](https://www.glfw.org). Ele até possui *binários* compilados para várias plataformas, como: Linux, Windows e MacOS (https://www.glfw.org/download.html). Mas vou te ensinar a compilar sua versão: 

1. Clone o repositório: 
```shell
https://github.com/glfw/glfw
```

2. Compile o GLFW: 
```shell
# Se você usa algum tipo de debian:
sudo apt update
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev

# Se usa fedora: 
sudo dnf install wayland-devel libxkbcommon-devel libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel

# Crie o make file: 
cd glfw
mkdir build
cd build
cmake ..

# Rode o make: 
make

# instale a lib:
sudo make install
sudo ldconfig
```

Pronto!

Agora vamos ver o **GLM**... Teoricamente, é só copiar os includes, mas isso sempre dá problema porque você pode esquecer alguma pasta. Então, o melhor a fazer é: 
```shell
sudo apt update
sudo apt install libglm-dev
```

Finalmente temos o **glad**! Ele é gerado através de um site: [https://glad.dav1d.de/](https://glad.dav1d.de/). Você preenche algumas combos e ele gera para você o glad.zip: 

![](../glad.png)

Eu estou usando a versão 3.3 core, mas isso pode mudar conforme avançamos mais. 

## Um projeto para ver se tudo funcionou

Crie um projeto com essa estrutura de pastas: 

```text
projeto2/
├── CMakeLists.txt
├── include/
│   └── glad/
│       ├── glad.h
│       └── khrplatform.h
└── src/
    ├── main.cpp
    └── glad.c
```

Os arquivos de include do `glad` vem dentro do `glad.zip`. Junte os dois dentro de `include/glad`. E copie o `glad.c` para a pasta `src`.

O `CMakeLists.txt` para esse projeto é assim: 

```text
cmake_minimum_required(VERSION 3.1)
project(projeto2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

# encontra o OpenGL e o GLFW já instalados no sistema
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# inclui os headers do GLAD e do GLM
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/glad.c
)

# linka contra as libs do sistema
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    OpenGL::GL
    glfw
)
```

Esse arquivo **CMakeLists.txt** está configurando um projeto em C++ que utiliza **OpenGL** e **GLFW**, além de incluir arquivos adicionais como **GLAD** e **GLM**. Aqui está uma explicação resumida do que cada parte faz:

### 1. **Configuração inicial:**
```cmake
cmake_minimum_required(VERSION 3.1)
project(projeto2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
```
- Define a versão mínima do **CMake** necessária (3.1).
- Nomeia o projeto como `projeto2` e especifica que ele usa as linguagens **C** e **C++**.
- Define que o padrão do C++ usado será o **C++17**.

### 2. **Localização de bibliotecas externas:**
```cmake
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
```
- Procura no sistema por versões instaladas do **OpenGL** e do **GLFW 3.3**.
- O `REQUIRED` indica que essas bibliotecas são obrigatórias para a compilação.

### 3. **Inclusão de diretórios com headers:**
```cmake
include_directories(
  ${CMAKE_SOURCE_DIR}/include
)
```
- Adiciona o diretório `include/` do projeto à lista de caminhos onde o compilador deve procurar pelos arquivos de cabeçalho (headers), como os do **GLAD** e **GLM**.

### 4. **Definição do executável:**
```cmake
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/glad.c
)
```
- Cria um executável chamado `projeto2`, a partir dos arquivos:
  - `main.cpp`: o código principal do programa.
  - `glad.c`: implementação gerada pelo GLAD, necessária para carregar funções do OpenGL.

### 5. **Vinculação das bibliotecas:**
```cmake
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    OpenGL::GL
    glfw
)
```
- `Linka` o executável às bibliotecas do **OpenGL** e **GLFW**, permitindo que o programa as utilize.

Bom, mas e o código-fonte? Então... Vamos criar um arquivo `main.cpp` dentro da pasta `src`. O que ele fará? Criará um cubo multicolorido giratório, como esse da imagem: 

![](../exemplo.png)

O código-fonte está no arquivo [`main.cpp`](./projeto2/src/main.cpp), mas vou reproduzir e explicar aqui: 

```C++
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

```

### O que o código faz passo a passo:

#### 1. Bibliotecas usadas:
- **GLFW:** cria uma janela e gerencia eventos (como teclado).
- **GLAD:** carrega as funções do OpenGL.
- **GLM:** ajuda com cálculos matemáticos 3D (matrizes, rotação, posição etc.).
- **iostream:** usado apenas para mostrar mensagens de erro.

#### 2. Definição dos vértices do cubo:
- Um cubo é formado por triângulos.
- Cada triângulo tem 3 vértices → o cubo tem **36 vértices no total**.
- Cada vértice tem:
  - **Posição (x, y, z)**
  - **Cor (r, g, b)**

#### 3. Shaders:
São programas que rodarão na **GPU** para renderizar gráficos.

- **Vertex Shader:**  
  - Pega a posição e cor de cada vértice.
  - Aplica transformações 3D (posição, rotação, perspectiva).
  - Manda os dados para o próximo estágio.

- **Fragment Shader:**  
  - Pega a cor calculada entre os vértices.
  - Define a cor final de cada pixel da tela.

#### 4. Inicialização do GLFW e GLAD:
- Inicia uma janela OpenGL.
- Configura o contexto do OpenGL (versão 3.3 Core Profile).
- Carrega todas as funções do OpenGL com o GLAD.

#### 5. Configuração dos dados de vértices (VBO e VAO):
- **VAO (Vertex Array Object):** salva como os dados estão organizados.
- **VBO (Vertex Buffer Object):** armazena os dados dos vértices na GPU.
- Aqui dizemos ao OpenGL onde estão as posições e cores dentro do array `cubeVertices`.

#### 6. Matrizes 3D:
Usamos o GLM para criar:
- **Projection:** dá a sensação de profundidade (perspectiva).
- **View:** define onde a câmera está (posicionada atrás do cubo).
- **Model:** controla a posição e rotação do objeto (neste caso, o cubo gira com o tempo).

#### 7. Loop principal de renderização:
Enquanto a janela estiver aberta:
- Limpa a tela.
- Atualiza a matriz de rotação com base no tempo (`glfwGetTime()`).
- Envia as matrizes para o shader.
- Desenha os triângulos do cubo.
- Atualiza a tela e verifica eventos (como fechar a janela).

#### 8. Limpeza ao finalizar:
- Libera memória dos objetos criados (VAO, VBO, shaders).
- Encerra o GLFW.


