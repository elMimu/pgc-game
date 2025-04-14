# 🧠 Um Sistema Adaptativo de Jogos Educacionais para Intervenção em Matemática no Ensino Fundamental

## 📚 Descrição

Este projeto propõe o desenvolvimento de um sistema de jogos educacionais **adaptativos**, voltados ao ensino de Matemática para **intervenções pedagógicas nos anos iniciais do ensino fundamental**.

A ideia central é oferecer **minijogos matemáticos personalizados**, que se **ajustam automaticamente ao desempenho individual** de cada aluno, promovendo uma experiência de aprendizagem mais eficaz e engajadora.

O projeto é **interdisciplinar**, integrando conhecimentos das áreas de:

- 💻 **Computação** (desenvolvimento do sistema e algoritmos adaptativos),
- ➕ **Educação Matemática** (conteúdo e estrutura pedagógica),
- 🧬 **Neurociência** (estratégias baseadas em evidências cognitivas e de aprendizado).

O desenvolvimento é feito em **colaboração com estudantes de pós-graduação em Neurociência**, que contribuem com a formulação das estratégias pedagógicas e cognitivas aplicadas aos jogos.

## 🎮 Funcionalidades Esperadas

- Plataforma de jogos educacionais em Matemática.
- Minijogos adaptativos que se ajustam automaticamente ao desempenho do aluno.
- Sistema de progressão e feedback imediato.
- Foco nos anos iniciais do ensino fundamental.
- Planejamento para **armazenamento local** (evitando dependência de conexões de internet).

## 🛠 Tecnologias Utilizadas

- **C++** com **Raylib** para o desenvolvimento dos jogos.
- **CMake** para gestão do projeto e builds multiplataforma.
- Desenvolvido na plataforma **Linux** e com o objetivo de ser **portado para Android**.

## ⚙️ Pré-requisitos

Antes de compilar, certifique-se de ter os seguintes pacotes instalados: cmake e raylib
O **cmake** pode ser baixado [clicando aqui](https://cmake.org/download/) - recomendado.
Ou pode ser instalado utilizando o seguinte comando:

## UBUNTU

```bash
sudo apt-get install cmake
```

O raylib está integrado ao projeto, entretanto é necessário instalar algumas dependências,
para isso, utilize como referência para instalação este [link](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

## 🚀 Como Executar

> ⚠️ Instruções de compilação e execução para Linux (em breve suporte a Android)

```bash
git clone https://github.com/elMimu/pgc-game.git
cd pgc-game/
cmake -S . -B build
```

- o executável está localizado no diretório /pgc-game/build/Debug
