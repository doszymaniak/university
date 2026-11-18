#include <iostream>
#include <map>
#include <string>
#include <queue>

using namespace std;

class Graph {
private:
    map<string, map<string, double>> adj;

    bool is_name_valid(const string &name)
    {
        if (name.empty())
            return 0;

        for (auto &c : name)
        {
            if (!isalpha(c))
                return 0;
        }

        return 1;
    }

public:
    void add_vertex(const string &name)
    {
        if (!is_name_valid(name))
            throw invalid_argument("Invalid name!");

        adj.emplace(name, map<string, double>());
    }

    void remove_vertex(string &name)
    {
        auto it = adj.find(name);

        if (it == adj.end())
            return;

        for (auto &vertex : adj)
            vertex.second.erase(name);
        
        adj.erase(it);
    }

    void add_edge(const string &name1, const string &name2, double weight)
    {
        if (name1 == name2)
            throw invalid_argument("Names must be different!");

        if (adj.find(name1) == adj.end() || adj.find(name2) == adj.end())
            throw invalid_argument("Node does not exist!");

        adj[name1][name2] = weight;
        adj[name2][name1] = weight;
    }
    
    void remove_edge(const string &name1, const string &name2)
    {
        if (adj.find(name1) == adj.end() || adj.find(name2) == adj.end())
            throw invalid_argument("Node does not exist!");
        
        adj[name1].erase(name2);
        adj[name2].erase(name1);
    }

    void change_weight(const string &name1, const string &name2, double new_weight)
    {
        if (adj.find(name1) == adj.end() || adj.find(name2) == adj.end())
            throw invalid_argument("Node does not exist");

        if (adj[name1].find(name2) == adj[name1].end() || adj[name2].find(name1) == adj[name2].end())
            throw invalid_argument("Edge does not exist");

        adj[name1][name2] = new_weight;
        adj[name2][name1] = new_weight;
    }

    void print() const {
        for (auto &vertex : adj)
        {
            cout << vertex.first << ": ";
            for (auto &neighbor : vertex.second)
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ")";
            }
            cout << '\n';
        }
    }

    Graph prims_alg() const {
        Graph mst;

        if (adj.empty())
            return mst;

        using Edge = tuple<double, string, string>;
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        map<string, bool> visited;

        for (auto it = adj.begin(); it != adj.end(); it++)
        {
            auto &[vertex, neighbors] = *it;
            mst.add_vertex(vertex);
        }

        string start = adj.begin()->first;
        pq.push({0.0, start, ""});

        while (!pq.empty())
        {
            auto [weight, curr, prev] = pq.top();
            pq.pop();
            if (visited[curr])
                continue;
            visited[curr] = true;
            if (prev != "")
                mst.add_edge(prev, curr, weight);
            for (const auto &[neighbor, edge] : adj.at(curr))
            {
                if (!visited[neighbor])
                    pq.push({edge, neighbor, curr});
            }
        }

        if (visited.size() != adj.size())
            throw runtime_error("Graph is not connected!");

        return mst;
    }
};

int main()
{
    Graph g;
    
    string A = "A";
    string B = "B";
    string C = "C";
    string D = "D";
    string E = "E";

    g.add_vertex(A);
    g.add_vertex(B);
    g.add_vertex(C);
    g.add_vertex(D);
    g.add_vertex(E);

    g.add_edge("A", "B", 4.5);
    g.add_edge("A", "C", 2.0);
    g.add_edge("B", "C", -3.5);
    g.add_edge("B", "D", 7.0);
    g.add_edge("C", "D", 1.5);
    g.add_edge("C", "E", 6.0);
    g.add_edge("D", "E", 8.0);

    cout << "Initial graph:\n";
    g.print();

    cout << "\nMinimum spanning tree:\n";
    (g.prims_alg()).print();

    cout << "\nChanging weight of edge A-B:\n";
    g.change_weight("A", "B", 10.5);
    g.print();

    cout << "\nRemoving edge B-C:\n";
    g.remove_edge("B", "C");
    g.print();

    cout << "\nRemoving vertex D:\n";
    g.remove_vertex(D);
    g.print();

    cout << "\nAdding vertex D again:\n";
    g.add_vertex(D);
    g.print();

    cout << "\nAdding new edges:\n";
    g.add_edge("D", "E", -5.0);
    g.add_edge("A", "D", 3.0);
    g.print();

    return 0;
}