#include "parser.h"
#include <cctype>
#include <stdexcept>
#include <string>
#include <cmath>

using namespace std;

// Helper to advance the parser position past any whitespace.
void skip_spaces(const std::string& input, size_t& pos) {
    while(pos < input.size() && isspace(input[pos])) {
        pos++;
    }
}

std::unique_ptr<Node> Parser::parseExpression() {
    // Expression -> Term { ('+' | '-') Term }
    skip_spaces(input, pos);
    auto node = parseTerm();
    skip_spaces(input, pos);
    while(pos < input.size() && (input[pos]=='+' || input[pos]=='-')) {
        char op = input[pos++];
        auto right = parseTerm();
        node = std::make_unique<BinaryNode>(op, std::move(node), std::move(right));
        skip_spaces(input, pos);
    }
    return node;
}

std::unique_ptr<Node> Parser::parseTerm() {
    // Term -> Power { ('*' | '/') Power }
    skip_spaces(input, pos);
    auto node = parsePower();
    skip_spaces(input, pos);
    while(pos < input.size() && (input[pos]=='*' || input[pos]=='/')) {
        char op = input[pos++];
        auto right = parsePower();
        node = std::make_unique<BinaryNode>(op, std::move(node), std::move(right));
        skip_spaces(input, pos);
    }
    return node;
}

std::unique_ptr<Node> Parser::parseFactor() {
    // Factor -> Unary
    skip_spaces(input, pos);
    return parseUnary();
}

std::unique_ptr<Node> Parser::parsePower() {
    // Power -> Factor { '^' Factor } (right-associative)
    skip_spaces(input, pos);
    auto node = parseFactor();
    skip_spaces(input, pos);
    while(pos < input.size() && input[pos]=='^') {
        char op = input[pos++];
        auto right = parseFactor();
        node = std::make_unique<BinaryNode>(op, std::move(node), std::move(right));
        skip_spaces(input, pos);
    }
    return node;
}

std::unique_ptr<Node> Parser::parseUnary() {
    // Unary -> ('+' | '-') Unary | Primary
    skip_spaces(input, pos);
    if (input[pos] == '-') {
        pos++;
        auto node = parseUnary();
        return std::make_unique<BinaryNode>('*', std::make_unique<NumberNode>(-1), std::move(node));
    }
    if (input[pos] == '+') { // Unary plus
        pos++;
        return parseUnary();
    }
    return parsePrimary();
}

std::unique_ptr<Node> Parser::parsePrimary() {
    // Primary -> Number | Constant | Function | '(' Expression ')'
    skip_spaces(input, pos);

    // Number
    if(isdigit(input[pos]) || input[pos]=='.') {
        size_t start_pos = pos;
        while(pos < input.size() && (isdigit(input[pos]) || input[pos] == '.')) pos++;
        string num_str = input.substr(start_pos, pos - start_pos);
        return make_unique<NumberNode>(stod(num_str));
    }

    // Functions and constants
    if(isalpha(input[pos])) {
        string name = parseFunction();
        constexpr double pi = 3.141592653589793;
        constexpr double e = 2.718281828459045;

        if(name=="pi") return make_unique<NumberNode>(pi);
        if(name=="e") return make_unique<NumberNode>(e);

        skip_spaces(input, pos);
        if(input[pos] != '(') throw runtime_error("Expected '(' after function name: " + name);
        pos++;
        auto arg = parseExpression(); // Recurse to parse the argument
        skip_spaces(input, pos);
        if(input[pos] != ')') throw runtime_error("Expected ')' after function argument");
        pos++;
        return make_unique<FunctionNode>(name, std::move(arg));
    }

    // Parentheses
    if(input[pos]=='('){
        pos++;
        auto node=parseExpression();
        skip_spaces(input, pos);
        if(input[pos] != ')') throw runtime_error("Expected ')' to close parenthesis");
        pos++;
        return node;
    }

    throw runtime_error("Unexpected character: " + string(1, input[pos]));
}

string Parser::parseFunction(){
    size_t start_pos = pos;
    while(pos<input.size() && isalpha(input[pos])) pos++;
    return input.substr(start_pos, pos - start_pos);
}
