#
#   This script can be used to fit a power law distribution
#   on the degree distribution of each token network.
#
#   Author: Matteo Loporchio
#

import pandas as pd
import numpy as np
import subprocess

f = open('results/fit_deg.tsv', 'w')
f.write('contract_id\talpha\txmin\tL\tD\n')
for i in range(0, 100):
    stats = pd.read_csv(f'./igraph/results/stats_{i}.csv.gz', compression='gzip')
    largest_comp_id = stats.wcc_id.value_counts().index[0]
    data = stats[stats.wcc_id == largest_comp_id].degree.values
    np.savetxt(f'tmp/tmp_{i}.out', data, fmt="%.6f", delimiter='\n')
    p = subprocess.run(['./igraph/pl_fit', f'tmp/tmp_{i}.out'], capture_output=True)
    p_out = p.stdout.decode('utf-8').rstrip()
    f.write(f'{i}\t{p_out}\n')
f.close()