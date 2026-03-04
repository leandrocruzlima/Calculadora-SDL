
# CÁLCULADORA SDL

Esta calculadora é um projeto feito para o meu portfólio que demonstra minhas habilidades gerenciando dados e utilizando lógica de programação.

Além disso, criei a interface inteira usando apenas o **SDL**, por isso a interface é básica.

Os botões e o display da calculadora foram programados dentro de `basicgui.cpp`, enquanto a lógica da calculadora e o layout principal estão em `main.cpp`.

---

# Como baixar

No terminal, digite:

```shell
git clone https://github.com/leandrocruzlima/Calculadora-SDL
cd Calculadora-SDL
```

---

# Dependências

Para compilar o projeto você precisa de:

* Compilador C++
* Make
* SDL2
* SDL2_ttf

## Debian e derivados

```shell
sudo apt install build-essential libsdl2-dev libsdl2-ttf-dev
```

---

## RedHat / Fedora / Rocky / Alma

```shell
sudo dnf groupinstall "Development Tools"
sudo dnf install SDL2-devel SDL2_ttf-devel
```

ou instalação mínima:

```shell
sudo dnf install gcc gcc-c++ make SDL2-devel SDL2_ttf-devel
```

---

## Arch Linux e derivados

```shell
sudo pacman -S base-devel sdl2 sdl2_ttf
```

---

## openSUSE

```shell
sudo zypper install -t pattern devel_basis
sudo zypper install SDL2-devel SDL2_ttf-devel
```

---

## Windows (MSYS2 / MINGW64)

Instale o **MSYS2** e abra o terminal **MINGW64**, depois execute:

```shell
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf make
```

---

# Como compilar

Execute:

```shell
make
```

ou compile manualmente:

```shell
g++ main.cpp basicgui.cpp -o calculadora `sdl2-config --cflags --libs` -lSDL2_ttf
```

---

# Executar

Após compilar, execute:

```shell
./calculadora
```
