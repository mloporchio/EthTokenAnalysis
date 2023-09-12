#
# This script tests all possible feature combinations with K-means clustering.
# For each feature subset, it tests all values of k from a minimum of 2 to a maximum of 20 (included).
# For each configuration, it prints the silhouette and homogeneity scores.
# Homogeneity is computed with respect to the manually-assigned labels describing the application domain
# of the token network.
#
# Author: Matteo Loporchio
#

import pandas as pd
import numpy as np
import itertools
from sklearn.cluster import *
from sklearn.metrics import *
from sklearn.preprocessing import *

# List of features used for clustering
features = ['coverage', 'alpha', 'error', 'diameter', 'est_apl', 'transitivity', 'density']
# Path of the output file
output_file = 'results/kmeans.csv'

final = pd.read_csv('results/final.csv')
kmin = 2
kmax = 20
categories = final.category_id.values
pt = PowerTransformer()

fh = open(output_file, 'w')
fh.write('features,k,silhouette,homogeneity\n')
for num_features in range(1, len(features)+1):
    for x in list(itertools.combinations(features, num_features)):
        feature_subset = list(x)
        feature_subset_str = ' '.join(feature_subset)
        clust_data = pt.fit_transform(final[feature_subset])
        for k in np.arange(kmin, kmax+1):
            kmeans = KMeans(init='k-means++', n_clusters=k, n_init=100, max_iter=1000, random_state=1)
            pred_labels = kmeans.fit_predict(clust_data)
            sil = silhouette_score(clust_data, pred_labels)
            hom = homogeneity_score(categories, pred_labels)
            fh.write(f'{feature_subset_str},{k},{sil},{hom}\n')
fh.close()
