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
        void DoOneEpoch();
        void Do100Epochs();

    private:
        vector<vector<int> > data;
        float coefficients[3];
        int bias;
};

int main() {
    PerceptronT perceptron;

    perceptron.InputData();
    perceptron.DoOneEpoch();

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
void PerceptronT::DoOneEpoch() {
    double sum;
    double sigmoid;
    bool prediction;

    for (int i = 0; i < data.size(); i++) {
        // calculate sum & sigmoid
        sum = data[i][0] * coefficients[0]
            + data[i][1] * coefficients[1]
            + float(bias) * coefficients[2];
        // cout << "sum = " << sum << endl;

        sigmoid = 1/(1 + pow(E, -sum));
        // cout << "sigmoid = " << sigmoid << endl;

        if (sigmoid < .5) {
            prediction = false;
        } else {
            prediction = true;
        }
        // cout << "prediction = " << prediction << endl;
        
        if (DEBUG_MODE) {
            cout << "data[i][2] = " << data[i][2] << endl;
        }

        // if (prediction == data[i][2]) {    
        //     cout << "prediction agrees with target" << endl;
        // } else {
        //     cout << "prediction disagrees with target" << endl;
        // }
    }

    return;
}

void PerceptronT::Do100Epochs() {
    // Output the mean accuracy over the last 100 epochs as well as the accuracy of the last epoch. Thus, there will be two accuracy measures output after the 100th epoch, again after the 200th epoch, and so on, ending in the two measures after the 1,000th epoch.

    for (int i = 0; i < 100; i++) {
        DoOneEpoch();
    }

    cout << "coefficients: ";
    for (int i = 0; i < 3; i++) {
        cout << coefficients[i];
        if (i < 2) {
            cout << ", ";
        }
    }
    cout << endl;

    return;
}