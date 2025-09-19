#pragma once
#include <memory>
#include <string>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <unordered_map>

using namespace std;

// Abstract base class for all expression tree nodes.
struct Node {
    virtual double eval() const = 0;
    virtual ~Node() = default;
};

// Represents a literal number in an expression.
struct NumberNode : Node {
    double value;
    NumberNode(double v) : value(v) {}
    double eval() const override { return value; }
};

// Represents a binary operation (e.g., +, *, ^).
struct BinaryNode : Node {
    char op;
    unique_ptr<Node> left, right;

    BinaryNode(char o, unique_ptr<Node> l, unique_ptr<Node> r)
        : op(o), left(move(l)), right(move(r)) {}

    double eval() const override {
        const double l = left->eval();
        const double r = right->eval();
        switch(op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/':
                if (r == 0) throw runtime_error("Division by zero");
                return l / r;
            case '^': return pow(l, r);
            default: throw runtime_error("Unknown operator");
        }
    }
};

// Represents a function call (e.g., sin(x), sqrt(y)).
struct FunctionNode : Node {
    string func;
    unique_ptr<Node> arg;

private:
    using Func = function<double(double)>;
    static const unordered_map<string, Func> functions;

public:
    FunctionNode(const string& f, unique_ptr<Node> a)
        : func(f), arg(move(a)) {}

    double eval() const override {
        const double val = arg->eval();
        auto it = functions.find(func);
        if (it != functions.end()) {
            return it->second(val);
        }
        throw runtime_error("Unknown function: " + func);
    }
};
