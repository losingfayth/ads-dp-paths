/**
 * Simulates a checkboard pyramid of a given depth and calculates the number of
 * paths from the tip of the pyramid to a given sqaure on the base of the
 * pyramid.
 *
 * Example:
 * 					   (5,3)
 * 			 0           #
 * 			 1         #   #
 * 			 2       #   #   #
 * 			 3     #   #   #   #
 * 			 4   #   #   #   #   #
 * 	Depth -> 5 #   #   #   *   #   #
 * 		       0 1 2 3 4 5 6 7 8 9 10
 * 			   0   1   2   3   4   5
 * 						   ^
 * 						Goal Row
 *
 *
 * @author fayth quinn
 */

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

long recursive_path(int m, int n);
long recursive_backtracking_path(int m, int n);
long dynamic_path(int m, int n);

int main(int argc, char *argv[])
{
	if (argc > 0)
	{

		auto start_1 = high_resolution_clock::now();
		long rec_num = recursive_path(stoi(argv[1]), stoi(argv[2]));
		auto stop_1 = high_resolution_clock::now();
		long rec_duration = duration_cast<milliseconds>(stop_1 - start_1).count();

		auto start_2 = high_resolution_clock::now();
		long rec_back_num = recursive_path(stoi(argv[1]), stoi(argv[2]));
		auto stop_2 = high_resolution_clock::now();
		long rec_back_duration = duration_cast<milliseconds>(stop_2 - start_2).count();

		auto start_3 = high_resolution_clock::now();
		long dyn_num = dynamic_path(stoi(argv[1]), stoi(argv[2]));
		auto stop_3 = high_resolution_clock::now();
		long dyn_duration = duration_cast<milliseconds>(stop_3 - start_3).count();

		cout << "Recursive:              " << rec_num << "\t" << rec_duration << endl;
		cout << "Recursive Backtracking: " << rec_back_num << "\t" << rec_back_duration << endl;
		cout << "Dynamic Programming:    " << dyn_num << "\t" << dyn_duration << endl;
	}

	return 0;
}

/**
 * A method for solving the given maze using standard recursion.
 *
 * @param m The depth of the maze
 * @param n The goal column number
 */
long recursive_path(int m, int n)
{
	// If both values are 0, the goal has been reached
	if (m == 0 && n == 0)
		return 1;

	// Return the value of both smaller pyramids added together
	if (m > 0)
	{
		return (recursive_path(m - 1, n) + recursive_path(m - 1, n - 1));
	}

	return 0;
}

/**
 * A method for solving the given maze using recursive backtracking.
 *
 * @param m The depth of the maze
 * @param n The goal column number
 */
long recursive_backtracking_path(int m, int n)
{
	// If both values are 0, the goal has been reached
	if (m == 0 && n == 0)
		return 1;

	// Call itself with a smaller pyramid
	if (m > 0)
	{
		recursive_path(m - 1, n);	  // Check one arm first
		recursive_path(m - 1, n - 1); // ...then the other
	}

	return 0;
}

/**
 * A method for solving the given maze using dynamic programming.
 *
 * @param m The depth of the maze
 * @param n The goal column number
 */
long dynamic_path(int m, int n)
{
	// Declare and initialize the maze variables
	int r = m + 1;
	int c = (m * 2) + 1;
	long paths[r][c];

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			paths[i][j] = 0;
		}
	}

	// Set the goal variable equal to 1
	paths[m][n * 2] = 1;

	// Work through the array starting from the last row
	for (int i = r - 1; i >= 0; i--)
	{
		// ...And starting from the first relevant column in the pyramid
		// skipping every other space, like a checkboard
		for (int j = (c / 2) - i; j <= (c / 2) + i; j++)
		{
			// Add the value of the current space to the value of the two
			// spaces that could reach it. This will be that space's
			// number of paths to the goal.
			if (j > 0)
				paths[i - 1][j - 1] += paths[i][j];
			if (j < c - 1)
				paths[i - 1][j + 1] += paths[i][j];
		}
	}

	// Return the final number of paths, which will be stored at the
	// tip of the pyramid.
	return paths[0][c / 2];
}