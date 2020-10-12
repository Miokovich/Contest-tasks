#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>


void color_graph(const std::vector<std::list<int>> &graph, std::vector<int> &color,
                 int start, int cur_color, bool &cant_color){
    color[start] = cur_color;
    for (const auto &neigh : graph[start]){
        if (color[neigh] == 0){
            color_graph(graph, color, neigh, 3 - cur_color, cant_color);
        } else {
            if (color[neigh] == cur_color) {
                cant_color = true;
            }
        }
    }

}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::list<int>> list_edg;
    list_edg.reserve(n + 1);
    for (size_t i = 0; i <= n; ++i){
        list_edg.push_back(std::list<int>());
    }

    int a, b;
    std::vector<int> color(n + 1, 0);

    for (size_t i = 0; i < m; ++i){
        std::cin >> a >> b;
        list_edg[a].push_back(b);
        list_edg[b].push_back(a);
    }

    for (size_t i = 0; i <= n; ++i){
        list_edg[i].unique();
    }
    bool cant_color = false;
    for (size_t i = 1; i <= n; ++i){
        if (color[i] == 0) {
            color_graph(list_edg, color, i, 1, cant_color);
            if (cant_color) {
                std::cout << "NO";
                return 0;
            }
        }
    }
    std::cout << "YES";
    return 0;
}
