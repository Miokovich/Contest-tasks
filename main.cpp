#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <queue>


void print_parent(const std::vector<int> &parents, const size_t& cur_ind){
    if (cur_ind != -1) {
        print_parent(parents, parents[cur_ind]);
        std::cout << cur_ind << ' ';
    }
    //std::cout << cur_ind;

}


void BFS(const std::vector<std::list<int>> &graph, const size_t& index_start,
           const size_t &finish){

    std::queue<size_t> que;
    size_t size_edg = graph.size();
    std::vector<int> dist(size_edg + 1, -1), parent(size_edg + 1, -1);

    que.push(index_start);
    dist[index_start] = 0;

    while (!que.empty()){
        size_t cur_ind = que.front();
        que.pop();
        std::list<int> neigh = graph[cur_ind];
        while (!neigh.empty()){
            if (dist[neigh.front()] == -1){
                dist[neigh.front()] = dist[cur_ind] + 1;
                parent[neigh.front()] = cur_ind;
                que.push(neigh.front());
            }
            neigh.pop_front();
        }
    }
    if (dist[finish] != -1) {
        std::cout << dist[finish] << '\n';
        print_parent(parent, finish);
    } else {
        std::cout << "-1";
    }
}


int main(){
    size_t n, m;
    size_t start, finish;
    std::cin >> n >> m;
    std::cin >> start >> finish;
    std::vector<std::list<int>> list_edg;
    list_edg.reserve(n + 1);
    for (size_t i = 0; i <= n; ++i){
        list_edg.push_back(std::list<int>());
    }
    size_t a, b;
    for (size_t i = 0; i < m; ++i){
        std::cin >> a >> b;
        list_edg[a].push_back(b);
        list_edg[b].push_back(a);
    }
    BFS(list_edg, start, finish);
    return 0;
}
