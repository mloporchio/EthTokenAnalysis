#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <igraph.h>

using namespace std;

int main(int argc, char **argv) {
    // Check the input arguments.
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    // Open the input file.
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        cerr << "Error: could not open input file!\n";
        return 1;
    }

    // Read data from the input file.
    char *line_buf = NULL;
    size_t line_size = 0;
    vector<igraph_real_t> values;
    while (getline(&line_buf, &line_size, input_file) > 0) {
        values.push_back((igraph_real_t) strtod(line_buf, NULL));
    }
    // Close the input file.
    fclose(input_file);

    // Initialize igraph vector.
    igraph_vector_t degree;
    igraph_real_t *ptr = (igraph_real_t *) values.data();
    igraph_vector_init_array(&degree, ptr, values.size());

    // Fit power law.
    igraph_plfit_result_t model;
    igraph_power_law_fit(&degree, &model, /* xmin = */ -1, /* force_continuous = */ 0);
    igraph_vector_destroy(&degree);

    /* If you also need a p-value: */
    /* igraph_plfit_result_calculate_p_value(&model, &p, 0.001); */

    // Print results.
    fprintf(stdout, "%.6f\t%.6f\t%.6f\t%.6f\n", model.alpha, model.xmin, model.L, model.D);

    return 0;
}