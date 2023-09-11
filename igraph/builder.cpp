#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
using namespace std::chrono;

/// @brief The node map represents a mapping from addresses to node identifiers
typedef unordered_map<int,int> node_map_t;

/// @brief The edge list contains pairs representing graph edges
typedef vector<pair<int,int>> edge_list_t;

/**
 * @brief Checks if the node map contains an association for the given address
 * 
 * @param map node map
 * @param address address
 * @return the node identifier if the map has an association, -1 otherwise
 */
inline int contains_id(node_map_t &map, int address) {
    node_map_t::iterator it = map.find(address);
    return ((it != map.end()) ? it->second : -1);
}

/**
 * @brief Given an address, returns the associated identifier in the node map, if there is one.
 * Otherwise, it creates a new association with a new identifier.
 * 
 * @param map node map
 * @param address address
 * @return the node identifier associated with
 */
inline int get_or_create_id(node_map_t &map, int address) {
    static int next_id = 0;
    int id = contains_id(map, address);
    if (id == -1) {
        id = next_id;
        map[address] = id;
        next_id++;
    }
    return id;
}

/**
 * @brief 
 * 
 * @param line_buf 
 * @param line_size 
 * @param nodes 
 * @param edges 
 */
void process_line(char *line_buf, size_t line_size, node_map_t &nodes, edge_list_t &edges) {
    char *token = NULL;
    int token_count = 0;
    int from, to, block_id;
    while ((token = strsep(&line_buf, ","))) {
        // Sender address
        if (token_count == 2) from = get_or_create_id(nodes, atoi(token));
        // Receiver address
        if (token_count == 3) to = get_or_create_id(nodes, atoi(token));
        token_count++;
    }
    edges.push_back(minmax(from, to));
}

int main(int argc, char **argv) {
    // Check the input arguments.
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <graph_file> <mapping_file>\n";
        return 1;
    }
    auto start = high_resolution_clock::now();
    // Open the input and output files.
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        cerr << "Error: could not open input file!\n";
        return 1;
    }
    FILE *graph_file = fopen(argv[2], "w");
    if (!graph_file) {
        cerr << "Error: could not open output graph file!\n";
        return 1;
    }
    FILE *mapping_file = fopen(argv[3], "w");
    if (!mapping_file) {
        cerr << "Error: could not open output mapping file!\n";
        return 1;
    }
    // Build the graph by reading the input file line by line.
    node_map_t nodes;
    edge_list_t edges;
    char *line_buf = NULL;
    size_t line_size = 0;
    while (getline(&line_buf, &line_size, input_file) > 0) {
        process_line(line_buf, line_size, nodes, edges);
    }
    //
    sort(edges.begin(), edges.end());
    // Write the list of edges to the graph file.
    int num_nodes = nodes.size();
    int num_edges = 0;
    for (int i = 0; i < edges.size(); i++) {
        if (i == 0 || edges[i] != edges[i-1]) {
            fprintf(graph_file, "%d\t%d\n", edges[i].first, edges[i].second);
            num_edges++;
        }
    }
    // Write the (address, node_id) mapping to the corresponding file.
    fprintf(mapping_file, "address,node_id\n");
    for (auto i : nodes) fprintf(mapping_file, "%d,%d\n", i.first, i.second);

    // Close all files.
    fclose(input_file);
    fclose(graph_file);
    fclose(mapping_file);


    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    // Print statistics. We print the following information:
    // (1) number of nodes;
    // (2) number of edges;
    // (3) graph creation time (in nanoseconds).
    cout << num_nodes << '\t' 
        << num_edges << '\t' 
        << duration.count() << '\n';
    return 0;
}