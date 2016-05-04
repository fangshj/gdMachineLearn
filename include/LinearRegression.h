#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class LinearRegression {
    public:
        LinearRegression();
        ~LinearRegression();
        void readParameters();
        void readData(const string dataFileName);
        void gradientDescent();
        double calMsv();
        void writeParas();
        void calTestFile();
        void setUnitsOfParas(const int& unitsOfParas);
        void setAlpha(const double& alpha);
        void setGdtimes(const int& gdtimes);
        void setParaFileName(const string fileName);
        void setParaOutFileName(const string fileName);
    private:
        int UNITS_OF_PARAMTERS;
        double ALPHA;
        int GDTIMES;
        string paraFileName;
        string paraOutFileName;
        vector<vector<double> > data;
        double parameters[1000];
};

#endif // LINEARREGRESSION_H
