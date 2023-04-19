/*
    Lynx McCormick
    CSC385 Data Structures & Algorithms
    Perceptron

    machine learning
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const bool DEBUG_MODE = false;
const double E = 2.7182818284;

class PerceptronT {
    public:
        // function prototypes
        PerceptronT();
        void InputData();
        void ProcessData();

    private:
        vector<vector<int> > data;
        float coefficients[3];
        int bias;
};

int main() {
    PerceptronT perceptron;

    perceptron.InputData();
    perceptron.ProcessData();

    return 0;
}

// sets default values for perceptrons
PerceptronT::PerceptronT() {
    coefficients[0] = 0.58;
    coefficients[1] = -0.67;
    coefficients[2] = 0.17;
    bias = 1;

    return;
}

// get data from file
void PerceptronT::InputData() {
    ifstream inFile;
    string fileName;
    string line;
    vector<int> newVector;
    size_t position = 0;
    string substring;

    cout << "Enter a file name: ";
    cin >> fileName;
    cout << endl;
    inFile.open(fileName.c_str());
    getline(inFile, line);

    while (inFile) {
        while (position != string::npos) {
            position = line.find(" ");
            // get substring from beginning to next space
            substring = line.substr(0, position);
            // remove already-searched characters from line
            line = line.substr(position + 1);
            // convert to c string, then integer
            newVector.push_back(atoi(substring.c_str()));
        }
        
        data.push_back(newVector);
        newVector.clear();
        position = 0;
        getline(inFile, line);
    }

    inFile.close();
    return;
}

// does calculations and prints results
void PerceptronT::ProcessData() {
    double sum;
    double sigmoid;
    bool prediction;

    for (int i = 0; i < data.size(); i++) {
        // calculate sum & sigmoid
        sum = data[i][0] * coefficients[0]
            + data[i][1] * coefficients[1]
            + float(bias) * coefficients[2];
        cout << "sum = " << sum << endl;

        sigmoid = 1/(1 + pow(E, -sum));
        cout << "sigmoid = " << sigmoid << endl;

        if (sigmoid < .5) {
            prediction = false;
        } else {
            prediction = true;
        }
        cout << "prediction = " << prediction << endl;
        
        if (DEBUG_MODE) {
            cout << "data[i][2] = " << data[i][2] << endl;
        }
        if (prediction == data[i][2]) {
            
            cout << "prediction agrees with target" << endl;
        } else {
            cout << "prediction disagrees with target" << endl;
        }
    }

    return;
}
