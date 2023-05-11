#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

class graph_exception: public std::exception {
private:
    const char* message;
public:
    graph_exception(const char* const msg): message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
};

const graph_exception node_exists("node with same id already exists");
const graph_exception edge_exists("edge already exists");
const graph_exception node_does_not_exist("node does not exist");
const graph_exception edge_does_not_exist("edge does not exist");

// Здесь отдельно объявляем название класса, что оно существует, чтобы иметь возможность им воспользоваться в классе Node
// В плюсах это кажется называется extern definition
struct Edge;

// Все вершины в нашем графе будут иметь тип Node. Также у каждой вершины будет уникальной индитификатор (id).
struct Node {
    explicit Node(int id);
    int id;

    // Для каждой вершины будем хранить список входящих и исходящих ребер. Только вместо списка, будем хранить
    // хеш-таблицу из id ноды в ребро связывающее эти вершины. Так просто удобней оперировать с вершинами на практике,
    // а также удалении сильно проще и быстрее.
    std::unordered_map<int, Edge*> out_edges;
    std::unordered_map<int, Edge*> in_edges;
};

struct Edge {
    Edge(Node* src, Node* dst);
    Node* src;
    Node* dst;
};


class DirectedGraph {
public:
    void add_node(int id);
    void delete_node(int id);
    bool check_node(int id);
    Node* get_node(int id);

    void add_edge(int src, int dst);
    void delete_edge(int src, int dst);
    bool check_edge(int src, int dst);
    Edge* get_edge(int src, int dst);

    void print_edges();
    void print_nodes();
    void print_graph();

private:
    // отдельная вспомогательная функция чтобы удалять сразу список ребер, про которые мы точно знаем, что они есть в графе
    void delete_edges(const std::vector<std::pair<int, int>>& edges_to_delete);

    // вершины так же будем хранить в хештаблице для удобства.
    std::unordered_map<int, Node*> nodes;

    std::map<std::pair<int, int>, Edge*> edges;
};

Node::Node(int id): id(id) { }

Edge::Edge(Node *src, Node *dst): src(src), dst(dst) { }

void DirectedGraph::add_node(int id) {

    auto& node = nodes[id];
    if (node != nullptr)
        throw node_exists;
    node = new Node(id);
}

// Когда мы удаляем вершину, мы сначала собираем все ребра, связанные с этой вершиной, в первую очередь удаляем эти ребра,
// а затем уже удаляем саму вершину
void DirectedGraph::delete_node(int id) {
    if (!nodes.contains(id))
        throw node_does_not_exist;

    auto node = nodes[id];
    std::vector<std::pair<int, int>> edges_to_delete;
    for (const auto& [_, e]: node->in_edges) {
        edges_to_delete.push_back({e->src->id, e->dst->id});
    }
    for (const auto& [_, e]: node->out_edges) {
        edges_to_delete.push_back({e->src->id, e->dst->id});
    }

    delete_edges(edges_to_delete);
    delete node;
    nodes.erase(id);
}

bool DirectedGraph::check_node(int id) {
    return nodes.contains(id);
}

Node* DirectedGraph::get_node(int id) {
    if (!nodes.contains(id))
        throw node_does_not_exist;
    return nodes[id];
}

void DirectedGraph::add_edge(int src, int dst) {
    Node* src_node = get_node(src);
    Node* dst_node = get_node(dst);
    auto& edge = edges[{src, dst}];
    if (edge != nullptr)
        throw edge_exists;
    edge = new Edge(src_node, dst_node);
    src_node->out_edges[dst] = edge;
    dst_node->in_edges[src] = edge;
}

void DirectedGraph::delete_edge(int src, int dst) {
    if (!edges.contains({src, dst}))
        throw edge_does_not_exist;
    delete_edges({{src, dst}});
}

bool DirectedGraph::check_edge(int src, int dst) {
    return edges.contains({src, dst});
}

Edge* DirectedGraph::get_edge(int src, int dst) {
    if (!edges.contains({src, dst}))
        throw edge_does_not_exist;
    return edges[{src, dst}];
}

void DirectedGraph::print_edges() {
    std::cout << "Total edges: " << edges.size() << std::endl;
    for (const auto& [e, _]: edges) {
        std::cout << e.first << " -> " << e.second << std::endl;
    }
}

void DirectedGraph::print_nodes() {
    std::cout << "Total nodes: " << nodes.size() << std::endl;
    for (const auto& [node_id, _]: nodes) {
        std::cout << node_id << " ";
    }
    std::cout << std::endl;
}

void DirectedGraph::print_graph() {
    print_nodes();
    print_edges();
}

void DirectedGraph::delete_edges(const std::vector<std::pair<int, int>>& edges_to_delete) {
    for (const auto& [u, v]: edges_to_delete) {
        auto src_node = get_node(u);
        auto dst_node = get_node(v);
        src_node->out_edges.erase(v);
        dst_node->in_edges.erase(u);
        delete edges[{u, v}];
        edges.erase({u, v});
    }
}

void test() {
    DirectedGraph g;
    g.add_node(0);
    g.add_node(100);
    g.add_node(3);

    g.add_edge(0, 3);
    g.add_edge(0, 100);
    g.add_edge(3, 100);

    std::cout << "First iteration graph: " << std::endl;
    g.print_graph();

    assert(g.check_node(3));
    assert(!g.check_node(239));

    auto node0 = g.get_node(0);
    auto node100 = g.get_node(100);

    assert(node0->out_edges.size() == 2);
    assert(node0->in_edges.empty());
    assert(node0->out_edges.contains(100));
    assert(node0->out_edges[100]->dst == node100);

    assert(node100->out_edges.empty());
    assert(node100->in_edges.size() == 2);
    assert(node100->in_edges.contains(0));
    assert(node100->in_edges[0]->src == node0);

    auto edge_0_100 = g.get_edge(0, 100);
    assert(edge_0_100 == node0->out_edges[100]);
    assert(edge_0_100 == node100->in_edges[0]);

    g.add_node(239);
    g.add_edge(0, 239);
    g.add_edge(100, 239);
    g.add_edge(3, 239);
    g.delete_edge(0, 100);
    g.delete_node(3);

    std::cout << std::endl << "Second iteration graph: " << std::endl;
    g.print_graph();

    assert(!g.check_node(3));
    assert(!g.check_edge(0, 100));
    assert(!g.get_node(239)->in_edges.contains(3));
    assert(!g.get_node(0)->out_edges.contains(3));
    assert(g.get_node(239)->in_edges.size() == 2);

    std::cout << std::endl << "Tests passed!" << std::endl;
}

int main() {
    test();
}
