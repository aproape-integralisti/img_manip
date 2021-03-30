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
	Pixel* px;
	
	auto dimRow = pixels.size();
	auto dimCol = pixels[0].size();
	
	int a = 0;

	// Set the random speed
	srand(time(0));

	// Pick random centroids
	for (int i = 0; i < clusters; i++) 
	{
		centroids.push_back(pixels[rand() % (dimRow)][rand() % (dimCol)]);
	}

	auto dimCentroids = centroids.size();

	// Counting number of centroids to check if we must stop
	bool centroidChanged = false;

	cout << "STARTING THE K-MEANS PROCESSING..." << '\n';

	while (true) 
	{
		centroidChanged = false;
		// cout << "CENTROIDS MODIFIED ONCE" << '\n';
		double dist, minDist;
		

		// Initialise with zeroes
		vector<int> nPixels(clusters, 0);
		vector<double> sumR(clusters, 0.0), sumG(clusters, 0.0), sumB(clusters, 0.0);

		for (int row = 0; row < dimRow; row++)
		{
			for (int col = 0; col < dimCol; col++)
			{
				minDist = DBL_MAX;
				px = &pixels[row][col];

				for (int Id = 0; Id < dimCentroids; Id++)
				{
					dist = centroids[Id].distance(*px);

					if(dist < minDist)
					{
						minDist = dist;
						px->cluster = Id;
					}
				}

				nPixels[px->cluster] += 1;
				sumR[px->cluster] += px->r;
				sumG[px->cluster] += px->g;
				sumB[px->cluster] += px->b;
			}
		}

		// Recalculating the centroids
		for (int Id = 0; Id < dimCentroids; Id++)
		{
			uchar crtR, crtG, crtB;

			if ((sumR[Id] / nPixels[Id] < 0 || sumR[Id] / nPixels[Id] > 255) ||
				(sumG[Id] / nPixels[Id] < 0 || sumG[Id] / nPixels[Id] > 255) ||
				(sumB[Id] / nPixels[Id] < 0 || sumB[Id] / nPixels[Id] > 255))
			{
				cout << "OVERFLOW" << '\n';

				exit(-1);
			}
			if (nPixels[Id] == 0) 
			{
				int pozR = rand() % (dimRow);
				int pozC = rand() % (dimCol);
				centroids[Id] = pixels[pozR][pozC];
				pixels[pozR][pozC].cluster = Id;
			}
			else 
			{
				crtR = sumR[Id] / nPixels[Id]; // div 0 !!!!
				crtG = sumG[Id] / nPixels[Id]; // overflow >256
				crtB = sumB[Id] / nPixels[Id];
				
				uint16_t distErr = (crtR - centroids[Id].r) * (crtR - centroids[Id].r)
					+ (crtG - centroids[Id].g) * (crtG - centroids[Id].g) 
					+ (crtB - centroids[Id].b) * (crtB - centroids[Id].b);

				centroids[Id].r = crtR;
				centroids[Id].g = crtG;
				centroids[Id].b = crtB;

				uint8_t err = 1;
				if (distErr > err)
				{
					centroidChanged = true;
				}
			}
		}

		// Stop when no centroids were modified in the last iteration
		if (centroidChanged == false)
		{
			cout << "THE K-MEANS PROCESSING IS COMPLETE" << '\n';
			break;
		}
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