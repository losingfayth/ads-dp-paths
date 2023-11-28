/**
 * Declaration File for Paths
 * 
 * @author fayth quinn
*/

#ifndef PATHS_H_INCLUDED
#define PATHS_H_INCLUDED

class Paths {
	public:
		Paths(int m, int n);
		~Paths();
		void run();

		friend std::ostream& operator<<(std::ostream&, const Paths&);

	private:
		void init();
		void release();
		void rbSolve(int x, int y);
		void dpSolve();
		int** board;
		int rows;
		int cols;
		int goal;
		int rbPaths;
		int dpPaths;	
};

#endif