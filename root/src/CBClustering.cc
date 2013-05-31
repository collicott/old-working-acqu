#include "CBClustering.h"

//****** stuff that should go into .cc file ******

void CBClustering::_setupFired( const int* pattern, const int ncryst ) {

	for( int i=0; i<ncryst; ++i )
		clid[ pattern[i] ] = -3;

};

void CBClustering::_clear() {

	id = 0;

	for( unsigned int i=0; i<180; ++i ) {
		clid[i] = -1;
	}

};

void CBClustering::PrintResult( const int* pattern,  const int nclust ) const {
	for( int i =0; i<nclust; ++i )
		std::cout << " crystal id: " << std::setw(3) << pattern[i] << " cluster id: " << clid[ pattern[i] ] << std::endl;
};

bool CBClustering::NumberNeighbours( const int cluster, const unsigned int _id ) {

	if( isFired( cluster ) && !isVisited( cluster ) ) {

		clid[ cluster ] = _id;

		for( int n=0; n<3; ++n )
			NumberNeighbours( N4[ cluster ][ n ], _id );

		return true;
	}

	return false;

};

unsigned int CBClustering::NumClusters( const int* pattern, const int nclust ) {

	_clear();
	_setupFired( pattern, nclust );

	for( int c=0; c< nclust; ++c ) {

		if( NumberNeighbours( pattern[c], id) )
			++id;
	}

	return id;

};


const int CBClustering::N4[180][12] =
{{ 144, 36, 1, 145, 108, 72, 37, 12, 2, 144, 38, 156},
	{ 12, 2, 0, 38, 13, 3, 156, 144, 36, 14, 145, 37},
	{ 156, 1, 3, 157, 145, 0, 12, 14, 4, 144, 13, 168},
	{ 14, 4, 2, 13, 15, 5, 168, 156, 1, 16, 157, 12},
	{ 168, 3, 5, 169, 157, 2, 14, 16, 6, 156, 15, 6},
	{ 16, 6, 4, 15, 17, 7, 169, 168, 3, 18, 168, 14},
	{ 169, 5, 7, 170, 168, 4, 16, 18, 8, 4, 17, 171},
	{ 18, 8, 6, 17, 19, 9, 171, 169, 5, 20, 170, 16},
	{ 171, 7, 9, 172, 170, 6, 18, 20, 10, 169, 19, 173},
	{ 20, 10, 8, 19, 21, 11, 173, 171, 7, 22, 172, 18},
	{ 173, 9, 11, 174, 172, 8, 20, 22, 175, 171, 21, 175},
	{ 22, 175, 10, 21, 23, 176, 174, 173, 9, 177, 173, 20},
	{ 1, 38, 13, 2, 0, 37, 39, 24, 14, 36, 40, 3},
	{ 24, 14, 12, 40, 25, 15, 3, 1, 38, 26, 2, 39},
	{ 3, 13, 15, 4, 2, 12, 24, 26, 16, 1, 25, 5},
	{ 26, 16, 14, 25, 27, 17, 5, 3, 13, 28, 4, 24},
	{ 5, 15, 17, 6, 4, 14, 26, 28, 18, 3, 27, 7},
	{ 28, 18, 16, 27, 29, 19, 7, 5, 15, 30, 6, 26},
	{ 7, 17, 19, 8, 6, 16, 28, 30, 20, 5, 29, 9},
	{ 30, 20, 18, 29, 31, 21, 9, 7, 17, 32, 8, 28},
	{ 9, 19, 21, 10, 8, 18, 30, 32, 22, 7, 31, 11},
	{ 32, 22, 20, 31, 33, 23, 11, 9, 19, 34, 10, 30},
	{ 11, 21, 23, 175, 10, 20, 32, 34, 177, 9, 33, 176},
	{ 34, 177, 22, 33, 35, 178, 176, 11, 21, 179, 175, 32},
	{ 13, 40, 25, 14, 12, 39, 41, 42, 26, 38, 42, 15},
	{ 42, 26, 24, 41, 43, 27, 15, 13, 40, 44, 14, 40},
	{ 15, 25, 27, 16, 14, 24, 42, 44, 28, 13, 43, 17},
	{ 44, 28, 26, 43, 45, 29, 17, 15, 25, 46, 16, 42},
	{ 17, 27, 29, 18, 16, 26, 44, 46, 30, 15, 45, 19},
	{ 46, 30, 28, 45, 47, 31, 19, 17, 27, 31, 18, 44},
	{ 19, 29, 31, 20, 18, 28, 46, 47, 32, 17, 47, 21},
	{ 47, 32, 30, 46, 58, 33, 21, 19, 29, 59, 20, 29},
	{ 21, 31, 33, 22, 20, 30, 47, 59, 34, 19, 58, 23},
	{ 59, 34, 32, 58, 70, 35, 23, 21, 31, 71, 22, 47},
	{ 23, 33, 35, 177, 22, 32, 59, 71, 179, 21, 70, 178},
	{ 71, 179, 34, 70, 107, 143, 178, 23, 33, 71, 177, 59},
	{ 0, 72, 37, 1, 144, 108, 73, 48, 38, 0, 74, 12},
	{ 48, 38, 36, 74, 49, 39, 12, 0, 72, 50, 1, 73},
	{ 12, 37, 39, 13, 1, 36, 48, 50, 40, 0, 49, 24},
	{ 50, 40, 38, 49, 51, 41, 24, 12, 37, 52, 13, 48},
	{ 24, 39, 41, 25, 13, 38, 50, 52, 42, 12, 51, 42},
	{ 52, 42, 40, 51, 53, 43, 25, 24, 39, 54, 24, 50},
	{ 25, 41, 43, 26, 24, 40, 52, 54, 44, 40, 53, 27},
	{ 54, 44, 42, 53, 55, 45, 27, 25, 41, 56, 26, 52},
	{ 27, 43, 45, 28, 26, 42, 54, 56, 46, 25, 55, 29},
	{ 56, 46, 44, 55, 57, 47, 29, 27, 43, 58, 28, 54},
	{ 29, 45, 47, 30, 28, 44, 56, 58, 31, 27, 57, 31},
	{ 58, 31, 46, 57, 59, 32, 30, 29, 45, 33, 29, 56},
	{ 37, 74, 49, 38, 36, 73, 75, 60, 50, 72, 76, 39},
	{ 60, 50, 48, 76, 61, 51, 39, 37, 74, 62, 38, 75},
	{ 39, 49, 51, 40, 38, 48, 60, 62, 52, 37, 61, 41},
	{ 62, 52, 50, 61, 63, 53, 41, 39, 49, 64, 40, 60},
	{ 41, 51, 53, 42, 40, 50, 62, 64, 54, 39, 63, 43},
	{ 64, 54, 52, 63, 65, 55, 43, 41, 51, 66, 42, 62},
	{ 43, 53, 55, 44, 42, 52, 64, 66, 56, 41, 65, 45},
	{ 66, 56, 54, 65, 67, 57, 45, 43, 53, 68, 44, 64},
	{ 45, 55, 57, 46, 44, 54, 66, 68, 58, 43, 67, 47},
	{ 68, 58, 56, 67, 69, 59, 47, 45, 55, 70, 46, 66},
	{ 47, 57, 59, 31, 46, 56, 68, 70, 33, 45, 69, 32},
	{ 70, 33, 58, 69, 71, 34, 32, 47, 57, 35, 31, 68},
	{ 49, 76, 61, 50, 48, 75, 77, 78, 62, 74, 78, 51},
	{ 78, 62, 60, 77, 79, 63, 51, 49, 76, 80, 50, 76},
	{ 51, 61, 63, 52, 50, 60, 78, 80, 64, 49, 79, 53},
	{ 80, 64, 62, 79, 81, 65, 53, 51, 61, 82, 52, 78},
	{ 53, 63, 65, 54, 52, 62, 80, 82, 66, 51, 81, 55},
	{ 82, 66, 64, 81, 83, 67, 55, 53, 63, 67, 54, 80},
	{ 55, 65, 67, 56, 54, 64, 82, 83, 68, 53, 83, 57},
	{ 83, 68, 66, 82, 94, 69, 57, 55, 65, 95, 56, 65},
	{ 57, 67, 69, 58, 56, 66, 83, 95, 70, 55, 94, 59},
	{ 95, 70, 68, 94, 106, 71, 59, 57, 67, 107, 58, 83},
	{ 59, 69, 71, 33, 58, 68, 95, 107, 35, 57, 106, 34},
	{ 107, 35, 70, 106, 143, 179, 34, 59, 69, 107, 33, 95},
	{ 36, 108, 73, 37, 0, 144, 109, 84, 74, 36, 110, 48},
	{ 84, 74, 72, 110, 85, 75, 48, 36, 108, 86, 37, 109},
	{ 48, 73, 75, 49, 37, 72, 84, 86, 76, 36, 85, 60},
	{ 86, 76, 74, 85, 87, 77, 60, 48, 73, 88, 49, 84},
	{ 60, 75, 77, 61, 49, 74, 86, 88, 78, 48, 87, 78},
	{ 88, 78, 76, 87, 89, 79, 61, 60, 75, 90, 60, 86},
	{ 61, 77, 79, 62, 60, 76, 88, 90, 80, 76, 89, 63},
	{ 90, 80, 78, 89, 91, 81, 63, 61, 77, 92, 62, 88},
	{ 63, 79, 81, 64, 62, 78, 90, 92, 82, 61, 91, 65},
	{ 92, 82, 80, 91, 93, 83, 65, 63, 79, 94, 64, 90},
	{ 65, 81, 83, 66, 64, 80, 92, 94, 67, 63, 93, 67},
	{ 94, 67, 82, 93, 95, 68, 66, 65, 81, 69, 65, 92},
	{ 73, 110, 85, 74, 72, 109, 111, 96, 86, 108, 112, 75},
	{ 96, 86, 84, 112, 97, 87, 75, 73, 110, 98, 74, 111},
	{ 75, 85, 87, 76, 74, 84, 96, 98, 88, 73, 97, 77},
	{ 98, 88, 86, 97, 99, 89, 77, 75, 85, 100, 76, 96},
	{ 77, 87, 89, 78, 76, 86, 98, 100, 90, 75, 99, 79},
	{ 100, 90, 88, 99, 101, 91, 79, 77, 87, 102, 78, 98},
	{ 79, 89, 91, 80, 78, 88, 100, 102, 92, 77, 101, 81},
	{ 102, 92, 90, 101, 103, 93, 81, 79, 89, 104, 80, 100},
	{ 81, 91, 93, 82, 80, 90, 102, 104, 94, 79, 103, 83},
	{ 104, 94, 92, 103, 105, 95, 83, 81, 91, 106, 82, 102},
	{ 83, 93, 95, 67, 82, 92, 104, 106, 69, 81, 105, 68},
	{ 106, 69, 94, 105, 107, 70, 68, 83, 93, 71, 67, 104},
	{ 85, 112, 97, 86, 84, 111, 113, 114, 98, 110, 114, 87},
	{ 114, 98, 96, 113, 115, 99, 87, 85, 112, 116, 86, 112},
	{ 87, 97, 99, 88, 86, 96, 114, 116, 100, 85, 115, 89},
	{ 116, 100, 98, 115, 117, 101, 89, 87, 97, 118, 88, 114},
	{ 89, 99, 101, 90, 88, 98, 116, 118, 102, 87, 117, 91},
	{ 118, 102, 100, 117, 119, 103, 91, 89, 99, 103, 90, 116},
	{ 91, 101, 103, 92, 90, 100, 118, 119, 104, 89, 119, 93},
	{ 119, 104, 102, 118, 130, 105, 93, 91, 101, 131, 92, 101},
	{ 93, 103, 105, 94, 92, 102, 119, 131, 106, 91, 130, 95},
	{ 131, 106, 104, 130, 142, 107, 95, 93, 103, 143, 94, 119},
	{ 95, 105, 107, 69, 94, 104, 131, 143, 71, 93, 142, 70},
	{ 143, 71, 106, 142, 179, 35, 70, 95, 105, 143, 69, 131},
	{ 72, 144, 109, 73, 36, 0, 145, 120, 110, 72, 146, 84},
	{ 120, 110, 108, 146, 121, 111, 84, 72, 144, 122, 73, 145},
	{ 84, 109, 111, 85, 73, 108, 120, 122, 112, 72, 121, 96},
	{ 122, 112, 110, 121, 123, 113, 96, 84, 109, 124, 85, 120},
	{ 96, 111, 113, 97, 85, 110, 122, 124, 114, 84, 123, 114},
	{ 124, 114, 112, 123, 125, 115, 97, 96, 111, 126, 96, 122},
	{ 97, 113, 115, 98, 96, 112, 124, 126, 116, 112, 125, 99},
	{ 126, 116, 114, 125, 127, 117, 99, 97, 113, 128, 98, 124},
	{ 99, 115, 117, 100, 98, 114, 126, 128, 118, 97, 127, 101},
	{ 128, 118, 116, 127, 129, 119, 101, 99, 115, 130, 100, 126},
	{ 101, 117, 119, 102, 100, 116, 128, 130, 103, 99, 129, 103},
	{ 130, 103, 118, 129, 131, 104, 102, 101, 117, 105, 101, 128},
	{ 109, 146, 121, 110, 108, 145, 147, 132, 122, 144, 148, 111},
	{ 132, 122, 120, 148, 133, 123, 111, 109, 146, 134, 110, 147},
	{ 111, 121, 123, 112, 110, 120, 132, 134, 124, 109, 133, 113},
	{ 134, 124, 122, 133, 135, 125, 113, 111, 121, 136, 112, 132},
	{ 113, 123, 125, 114, 112, 122, 134, 136, 126, 111, 135, 115},
	{ 136, 126, 124, 135, 137, 127, 115, 113, 123, 138, 114, 134},
	{ 115, 125, 127, 116, 114, 124, 136, 138, 128, 113, 137, 117},
	{ 138, 128, 126, 137, 139, 129, 117, 115, 125, 140, 116, 136},
	{ 117, 127, 129, 118, 116, 126, 138, 140, 130, 115, 139, 119},
	{ 140, 130, 128, 139, 141, 131, 119, 117, 127, 142, 118, 138},
	{ 119, 129, 131, 103, 118, 128, 140, 142, 105, 117, 141, 104},
	{ 142, 105, 130, 141, 143, 106, 104, 119, 129, 107, 103, 140},
	{ 121, 148, 133, 122, 120, 147, 149, 150, 134, 146, 150, 123},
	{ 150, 134, 132, 149, 151, 135, 123, 121, 148, 152, 122, 148},
	{ 123, 133, 135, 124, 122, 132, 150, 152, 136, 121, 151, 125},
	{ 152, 136, 134, 151, 153, 137, 125, 123, 133, 154, 124, 150},
	{ 125, 135, 137, 126, 124, 134, 152, 154, 138, 123, 153, 127},
	{ 154, 138, 136, 153, 155, 139, 127, 125, 135, 139, 126, 152},
	{ 127, 137, 139, 128, 126, 136, 154, 155, 140, 125, 155, 129},
	{ 155, 140, 138, 154, 166, 141, 129, 127, 137, 167, 128, 137},
	{ 129, 139, 141, 130, 128, 138, 155, 167, 142, 127, 166, 131},
	{ 167, 142, 140, 166, 178, 143, 131, 129, 139, 179, 130, 155},
	{ 131, 141, 143, 105, 130, 140, 167, 179, 107, 129, 178, 106},
	{ 179, 107, 142, 178, 35, 71, 106, 131, 141, 179, 105, 167},
	{ 108, 0, 145, 109, 72, 36, 1, 156, 146, 108, 2, 120},
	{ 156, 146, 144, 2, 157, 147, 120, 108, 0, 158, 109, 1},
	{ 120, 145, 147, 121, 109, 144, 156, 158, 148, 108, 157, 132},
	{ 158, 148, 146, 157, 159, 149, 132, 120, 145, 160, 121, 156},
	{ 132, 147, 149, 133, 121, 146, 158, 160, 150, 120, 159, 150},
	{ 160, 150, 148, 159, 161, 151, 133, 132, 147, 162, 132, 158},
	{ 133, 149, 151, 134, 132, 148, 160, 162, 152, 148, 161, 135},
	{ 162, 152, 150, 161, 163, 153, 135, 133, 149, 164, 134, 160},
	{ 135, 151, 153, 136, 134, 150, 162, 164, 154, 133, 163, 137},
	{ 164, 154, 152, 163, 165, 155, 137, 135, 151, 166, 136, 162},
	{ 137, 153, 155, 138, 136, 152, 164, 166, 139, 135, 165, 139},
	{ 166, 139, 154, 165, 167, 140, 138, 137, 153, 141, 137, 164},
	{ 145, 2, 157, 146, 144, 1, 3, 168, 158, 0, 4, 147},
	{ 168, 158, 156, 4, 169, 159, 147, 145, 2, 170, 146, 3},
	{ 147, 157, 159, 148, 146, 156, 168, 170, 160, 145, 169, 149},
	{ 170, 160, 158, 169, 171, 161, 149, 147, 157, 172, 148, 168},
	{ 149, 159, 161, 150, 148, 158, 170, 172, 162, 147, 171, 151},
	{ 172, 162, 160, 171, 173, 163, 151, 149, 159, 174, 150, 170},
	{ 151, 161, 163, 152, 150, 160, 172, 174, 164, 149, 173, 153},
	{ 174, 164, 162, 173, 175, 165, 153, 151, 161, 176, 152, 172},
	{ 153, 163, 165, 154, 152, 162, 174, 176, 166, 151, 175, 155},
	{ 176, 166, 164, 175, 177, 167, 155, 153, 163, 178, 154, 174},
	{ 155, 165, 167, 139, 154, 164, 176, 178, 141, 153, 177, 140},
	{ 178, 141, 166, 177, 179, 142, 140, 155, 165, 143, 139, 176},
	{ 157, 4, 169, 158, 156, 3, 5, 6, 170, 2, 6, 159},
	{ 6, 170, 168, 5, 7, 171, 159, 157, 4, 8, 158, 4},
	{ 159, 169, 171, 160, 158, 168, 6, 8, 172, 157, 7, 161},
	{ 8, 172, 170, 7, 9, 173, 161, 159, 169, 10, 160, 6},
	{ 161, 171, 173, 162, 160, 170, 8, 10, 174, 159, 9, 163},
	{ 10, 174, 172, 9, 11, 175, 163, 161, 171, 175, 162, 8},
	{ 163, 173, 175, 164, 162, 172, 10, 11, 176, 161, 11, 165},
	{ 11, 176, 174, 10, 22, 177, 165, 163, 173, 23, 164, 173},
	{ 165, 175, 177, 166, 164, 174, 11, 23, 178, 163, 22, 167},
	{ 23, 178, 176, 22, 34, 179, 167, 165, 175, 35, 166, 11},
	{ 167, 177, 179, 141, 166, 176, 23, 35, 143, 165, 34, 142},
	{ 35, 143, 178, 34, 71, 107, 142, 167, 177, 35, 141, 23}};


