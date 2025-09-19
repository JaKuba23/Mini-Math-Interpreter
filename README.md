<div align="center">

  <h1 align="center">Mini Math Interpreter</h1>

  <p align="center">
    A professional, high-performance C++ interpreter for mathematical expressions, engineered with a focus on clean architecture, modern C++ standards, and robust parsing techniques.
    <br />
  </p>
</div>

---

## ✨ Key Features

- **Full Operator Support:**  
  Implements arithmetic (`+`, `-`, `*`, `/`) and exponentiation (`^`) with correct, right-associative precedence.
- **Recursive Descent Parser:**  
  A robust, hand-written parser that correctly interprets operator precedence and associativity (PEMDAS/BODMAS).
- **Abstract Syntax Tree (AST) Evaluation:**  
  Expressions are compiled into an AST, which is then evaluated to produce a result. This separates parsing from calculation, enabling future optimizations.
- **Standard Library Functions & Constants:**  
  Built-in support for `sin`, `cos`, `tan`, `sqrt`, `log`, `exp`, and the constants `pi` and `e`.
- **Robust Error Handling:**  
  Provides clear, user-friendly error messages for both syntax errors (e.g., mismatched parentheses) and mathematical errors (e.g., division by zero).
- **Interactive Console:**  
  A clean, simple command-line interface for real-time expression evaluation.
- **Modern C++ Implementation:**  
  Written in C++17, leveraging smart pointers (`unique_ptr`), `[[nodiscard]]`, and other modern features for memory safety and code clarity.

---

## 👁️ Architecture Overview

The interpreter's design follows a classic two-stage compiler pipeline, ensuring modularity and extensibility.

```mermaid
graph TD
    A[Input String: "3 * (4 + 2)"] --> B{Parser};
    B -- Lexical & Syntactic Analysis --> C[Abstract Syntax Tree];
    C -- Traversal --> D{Evaluator};
    D --> E[Result: 18.0];
```

- **Parser:** A recursive descent parser reads the input string. It tokenizes the input on-the-fly and applies grammar rules to build an Abstract Syntax Tree (AST).
- **Abstract Syntax Tree (AST):** A tree structure where each node represents an operation (`BinaryNode`), a value (`NumberNode`), or a function call (`FunctionNode`). This tree accurately represents the expression's structure and precedence.
- **Evaluator:** The `eval()` method on each AST node recursively traverses the tree, calculating the value of its children and applying the operation at the current node until a final result is computed.

---

## 📁 Project Structure

```
minicompiler/
├── src/
│   ├── ast.h               # Defines the structure of all AST nodes (Node, NumberNode, etc.)
│   ├── ast.cpp             # Implementation for AST nodes, including the function map
│   ├── parser.h            # Declaration of the Parser class
│   ├── parser.cpp          # Core recursive descent parsing logic
│   └── main.cpp            # Application entry point and interactive console loop
└── README.md               # This file
```

---

## ⚙️ Installation and Setup

### Prerequisites

- A C++ compiler supporting C++17 (e.g., g++, Clang, MSVC).

### Build Instructions

1.  Clone the repository to your local machine.
2.  Navigate to the project's root directory in your terminal.
3.  Compile the source files using your C++ compiler.

```bash
# The following command works for g++ on Linux, macOS, and Windows (MinGW)
g++ src/*.cpp -std=c++17 -o run
```

### Example Expressions

2 + 3^2 * sin(pi/2) - exp(1) + sqrt(9)

3^2 + 4^2 - sqrt(16) * (2 + 3)

sin(pi/4)^2 + cos(pi/4)^2 + log(e^2)

-(2 + 5^2) + sqrt(49) + sin(pi)

(3 + 4)^2 - 2^3 * tan(pi/4)


---
