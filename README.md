# C Matrix Toolkit

A dynamic **matrix operations engine in C** built using pointer-to-VLA allocation, recursive determinant evaluation, and modular function design.

This project demonstrates **low-level memory control**, **runtime dimension handling**, and **clean procedural architecture** beyond typical beginner implementations.

---

## Features

- Matrix **addition** and **subtraction**
- Matrix **transpose**
- Matrix **multiplication**
- Recursive **determinant calculation** for _n × n_ matrices
- Dynamic memory allocation using **pointer-to-VLA**
- Input parsing with flexible `rows x cols` format
- Proper **memory cleanup** and error handling

---

## Why this project is different

Most beginner matrix programs:

- use fixed-size arrays  
- avoid recursion  
- leak memory like a broken pipe  

This implementation:

- allocates matrices **contiguously in heap memory**
- supports **runtime dimensions**
- uses **clean modular functions**
- follows **safe memory practices**

---

## Compilation

```bash
gcc -std=c99 -Wall -Wextra -o matrix matrix.c
./matrix
