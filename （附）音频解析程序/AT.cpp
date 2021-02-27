// AT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "plot.h"
using namespace std;

vector<int> ReadMp3() {
    ifstream fin("D://testmp3.mp3", ios::binary);
    vector<int> data;
    while (1) {
        char start[2] = { 0 };
        while (1) {
            start[0] = start[1];
            fin.read(&start[1], sizeof(char));
            if ((int)start[0] == 0xffffffff && (int)start[1] == 0xfffffffb) {
                break;
            }
            if (start[1] == NULL) break;
        }
        char frame[8338] = { 0 };
        int sum = 0;
        fin.read(frame, sizeof(char) * 8338);
        for (int i = 1; i < 8338; i++) {
            stringstream ss;
            ss << dec << (int)frame[i - 1];
            int temp = stoi(ss.str());
            if (temp < 0) {
                temp += 256;
            }
            sum += temp;
        }
        data.push_back(sum);
        //cout << sum << endl;
        if (sum == 0) break;
    }
    return data;
}

void WriteData(vector<int> data) {
    ofstream outfile;
    outfile.open("D:\\data.txt", ios::out);
    if (!outfile.is_open())
        cout << "Open file failure" << endl;
    for (int i = 0; i < data.size(); i++) {
        outfile << data[i] << endl;
    }
    outfile.close();
}

int main()
{
    WriteData(ReadMp3());
    //ReadMp3();
    cout << "done" << endl;
    system("pause");
    return 0;
}
