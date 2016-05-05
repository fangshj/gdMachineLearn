#include "../include/LinearRegression.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include <ctime>

using namespace std;

string getTime() {
    time_t rawtime = time(NULL);
    char *date = ctime(&rawtime);
    string timeNow(date);
    return timeNow;
}

LinearRegression::LinearRegression() {
    string timeNow = getTime();

    UNITS_OF_PARAMTERS = 769;
    ALPHA = 0.002;
    GDTIMES = 800;
    memset(parameters, 0, sizeof(double)*1000);
    paraFileName = "parameters13.txt";
    paraOutFileName = timeNow + "parametersNewest.txt";
}

LinearRegression::~LinearRegression() {
    cout << "Finish!" << endl;
}

void LinearRegression::readParameters() {
    ifstream fileParameters(paraFileName);
    if (!fileParameters.is_open())cout << endl << "Open parameters file ERROR" << endl;
    string str;
    double parameter;
    for(int i = 0; i < UNITS_OF_PARAMTERS; i++) {
        getline(fileParameters, str);
        stringstream strstr2(str);
        strstr2 >> parameter;
        parameters[i] = parameter;
    }
    fileParameters.close();
    cout << "Done reading parameters" << endl << endl;

}

void LinearRegression::readData(const string dataFileName) {
    ifstream fileTrain(dataFileName);
    if (!fileTrain.is_open())cout << endl << "Open train file ERROR" << endl;
    string strTemp;
    getline(fileTrain, strTemp);  // ignore the first line
    while (getline(fileTrain, strTemp)) {
        stringstream strstr(strTemp);
        string value;
        double valueDouble;
        vector<double> lineData;
        getline(strstr, value, ',');
        lineData.push_back(1.0);

        while(getline(strstr, value, ',')) {
            stringstream strstr1(value);
            strstr1 >> valueDouble;
            lineData.push_back(valueDouble);
            lineData.push_back(pow(valueDouble, 3));
        }

        // last line of the data is a result value which does not need to add a x^3 value, so delete it
        if (dataFileName == "train.csv")
            lineData.pop_back();

        data.push_back(lineData); // after finishing iteration, size of data is data[25000][386]
    }
    fileTrain.close();  // close the file
    cout << "Done reading data" << data.size() << endl << endl;

}

void LinearRegression::gradientDescent() {
     double msv = 0, msvUnit = 0;
     double tempParameters[1000] = {0};
     double valForIter[25000] = {0};
     double tempMsv = 0;

     for (int route = 0; route < GDTIMES; route++) {
         // calculate the Hj(Xi)-Yj to reuse
         for (int i = 0; i < data.size(); i++) {
                msvUnit = 0;
                for (int j = 0; j < UNITS_OF_PARAMTERS; j++) {
                     msvUnit += (data[i][j] * parameters[j]);
                }
                msvUnit -= data[i][UNITS_OF_PARAMTERS];
                valForIter[i] = msvUnit;
         }

         for (int k = 0; k < UNITS_OF_PARAMTERS; k++) {
             msv = 0;
             for (int i = 0; i < data.size(); i++) {
                msvUnit = valForIter[i] * data[i][k];
                msv += msvUnit;
            }
            tempParameters[k] = parameters[k] - (ALPHA * msv / data.size());
         }
        // replace all the parameters with new parameters
         for (int k = 0; k < UNITS_OF_PARAMTERS; k++) {
            parameters[k] = tempParameters[k];
         }
         // imply the process on terminal
         cout << "gradient descent process: " << (double)(route + 1) * 100 / GDTIMES << " %" << endl;
         if (route % 10 == 0) {
            double nowMsv = calMsv();
            cout << "======================= msv after " << route << " times is : " << nowMsv << " =========================" << endl;
            cout << "======================= msv decrease " << tempMsv - nowMsv << " compared with last time =========================" << endl;
            tempMsv = nowMsv;
         }
     }
}

double LinearRegression::calMsv() {
    if (data.empty()) {
        readParameters();
        readData(string("train.csv"));
    }
    double msv = 0, msvUnit = 0;
    for (int i = 0; i < data.size(); i++) {
        msvUnit = 0;
        for (int j = 0; j < UNITS_OF_PARAMTERS; j++) {
             msvUnit += (data[i][j] * parameters[j]);
        }
        msvUnit -= data[i][UNITS_OF_PARAMTERS];  // data[i][UNITS_OF_PARAMTERS]means reference of each line
        msvUnit = pow(msvUnit, 2);
        msv += msvUnit;
    }
    msv /= (2 * data.size());

    return msv;
}

void LinearRegression::writeParas() {
    /*output the final parameters into file "parameters.txt"*/
    ofstream outfile(paraOutFileName);
    if (!outfile.is_open())cout << endl << "Write parameters file ERROR" << endl;
    outfile << "The value of msv after " << GDTIMES << " times is : " << calMsv() << endl;
    for (int k = 0; k < UNITS_OF_PARAMTERS; k++) {
        outfile << parameters[k] << endl;
    }
    outfile.close();
    cout << "Done writing parameters" << endl << endl;
}

void LinearRegression::calTestFile() {
    if (data.empty()) {
        cout << "You haven't decide which data and parameters files to read!!!" << endl;
        return;
    }
    ofstream outfile("referenceOfTest.csv");
    if (!outfile.is_open())cout << endl << "Open referenceOfTest file ERROR" << endl;
    outfile << "Id,reference" << endl;
    double msvUnit = 0;
    for (int i = 0; i < data.size(); i++) {
        msvUnit = 0;
        for (int j = 0; j < UNITS_OF_PARAMTERS; j++) {
             msvUnit += (data[i][j] * parameters[j]);
        }
        outfile << i << ',' << msvUnit << endl;
    }
    outfile.close();
}

void LinearRegression::setUnitsOfParas(const int& unitsOfParas) {
    UNITS_OF_PARAMTERS = unitsOfParas;
}

void LinearRegression::setAlpha(const double& alpha) {
    ALPHA = alpha;
}

void LinearRegression::setGdtimes(const int& gdtimes) {
    GDTIMES = gdtimes;
}

void LinearRegression::setParaFileName(const string fileName) {
    paraFileName = fileName;
}

void LinearRegression::setParaOutFileName(const string fileName) {
    paraOutFileName = fileName;
}
