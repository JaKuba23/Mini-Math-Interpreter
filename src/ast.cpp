#include "ast.h"

using namespace std;

// Initialize the static map of functions for FunctionNode.
const unordered_map<string, function<double(double)>> FunctionNode::functions = {
    {"sin", [](double v) { return sin(v); }},
    {"cos", [](double v) { return cos(v); }},
    {"tan", [](double v) { return tan(v); }},
    {"exp", [](double v) { return exp(v); }},
    {"sqrt", [](double v) {
        if (v < 0) throw runtime_error("Square root of a negative number");
        return sqrt(v);
    }},
    {"log", [](double v) {
        if (v <= 0) throw runtime_error("Logarithm of a non-positive number");
        return log(v);
    }}
};
