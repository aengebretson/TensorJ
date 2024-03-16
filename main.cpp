#include <iostream>
#include <string>
#include "jtensorflow_builder.h"
#include "JLexer.h"
#include "JParser.h"

using namespace antlr4;
using namespace tensorflow;

int main(int argc, char *argv[]) {
    std::string jExpression = argc > 1 ? argv[1] : "+/ * 1 2 3 4 5";

    ANTLRInputStream input(jExpression);

    JLexer lexer(&input);

    CommonTokenStream tokens(&lexer);

    JParser parser(&tokens);
    tree::ParseTree *tree = parser.start();

    JTensorflowBuilder builder;

    tree::ParseTreeWalker::DEFAULT.walk(&builder, tree);

    Node* outputNode = builder.GetOutput();

    Session* session = NewSession(SessionOptions());
    std::vector<Tensor> outputs;
    session->Run({}, {outputNode}, {}, &outputs);

    std::cout << "Result: " << outputs[0].scalar<float>() << std::endl;

    session->Close();
    delete session;

    return 0;
}