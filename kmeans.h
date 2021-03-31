#pragma once

#include "include.h"
#include "pixel.h"

void debugshow1(vector<Pixel> const& centroids)
{
	int dim = centroids.size();

	for (int i = 0; i < dim; i++)
	{
		cout << " [" << +centroids[i].r << "-" << +centroids[i].g << "-" << +centroids[i].b << "] ";
	}
	cout << endl << endl << endl;

	/*for (int i = 0; i < dim - 1; i++) {
		if (centroids[i].r == centroids[i + 1].r && centroids[i].g == centroids[i + 1].g && centroids[i].b == centroids[i + 1].b) {
			cout << "     OOOPS, SAME CENTROID     " << endl;
		}
	}*/
}

void debugshow2(vector<int>const& sume)
{
	for (int i = 0; i < sume.size(); i++)
	{
		//cout << sume[i] << " ";
		if (sume[i] == 0) {
			cout << "       OOOPS, PROBLEM!      " << endl;
		}
	}
	//cout << endl;
}

Pixel &pickRandomPixel(vector<vector<Pixel>> &pixels, int const &dimRow, int const &dimCol)
{
	srand(time(0));
	rand();
	rand();
	return pixels[rand() % dimRow][rand() % dimCol];
}

void centroidInit(vector<vector<Pixel>>& pixels, vector<Pixel>& centroids, Pixel*& px, double& dist, double& minDist, int const& row, int const& col, int& dimCentroids, vector<int>& nPixels, vector<double>& sumR, vector<double>& sumG, vector<double>& sumB)
{
	minDist = 10000;
	px = &pixels[row][col];

	for (int id = 0; id < dimCentroids; id++)
	{
		dist = centroids[id].distance(*px);

		if (dist < minDist)
		{
			minDist = dist;
			px->cluster = id;
		}
	}

	if (minDist == 10000)
	{
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

int kMeansClustering(vector<vector<Pixel>>& pixels, int dimCentroids) 
{
	vector<Pixel> centroids(dimCentroids);
	Pixel* px;
	
	auto dimRow = pixels.size();
	auto dimCol = pixels[0].size();

	int a = 0;

	// Pick random centroids
	for (int i = 0; i < dimCentroids; i++) 
	{
		px = &pickRandomPixel(pixels, dimRow, dimCol);
		centroids[i] = *px;
	}

	cout << "STARTING THE K-MEANS PROCESSING..." << '\n';

	uchar crtR, crtG, crtB;

	bool centroidChanged;
	double dist, minDist;


	uint8_t err = 1;
	uint16_t distErr;
	uint16_t countIterations = 0;

	vector<int> nPixels(dimCentroids);
	vector<double> sumR(dimCentroids), sumG(dimCentroids), sumB(dimCentroids);

	while (true) 
	{
		// Reinitialise with zeroes
		fill(nPixels.begin(), nPixels.end(), 0);
		fill(sumR.begin(), sumR.end(), 0.0);
		fill(sumG.begin(), sumG.end(), 0.0);
		fill(sumB.begin(), sumB.end(), 0.0);
		
		clock_t time_req = clock();

		for (int row = 0; row < dimRow; row++)
		{
			for (int col = 0; col < dimCol; col++)
			{
				centroidInit(pixels, centroids, px, dist, minDist, row, col, dimCentroids, nPixels, sumR, sumG, sumB);

				/*if (minDist == 3500) 
				{
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
				sumB[px->cluster] += px->b;*/
			}
		}

		time_req = clock() - time_req;

		cout << "It took: " << (float)time_req / CLOCKS_PER_SEC << endl;

		centroidChanged = false;

		// Recalculating the centroids
		for (int id = 0; id < dimCentroids; id++) {
			if (nPixels[id] == 0) {
				px = &pickRandomPixel(pixels, dimRow, dimCol);
				centroids[id] = *px;
				(*px).cluster = id;
				nPixels[id] = 1;
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
		
		debugshow2(nPixels);

		//TODO: minDist between two centroids

		/*
		daca distanta nu respecta minDist, se atribuie toti pixelii la unul din centroizi si celalt isi ia random
		*/

		for (int id = 0; id < dimCentroids - 1; id++) 
		{
			dist = centroids[id].distance(centroids[(static_cast<std::vector<Pixel, std::allocator<Pixel>>::size_type>(id) + 1)]);

			if (dist < 2000) {
				for (int row = 0; row < dimRow; row++) 
				{
					for (int col = 0; col < dimCol; col++) 
					{
						px = &pixels[row][col];

						if (px->cluster == id + 1) {
							px->cluster = id;
						}
					}
				}

				px = &pickRandomPixel(pixels, dimRow, dimCol);
				centroids[(static_cast<std::vector<Pixel, std::allocator<Pixel>>::size_type>(id) + 1)] = *px;
				(*px).cluster = id + 1;
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

	return dimCentroids;
}
