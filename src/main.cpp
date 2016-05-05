/*This codes are used to calculate the linear regression with improving algorithm
 *the improving point is Features and polynomial regression x + x^3
 *The description of the question is in the kaggle.com with NO sysu
 *Input: input of this codes is the train.csv
 *Output: output of this codes is the parametersX.txt, storing the parameters
 *        after times of gradient descent method
 *author:fangshj3
 *date:2016/03/29
 */
#include <iostream>
#include <string>
#include "../include/LinearRegression.h"

using namespace std;

int main()
{
    LinearRegression lr;

    lr.setParaFileName(string("../data/parameters17.txt"));
    lr.readParameters();
    lr.readData(string("../data/train.csv"));

    cout << lr.calMsv() << endl;
    return 0;
}
