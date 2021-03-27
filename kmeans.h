#pragma once

#include "include.h"
#include "pixel.h"

void kMeansClustering(vector<vector<Pixel>> &pixels, int epochs, int clusters) {
	vector<Pixel> centroids;

	// set the random speed
	srand(time(0)); 

	// Pick random centroids
	for (int i = 0; i < clusters; i++) {
		centroids.push_back(pixels[rand() & 5][rand() % 3]);
	}
	
	// provizoriu
	for (int i = 0; i < 5; i++) {

		// Assign pixels to centroids
		for (auto itr = centroids.begin(); itr != centroids.end(); itr++) {
			int clusterId = itr - centroids.begin();

			for (auto row = pixels.begin(); row != pixels.end(); row++) {
				for (auto col = row->begin(); col != row->end(); col++) {
					Pixel px = *col;
					double dist = itr->distance(px);

					if (dist < px.minDist) {
						px.minDist = dist;
						px.cluster = clusterId;
					}

					*col = px;
				}
			}
		}

		// Initialise with zeroes
		vector<int> nPixels(clusters, 0);
		vector<double> sumR(clusters, 0.0), sumG(clusters, 0.0), sumB(clusters, 0.0);

		for (auto row = pixels.begin(); row != pixels.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				int clusterId = col->cluster;

				nPixels[clusterId] += 1;
				sumR[clusterId] += col->r;
				sumG[clusterId] += col->g;
				sumB[clusterId] += col->b;

				col->minDist = DBL_MAX;
			}
		}

		for (auto itr = centroids.begin(); itr != centroids.end(); itr++) {
			int clusterId = itr - centroids.begin();

			itr->r = sumR[clusterId] / nPixels[clusterId];
			itr->g = sumG[clusterId] / nPixels[clusterId];
			itr->b = sumB[clusterId] / nPixels[clusterId];
		}
	}


	cout << "kMeans\n";
}