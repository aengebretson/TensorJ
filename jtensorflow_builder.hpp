#include <antlr4-runtime.h>
#include <tensorflow/core/framework/tensor.h>
#include <tensorflow/core/public/session.h>

using namespace antlr4;
using namespace tensorflow;

class JTensorFlowBuilder : JBaseListener {
    public:

    void ExitArray(JParser::ArrayContext *ctx) override {
        std::vector<float> values;
        for (auto valueCtx : ctx->value()) {
            values.push_back(std::stof(valueCtx->NUMBER()->getText()));
        }
        
        Tensor tensor(DT_FLOAT, TensorShape({statis_cast<int64>(values.size())}));
        auto tensor_vec = tensor.vec<float>();
        for (size_t i = 0; i < values.size(); ++i) {
            tensor_vec(i) = values[i];
        }

        nodeStack.push(Const(builder, tensor));
    }

    void ExitMonad(JParser::MonadContext *ctx) override {
        std::string verb = ctx->VERB()->getText();
        Node* input = nodeStack.top();
        nodeStack.pop();

        if (verb == "+/") {
            nodeStack.push(Sum(input, 0));
        } else if (verb == "*/") {
            nodeStack.push(Prod(input, 0));
        } else if (verb == "|.") {
            nodeStack.push(Reverse(input, 0));
        } else if (verb == "|:") {
            nodeStack.push(Transpose(input, 0));
        } else if (verb == ",.") {
            nodeStack.push(Reshape(input, 0)); // this is actually Ravel
        } else if (verb == "$.") {
            nodeStack.push(Shape(input, 0));
        } else if (verb == "|") {
            nodeStack.push(Abs(input, 0));
        }
        // add more monads here

    }

    void ExitDyad(JParser::DyadContext* ctx) override {
        std::string verb = ctx->VERB()->getText();
        Node* right = nodeStack.top();
        nodeStack.pop();
        Node* left = nodeStack.top();
        nodeStack.pop();

        if (verb == "+") {
            nodeStack.push(Add(left, right));
        } else if (verb == "-") {
            nodeStack.push(Sub(left, right));
        } else if (verb == "*") {
            nodeStack.push(Mul(left, right));
        } else if (verb == "%") {
            nodeStack.push(Div(left, right));
        } else if (verb == "<.") {  
            nodeStack.push(Min(left, right));
        } else if (verb == ">.") {
            nodeStack.push(Max(left, right));
        } else if (verb == "=") {
            nodeStack.push(Equal(left, right));  
        } else if (verb == "~:") {
            nodeStack.push(NotEqual(left, right));
        } else if (verb == "<") {
            nodeStack.push(Less(left, right));
        } else if (verb == ">") {
            nodeStack.push(Greater(left, right));
        } else if (verb == "^") {
            nodeStack.push(Pow(left, right));
        // } else if (verb == ",") {
        //     nodeStack.push(Concat(left, right));
        // } else if (verb == ".") {
        //     nodeStack.push(Dot(left, right));
        }
    }

    void ExitFork(JParser::ForkContext* ctx) override {
        
    }

    Node* GetOutput() {
        return nodeStack.top();
    }

    private:
    std::stack<Node*> nodeStack;
    tensorflow::NodeBuilder builder;


    // monadic verbs

    Node* Sum(Node* input) {
        auto dims = input->shape().dim_size();
        std::vector<int64> axes(dims);
        std::iota(axes.begin(), axes.end(), 0);
        return tensorflow::ReduceSum(input, axes);
    }

    Node* Prod(Node* input) {
        auto dims = input->shape().dim_size();
        std::vector<int64> axes(dims);
        std::iota(axes.begin(), axes.end(), 0);
        return tensorflow::ReduceProd(input, axes);
    }

    Node* Reverse(Node* input) {
        auto dims = input->shape().dim_size();
        std::vector<int64> axes(dims);
        std::iota(axes.begin(), axes.end(), 0);
        return tensorflow::Reverse(input, axes);
    }


    // dyadic functions

    Node* Add(Node* left, Node* right) {
        return tensorflow::Add(left, right);
    }

    Node* Subtract(Node* left, Node* right) {
        return tensorflow::Sub(left, right);
    }

    Node* Multiply(Node* left, Node* right) {
        return tensorflow::Mul(left, right);
    }

    Node* Divide(Node* left, Node* right) {
        return tensorflow::Div(left, right);
    }

    Node* Minimum(Node* left, Node* right) {
        return tensorflow::Minimum(left, right);
    }

    Node* Maximum(Node* left, Node* right) {
        return tensorflow::Maximum(left, right);
    }

};

