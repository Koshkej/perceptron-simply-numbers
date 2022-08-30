#define PERCEPTRONS_h
#ifdef PERCEPTRONS_h

#include <fstream>
#include <time.h>

namespace neuralnetwork {

	auto sigmoid = [](float element) {
		return 1 / (1 + pow(exp(1), -1 * element));
	};

	auto reverse_scala = [](float element) {
		return element * -1;
	};

	class perceptrons {

	private:

		float input_nodes, hide_nodes, out_nodes, learning_rate;
		matrix wih, who;

	public:

		matrix dataout;

		perceptrons(float inodes, float hidenodes, float onodes, float lr) {

			input_nodes = inodes;
			hide_nodes = hidenodes;
			out_nodes = onodes;

			learning_rate = lr;

			wih.set_dimension(hide_nodes, input_nodes);
			who.set_dimension(out_nodes, hide_nodes);

			srand(time(NULL));

			wih.randomize();
			who.randomize();

		}

		matrix query(matrix input) {

			matrix hidden = wih * input;
			hidden.do_something(sigmoid);

			matrix out = who * hidden;
			out.do_something(sigmoid);

			return out;

		}

		void train(matrix input, matrix targets) {

			matrix hidden = wih * input;
			hidden.do_something(sigmoid);

			matrix out = who * hidden;
			out.do_something(sigmoid);

			dataout = out;

			matrix errors_out = targets - out;
			matrix errors_hidden = who.T() * errors_out;

			who += errors_out * out.structure * (out - 1).do_something_create(reverse_scala).structure * hidden.T() * learning_rate;
			wih += errors_hidden * hidden.structure * (hidden - 1).do_something_create(reverse_scala).structure * input.T() * learning_rate;

		}

	};

	class csv {
	private:

		std::ifstream file;

	public:

		matrix input, targets;

		int sizeline;

		csv(std::string path, int lines) {

			file.open(path);
			sizeline = lines;

		}

		bool get() {

			matrix bufinput, buftargets;

			std::string line;

			if (!std::getline(file, line)) {
				return false;
			}

			for (int i = 0; i < line.size(); i++) {
				if (buftargets.structure.size() == 0) {
					std::string word; 
					word += line[0];
					for (int x = 0; x < 10; x++) {
						if (x == atoi(word.c_str())) {
							std::vector<float> bufline;
							bufline.push_back(0.99);
							buftargets.structure.push_back(bufline);
						}
						else {
							std::vector<float> bufline;
							bufline.push_back(0.01);
							buftargets.structure.push_back(bufline);
						}
					}
					line.erase(0, 2);
					i = -1;
					continue;
				} 
				if (line[i + 1] == ',' && i + 1 < line.size()) {
					std::vector<float> bufline;
					std::string word = line;
					word.erase(i + 1, line.size() - 1);
					bufline.push_back(atoi(word.c_str()) / 255.0 * 0.99 + 0.01);
					bufinput.structure.push_back(bufline);
					line.erase(0, i + 2);
					i = -1;
					continue;
				}
				else if (i + 1 == line.size()) {
					std::vector<float> bufline;
					bufline.push_back(atoi(line.c_str()) / 255.0 * 0.99 + 0.01);
					bufinput.structure.push_back(bufline);
					break;
				}
			}
			
			input = bufinput;
			targets = buftargets;

			return true;

		}

		void close() {
			file.close();
		}

	};

}
#endif // CLASEES_H