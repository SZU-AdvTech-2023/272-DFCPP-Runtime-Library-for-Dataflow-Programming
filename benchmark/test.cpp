
#include "dfcpp/dfcpp.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace DFCPP;
using namespace std;

int main() {
    DFGraph graph;
    auto [a, b, c]  = graph.createDFV<int, int, int>();
    graph.emplace([](DFV<int> out){
        out = 0;
    }, make_tuple(), make_tuple(a));
    graph.emplace([](int a, DFV<int> out){
        out = a + 1;
    }, make_tuple(a), make_tuple(b));
    graph.emplace([](int b, DFV<int> a, DFV<int> c){
        if(b < 10) {
            a = b;
        } else {
            c = b;
        }
    }, make_tuple(b), make_tuple(a, c));
    graph.emplace([](int c){ cout << "done" << endl;}, make_tuple(c));
    Executor executor;
    executor.run(graph).wait();

    return 0;
}