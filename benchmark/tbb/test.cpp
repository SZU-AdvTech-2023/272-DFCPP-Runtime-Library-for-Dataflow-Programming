#include <tbb/flow_graph.h>
#include <tbb/tbb.h>
#include <iostream>
#include <vector>

using namespace tbb::flow;
using namespace tbb;
using namespace std;

int main() {
    graph g; // 创建图对象

    function_node<int, vector<int>> task1(g, 1, [](int n){
        vector<int> datas(n);
        for(int i = 0; i < n; i++) {
            datas[i] = i;
        }
        return datas;
    });
    function_node<vector<int>> task2(g, 1, [](vector<int> datas){
        int n = datas.size();
        tbb::parallel_for(0, n, 1, [&datas](int i){
            datas[i] += 1;
        });
        for(auto item : datas) {
            cout << item << " ";
        }
        cout << endl;
    });

    make_edge(task1, task2);

    task1.try_put(10);
    g.wait_for_all();			// 等待执行结束
	return 0;
}