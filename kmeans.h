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

void kMeansClustering(vector<vector<Pixel>>& pixels, int dimCentroids) {
	vector<Pixel> centroids;
	Pixel* px;
	
	auto dimRow = pixels.size();
	auto dimCol = pixels[0].size();

	int a = 0;

	// Set the random speed
	srand(time(0));

	// Pick random centroids
	for (int i = 0; i < dimCentroids; i++) 
	{
		centroids.push_back(pixels[rand() % (dimRow)][rand() % (dimCol)]);
	}

	bool centroidChanged;
	int countIterations = 0;
	cout << "STARTING THE K-MEANS PROCESSING..." << '\n';

	while (true) 
	{
		// Initialise with zeroes
		vector<int> nPixels(dimCentroids, 0);
		vector<double> sumR(dimCentroids, 0.0), sumG(dimCentroids, 0.0), sumB(dimCentroids, 0.0);

		double dist, minDist;
		
		for (int row = 0; row < dimRow; row++)
		{
			for (int col = 0; col < dimCol; col++)
			{
				minDist = 5000;
				px = &pixels[row][col];

				for (int id = 0; id < dimCentroids; id++)
				{
					dist = centroids[id].distance(*px);

					if(dist < minDist)
					{
						minDist = dist;
						px->cluster = id;
					}
				}

				if (minDist == 5000) {
					dimCentroids++;
					centroids.push_back(*px);
					px->cluster = dimCentroids - 1;
					nPixels.push_back(0);
					sumR.push_back(0.0);
					sumG.push_back(0.0);
					sumB.push_back(0.0);
				}

				nPixels[px->cluster] += 1;
				sumR[px->cluster] += px->r;
				sumG[px->cluster] += px->g;
				sumB[px->cluster] += px->b;
			}
		}

		uchar crtR, crtG, crtB;
		uint8_t err = 1;
		uint16_t distErr;
		centroidChanged = false;

		// Recalculating the centroids
		for (int id = 0; id < dimCentroids; id++) {
			if (nPixels[id] == 0) {
				int rowPoz = rand() % dimRow;
				int colPoz = rand() % dimCol;
				centroids[id] = pixels[rowPoz][colPoz];
				pixels[rowPoz][colPoz].cluster = id;
			}
			else {
				crtR = sumR[id] / nPixels[id];
				crtG = sumG[id] / nPixels[id];
				crtB = sumB[id] / nPixels[id];

				distErr = (crtR - centroids[id].r) * (crtR - centroids[id].r)
					+ (crtG - centroids[id].g) * (crtG - centroids[id].g)
					+ (crtB - centroids[id].b) * (crtB - centroids[id].b);

				centroids[id].r = crtR;
				centroids[id].g = crtG;
				centroids[id].b = crtB;

				if (distErr > err)
				{
					centroidChanged = true;
				}
			}
		}

		//TODO: minDist between two centroids

		/*
		daca distanta nu respecta minDist, se atribuie toti pixelii la unul din centroizi si celalt isi ia random
		*/

		for (int id = 0; id < dimCentroids - 1; id++) {
			dist = centroids[id].distance(centroids[id + 1]);

			if (dist < 100) {
				for (int row = 0; row < dimRow; row++) {
					for (int col = 0; col < dimCol; col++) {
						px = &pixels[row][col];

						if (px->cluster == id) {
							px->cluster = id + 1;
						}
					}
				}

				int rowPoz = rand() % dimRow;
				int colPoz = rand() % dimCol;
				centroids[id + 1] = pixels[rowPoz][colPoz];
				pixels[rowPoz][colPoz].cluster = id + 1;
			}
		}

		// Stop when no centroids were modified in the last iteration
		if (centroidChanged == false)
		{
			cout << "THE K-MEANS PROCESSING IS COMPLETE" << endl;
			cout << "No of iterations: " << countIterations << endl;
			cout << "No of colors: " << dimCentroids << endl;
			break;
		}

		countIterations++;
	}

	for (int row = 0; row < dimRow; row++)
	{
		for (int col = 0; col < dimCol; col++)
		{
			px = &pixels[row][col];

			px->r = centroids[px->cluster].r;
			px->g = centroids[px->cluster].g;
			px->b = centroids[px->cluster].b;
		}
	}
}