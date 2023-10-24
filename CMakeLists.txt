cmake_minimum_required(VERSION 3.22)

project(encryption)

set(CMAKE_CXX_STANDARD 11)

#for Exe to work
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(encryption main.cpp EncryptDecrypt.cpp EncryptDecrypt.h)
