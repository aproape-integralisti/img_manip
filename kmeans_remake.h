#pragma once
#include "include.h"
#include "pixel.h"

constexpr double ERROR = 2;
constexpr double UPPER_BOUND = 5000;

void kMeans(vector<vector<Pixel>> &pixels, int &K) {
	vector<Pixel> centroids(K);
	auto row_size = pixels.size();
	auto col_size = pixels[0].size();

	ofstream fout("kMeans.txt");
	srand(time(NULL));

	for (int i = 0; i < K; ++i) {
		int random_number = rand() % (row_size * col_size);

		centroids[i] = pixels[random_number % row_size][random_number % col_size];
		centroids[i].cluster_id = i;
	}

	cout << "Starting the KMEANS processing..." << endl;

	int iterations_count = 0;
	bool isFinished = false;
	while (!isFinished) {
		vector<vector<double>> pixels_sum(K, vector<double>(3, 0));
		vector<int> pixels_count(K, 0);

		iterations_count++;
		clock_t time_req = clock();

		for (auto& row : pixels) {
			for (auto& pixel : row) {
				double min_dist = DBL_MAX;

				for (auto const& centroid : centroids) {
					if (min_dist > pixel.getDistance(centroid)) {
						min_dist = pixel.getDistance(centroid);
						pixel.cluster_id = centroid.cluster_id;
					}
				}

				if (min_dist > UPPER_BOUND) {
					cout << "AM INTRAT COAIE" << endl;

					centroids.push_back(pixel);
					centroids.back().cluster_id = K;
	
					pixels_count.push_back(1);
					pixels_sum.push_back({ (double)centroids.back().r, (double)centroids.back().g, (double)centroids.back().b });

					pixel.cluster_id = K++;
				}
				else {
					pixels_count[pixel.cluster_id]++;
					pixels_sum[pixel.cluster_id][0] += pixel.r;
					pixels_sum[pixel.cluster_id][1] += pixel.g;
					pixels_sum[pixel.cluster_id][2] += pixel.b;
				}
			}
		}

		isFinished = false;
		int finished_count = 0;
		for (auto &centroid : centroids) {
			//fout << "COUNT: " << pixels_count[centroid.cluster_id] << endl;
			if (pixels_count[centroid.cluster_id] == 0) {
				cout << "Count is 0 for centroid: " << centroid.cluster_id << endl;
				int rand_number = rand() % (row_size * col_size);
				int rand_row = rand_number % row_size;
				int rand_col = rand_number % col_size;

				centroid = pixels[rand_row][rand_col];
				pixels_count[pixels[rand_row][rand_col].cluster_id]--;
				pixels_sum[pixels[rand_row][rand_col].cluster_id][0] -= pixels[rand_row][rand_col].r;
				pixels_sum[pixels[rand_row][rand_col].cluster_id][1] -= pixels[rand_row][rand_col].g;
				pixels_sum[pixels[rand_row][rand_col].cluster_id][2] -= pixels[rand_row][rand_col].b;
				pixels[rand_row][rand_col].cluster_id = centroid.cluster_id;
			} else {
				double tmp_r = pixels_sum[centroid.cluster_id][0] / pixels_count[centroid.cluster_id];
				double tmp_g = pixels_sum[centroid.cluster_id][1] / pixels_count[centroid.cluster_id];
				double tmp_b = pixels_sum[centroid.cluster_id][2] / pixels_count[centroid.cluster_id];

				double err_distance = sqrt((tmp_r - (double)centroid.r) * (tmp_r - (double)centroid.r) 
					+ (tmp_g - (double)centroid.g) * (tmp_g - (double)centroid.g) 
					+ (tmp_b - (double)centroid.b) * (tmp_b - (double)centroid.b));

				//fout << " R: " << tmp_r << " G: " << tmp_g << " B: " << tmp_b << endl;

				if (err_distance < ERROR) {
					//fout << "ERROR: " << err_distance << endl << endl;
					finished_count++;
					continue;
				}

				centroid.r = tmp_r;
				centroid.g = tmp_g;
				centroid.b = tmp_b;

				//fout << "ERROR: " << err_distance;
				//fout << "SUM: " << pixels_sum[centroid.cluster_id][0] << " COUNT: " << pixels_count[centroid.cluster_id] << endl;
				//fout << "SUM: " << pixels_sum[centroid.cluster_id][1] << " COUNT: " << pixels_count[centroid.cluster_id] << endl;
				//fout << "SUM: " << pixels_sum[centroid.cluster_id][2] << " COUNT: " << pixels_count[centroid.cluster_id] << endl;
				//fout << "CENTROIDS: " << +centroid.r << " " << +centroid.g << " " << +centroid.b << endl << endl;
			}
		}
		//fout << endl << endl;

		if (finished_count == K) {
			isFinished = true;
		}

		time_req = clock() - time_req;
		cout << "It took: " << (float)time_req / CLOCKS_PER_SEC << endl;
	}

	cout << "Number of iterations: " << iterations_count << endl;
	cout << "COLORS: " << K << endl;

	for (auto& row : pixels) {
		for (auto& pixel : row) {
			pixel.r = centroids[pixel.cluster_id].r;
			pixel.g = centroids[pixel.cluster_id].g;
			pixel.b = centroids[pixel.cluster_id].b;
		}
	}
}