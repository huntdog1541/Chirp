<h1 align = 'center'>Chirp</h1>

<div align = 'center'>
  <strong>Chirp is a modern low-level programming language written in C++</strong>

  <br><br>

  <!-- Source for new image: https://shields.io/category/build -->
  <a href = 'https://travis-ci.org/binkiklou/Chirp'>
    <img src = 'https://img.shields.io/travis/binkiklou/Chirp/master.svg?style=for-the-badge' alt = 'Build Status' />
  </a>

  <a href = 'https://github.com/binkiklou/Chirp/blob/master/LICENSE'>
    <img src = 'https://img.shields.io/github/license/binkiklou/Chirp.svg?style=for-the-badge' alt = 'License' />
  </a>

  <a href = 'https://discord.gg/8EeVJaS'>
    <img src = 'http://munchii.me/Images/ChirpDiscord.svg' alt = 'Discord Server' />
  </a>
</div>

<br><br><br>

<p align = 'center'>
  <img src = 'https://camo.githubusercontent.com/641f171b8217bb22d5951086a25c7c7a037a106c/68747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3530363135323839363631383935343831322f3538323035313338303737373435313534312f4368697270536d616c6c49636f6e2e706e67'>
</p>

<br>

Chirp is a modern low-level programming language written in C++. Currently the language is still very early and can barely run yet, but I am actively working on the compiler, and hope one day it will be a functioning language.

## Simple Example

```chirp
  entry ()
  {
    # Assign 123 to the variable "a", which is an int
    int: a = 123
  }
```

## Building

We are using CMake, so building is very easy. Depending on your platform there might be scripts to run the CMake commands for you, but even without the scripts it's very easy.

### Dependencies

- any compiler that supports c++11
- ``cmake`` 3.8.2 or higher

### Linux

You can build using the ``build.sh`` script

```bash
git clone https://github.com/chirp-language/Chirp.git
cd Chirp
sh build.sh
```

The executable will be created in ``./build/src/Chirp``.

### Windows

There is no scripts for windows, but you can use the CMake gui.

## Features

We are rewritting the compiler, and this is what we have done so far:

- [x] Variable declaration ``24-07-2019``
- [ ] Variable definition
- [ ] Assembly preprocessor
- [ ] Functions
- [ ] Function call
- [ ] Mathematical expressions
- [ ] If statements
- [ ] Else statements
- [ ] While statements
- [ ] For statement
- [ ] Pointers
- [ ] Classes
- [ ] Dynamic memory allocation
- [ ] IO library
