#pragma once

#include "include.h"
#include "pixel.h"

void kMeansClustering(vector<vector<Pixel>>& pixels, int clusters) {
	vector<Pixel> centroids;
	bool c_changed = true;
	int a = 0;
	// set the random speed
	srand(time(0));

	// Pick random centroids
	for (int i = 0; i < clusters; i++) {
		centroids.push_back(pixels[rand() & 5][rand() % 3]);
	}

	while (a < 20) {
		c_changed = true;
		a++;
		cout << "CENTROIDS MODIFIED ONCE" << '\n';
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

		for (auto row = pixels.begin(); row != pixels.end(); row++) 
		{
			for (auto col = row->begin(); col != row->end(); col++) 
			{
				int clusterId = col->cluster;

				Pixel px = *col;

				nPixels[clusterId] += 1;
				sumR[clusterId] += px.r;
				sumG[clusterId] += px.g;
				sumB[clusterId] += px.b;

				col->minDist = DBL_MAX;
			}
		}

		for (auto itr = centroids.begin(); itr != centroids.end(); itr++) 
		{
			int clusterId = itr - centroids.begin();

			uchar crt_r, crt_g, crt_b;

			crt_r = sumR[clusterId] / nPixels[clusterId];
			crt_g = sumG[clusterId] / nPixels[clusterId];
			crt_b = sumB[clusterId] / nPixels[clusterId];

			/*if(!((crt_r >= itr->r - 1 || crt_r <= itr->r + 1) &&
			(crt_b >= itr->b - 1 || crt_b <= itr->b + 1) &&
			(crt_g >= itr->g - 1 || crt_g <= itr->g + 1)))
			{
				
				c_changed = false;
			}
			else {*/

			itr->r = crt_r;
			itr->g = crt_g;
			itr->b = crt_b;
		}
	}

	for (auto row = pixels.begin(); row != pixels.end(); row++)
	{
		for (auto col = row->begin(); col != row->end(); col++)
		{
			Pixel px = *col;

			px.r = centroids[px.cluster].r;
			px.g = centroids[px.cluster].g;
			px.b = centroids[px.cluster].b;

			*col = px;
		}
	}

}