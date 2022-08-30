#define MATRIX_h
#ifdef MATRIX_h

#include <vector>
#include <functional>
#include <math.h>

class matrix {
private:

	int dimension_x = NULL;
	int dimension_y = NULL;

public:

	std::vector<std::vector<float>> structure;

	///

	void set_dimension(int rows, int collum) {
		dimension_x = collum;
		dimension_y = rows;
		for (int y = 0; y < dimension_y; y++) {
			std::vector<float> matrix_buf;
			for (int x = 0; x < dimension_x; x++) {
				matrix_buf.push_back(0.0);
			}
			structure.push_back(std::vector<float>(matrix_buf));
		}
	}

	///

	matrix operator*(matrix matrix_duo) {

		matrix composition;

		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int collum = 0; collum < matrix_duo.structure[0].size(); collum++) {
				float point_part_buf = NULL;
				for (int point = 0; point < structure[0].size(); point++) {
					point_part_buf += structure[line][point] * matrix_duo.structure[point][collum];
				}
				part.push_back(point_part_buf);
			}
			composition.structure.push_back(part);
		}

		return composition;
	}

	///

	matrix operator*(std::vector<std::vector<float>> structure_duo) {

		matrix composition;

		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int point = 0; point < structure[line].size(); point++) {
				part.push_back(structure[line][point] * structure_duo[line][point]);
			}
			composition.structure.push_back(part);
		}

		return composition;
	}

	///

	matrix operator-(const matrix deductible) {

		matrix quotient;
		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int point = 0; point < structure[line].size(); point++) {
				part.push_back(structure[line][point] - deductible.structure[line][point]);
			}
			quotient.structure.push_back(part);
		}

		return quotient;
	}

	///

	matrix operator+(const matrix matrix_duo) {

		matrix sum;
		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int point = 0; point < structure[line].size(); point++) {
				part.push_back(structure[line][point] + matrix_duo.structure[line][point]);
			}
			sum.structure.push_back(part);
		}

		return sum;
	}

	///

	matrix T() {
		matrix transposing;
		for (int point = 0; point < structure[0].size(); point++) {
			std::vector<float> part;
			for (int line = 0; line < structure.size(); line++) {
				part.push_back(structure[line][point]);
			}
			transposing.structure.push_back(part);
		}
		return transposing;
	}

	///

	matrix operator*(float scala) {

		matrix composition;

		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int collum = 0; collum < structure[line].size(); collum++) {
				part.push_back(structure[line][collum] * scala);
			}
			composition.structure.push_back(part);
		}

		return composition;
	}

	///

	matrix operator+(float scala) {

		matrix composition;

		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int collum = 0; collum < structure[line].size(); collum++) {
				part.push_back(structure[line][collum] + scala);
			}
			composition.structure.push_back(part);
		}

		return composition;
	}

	///

	matrix operator-(float scala) {

		matrix composition;

		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int collum = 0; collum < structure[line].size(); collum++) {
				part.push_back(structure[line][collum] - scala);
			}
			composition.structure.push_back(part);
		}

		return composition;
	}

	///

	void operator*=(float scala) {
		for (int line = 0; line < structure.size(); line++) {
			for (int collum = 0; collum < structure[line].size(); collum++) {
				structure[line][collum] *= scala;
			}
		}
	}

	///

	void operator+=(float scala) {
		for (int line = 0; line < structure.size(); line++) {
			for (int collum = 0; collum < structure[line].size(); collum++) {
				structure[line][collum] += scala;
			}
		}
	}

	///

	void operator-=(float scala) {
		for (int line = 0; line < structure.size(); line++) {
			for (int collum = 0; collum < structure[line].size(); collum++) {
				structure[line][collum] -= scala;
			}
		}
	}

	///

	void operator+=(const matrix matrix_duo) {
		for (int line = 0; line < structure.size(); line++) {
			for (int point = 0; point < structure[line].size(); point++) {
				structure[line][point] += matrix_duo.structure[line][point];
			}
		}
	}

	///

	void operator*=(const matrix matrix_duo) {
		for (int line = 0; line < structure.size(); line++) {
			for (int collum = 0; collum < matrix_duo.structure[0].size(); collum++) {
				for (int point = 0; point < structure[0].size(); point++) {
					structure[line][point] *= matrix_duo.structure[point][collum];
				}
			}
		}
	}

	///

	void operator-=(const matrix matrix_duo) {
		for (int line = 0; line < structure.size(); line++) {
			for (int point = 0; point < structure[line].size(); point++) {
				structure[line][point] -= matrix_duo.structure[line][point];
			}
		}
	}

	///

	void do_something(std::function<float(float)> function) {
		for (int line = 0; line < structure.size(); line++) {
			for (int collum = 0; collum < structure[line].size(); collum++) {
				structure[line][collum] = function(structure[line][collum]);
			}
		}
	}

	///

	matrix do_something_create(std::function<float(float)> function) {
		matrix result;
		for (int line = 0; line < structure.size(); line++) {
			std::vector<float> part;
			for (int collum = 0; collum < structure[line].size(); collum++) {
				part.push_back(function(structure[line][collum]));
			}
			result.structure.push_back(part);
		}
		return result;
	}

	///

	void randomize(float MIN = -1, float MAX = 1) {

		for (int y = 0; y < dimension_y; y++) {
			std::vector<float> matrix_buf;
			for (int x = 0; x < dimension_x; x++) {
				matrix_buf.push_back(MIN + (rand() / (float)RAND_MAX) * (MAX - MIN));
			}
			structure.push_back(std::vector<float>(matrix_buf));
		}
	}

	///

	void consoling() {
		for (int i = 0; i < structure.size(); i++) {
			for (int u = 0; u < structure[i].size(); u++) {
				std::cout << structure[i][u] << " ";
			}
		}
	}

};

#endif // matrix_h