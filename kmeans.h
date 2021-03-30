#pragma once

#include "include.h"
#include "pixel.h"

void debugshow1(vector<Pixel> const& centroids)
{
	for (int i = 0; i < centroids.size(); i++)
	{
		cout << +centroids[i].r << "-" << +centroids[i].g << "-" << +centroids[i].b << " ";
	}
	cout << endl;
}

void debugshow2(vector<int>const& sume)
{
	for (int i = 0; i < sume.size(); i++)
	{
		cout << sume[i] << " ";
	}
	cout << endl;
}

void kMeansClustering(vector<vector<Pixel>>& pixels, int clusters) {
	vector<Pixel> centroids;
	int a = 0;
	// Set the random speed
	srand(time(0));

	auto dim_row = pixels.size();
	auto dim_col = pixels[0].size();

	// Pick random centroids
	for (int i = 0; i < clusters; i++) 
	{
		centroids.push_back(pixels[rand() % (dim_row)][rand() % (dim_col)]);
	}

	// Counting number of centroids to check if we must stop
	int crt_centroids = 0;

	cout << "STARTING THE K-MEANS PROCESSING..." << '\n';

	while (true) 
	{
		crt_centroids = 0;
		// cout << "CENTROIDS MODIFIED ONCE" << '\n';
		// Assign pixels to centroids
		for (auto itr = centroids.begin(); itr != centroids.end(); itr++) 
		{
			int clusterId = itr - centroids.begin();

			for (auto row = pixels.begin(); row != pixels.end(); row++) 
			{
				for (auto col = row->begin(); col != row->end(); col++) 
				{
					Pixel px = *col;
					double dist = itr->distance(px);

					if (dist < px.minDist) 
					{
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

		// Recalculating the centroids
		for (auto itr = centroids.begin(); itr != centroids.end(); itr++)
		{
			int clusterId = itr - centroids.begin();

			uchar crt_r, crt_g, crt_b;

			if ((sumR[clusterId] / nPixels[clusterId] < 0 || sumR[clusterId] / nPixels[clusterId] > 255) ||
				(sumG[clusterId] / nPixels[clusterId] < 0 || sumG[clusterId] / nPixels[clusterId] > 255) ||
				(sumB[clusterId] / nPixels[clusterId] < 0 || sumB[clusterId] / nPixels[clusterId] > 255))
			{
				cout << "OVERFLOW" << '\n';

				exit(-1);
			}
			if (nPixels[clusterId] == 0) 
			{
				int pozr = rand() % (dim_row);
				int pozc = rand() % (dim_col);
				*itr = pixels[pozr][pozc];
				pixels[pozr][pozc].cluster = clusterId;
			}
			else 
			{
				crt_r = sumR[clusterId] / nPixels[clusterId]; // div 0 !!!!
				crt_g = sumG[clusterId] / nPixels[clusterId]; // overflow >256
				crt_b = sumB[clusterId] / nPixels[clusterId];

				uint16_t err = 1; //TODO: distance between centroids
				// schimbareCentroids = false -> true (daca ramane false -> return)

				if ((crt_r < itr->r - err || crt_r > itr->r + err)
					&& (crt_b < itr->b - err || crt_b > itr->r + err)
					&& (crt_g < itr->g - err || crt_g > itr->g + err))
				{
					itr->r = crt_r;
					itr->g = crt_g;
					itr->b = crt_b;

					crt_centroids++;
				}
			}
		}

		// Stop when no centroids were modified in the last iteration
		if (crt_centroids == 0)
		{
			cout << "THE K-MEANS PROCESSING IS COMPLETE" << '\n';
			break;
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