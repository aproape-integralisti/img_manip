#pragma once

#include "include.h"
#include "pixel.h"

void kMeansClustering(vector<vector<Pixel>> &pixels, int epochs, int k) {
	vector<Pixel> centroids;

	// set the random speed
	srand(time(0)); 

	// Pick random centroids
	for (int i = 0; i < k; i++) {
		centroids.push_back(pixels[rand() & 5][rand() % 3]);
	}
	
	// Assign pixels to centroids
	for (auto c = centroids.begin(); c != centroids.end(); c++) {
		int clusterId = c - centroids.begin();

		for (auto row = pixels.begin(); row != pixels.end(); row++) {
			for (auto col = row->begin(); col != row->end(); col++) {
				Pixel px = *col;
				double dist = c->distance(px);

				if (dist < px.minDist) {
					px.minDist = dist;
					px.cluster = clusterId;
				}
				*col = px;
				cout << px.cluster << " ";
			}
		}
		
		// Initialise with zeroes
		vector<int> nPixels(k, 0);
		vector<double> sumR(k, 0.0), sumG(k, 0.0), sumB(k, 0.0);


	}

	cout << "kMeans\n";
}