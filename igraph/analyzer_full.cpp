#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <igraph.h>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    auto start = high_resolution_clock::now();

    // Load the graph from the corresponding file.
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        cerr << "Error: could not open input file!\n";
        return 1;
    }
    igraph_t graph;
    igraph_read_graph_edgelist(&graph, input_file, 0, 0);
    fclose(input_file);

    // Simplify the graph (removes duplicate edges and self loops).
    igraph_simplify(&graph, 1, 1, NULL);

    // Obtain the number of nodes and edges.
    igraph_integer_t num_nodes = igraph_vcount(&graph);
    igraph_integer_t num_edges = igraph_ecount(&graph);

    // Compute the weakly connected components of the graph.
    igraph_integer_t num_wcc;
    igraph_vector_int_t wcc_map;
    igraph_vector_int_init(&wcc_map, num_nodes);
    igraph_connected_components(&graph, &wcc_map, NULL, &num_wcc, IGRAPH_WEAK);

    // Compute the degree for each vertex (we treat the graph as undirected).
    igraph_vector_int_t deg_v;
    igraph_vector_int_init(&deg_v, num_nodes);
    igraph_degree(&graph, &deg_v, igraph_vss_all(), IGRAPH_ALL, 0);
 
    // Write the results to the output CSV file.
    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        cerr << "Error: could not open output file!\n";
        return 1;
    }
    fprintf(output_file, "node_id,wcc_id,degree\n");
    for (int i = 0; i < num_nodes; i++) {
        int wcc_id = VECTOR(wcc_map)[i];
        int deg = VECTOR(deg_v)[i];
        fprintf(output_file, "%d,%d,%d\n", i, wcc_id, deg);
    }
    fclose(output_file);

    // Free the memory occupied by the graph.
    igraph_destroy(&graph);
    igraph_vector_int_destroy(&wcc_map);
    igraph_vector_int_destroy(&deg_v);
    
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<nanoseconds>(end - start);

    // Print information about the program execution. 
    // Specifically, we print the following values:
    // (1) number of nodes;
    // (2) number of edges;
    // (3) number of weakly connected components.
    cout << num_nodes << '\t' 
        << num_edges << '\t' 
        << (int) num_wcc << '\t' 
        << elapsed.count() << '\n';
    return 0;
}