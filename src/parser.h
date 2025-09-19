#pragma once
#include "ast.h"
#include <string>
#include <memory>

using namespace std;

class Parser {
    string input;
    size_t pos = 0;

public:
    Parser(const string& s) : input(s) {}
    unique_ptr<Node> parseExpression();

private:
    unique_ptr<Node> parseTerm();
    unique_ptr<Node> parseFactor();
    unique_ptr<Node> parsePower();
    unique_ptr<Node> parseUnary();
    unique_ptr<Node> parsePrimary();
    string parseFunction();
};
