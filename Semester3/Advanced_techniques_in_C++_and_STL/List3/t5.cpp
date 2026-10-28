#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

double m1[50][50];
double m2[100][100];
double m3[200][200];
double res1[50][50];
double res2[100][100];
double res3[200][200];

void fill_randomly(int rows, int cols, double *m)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            m[i * cols + j] = 0.5 +
                (static_cast<double>(rand()) / RAND_MAX) * 1.5;
        }
    }
}

void square_matrix(int rows, int cols, double *m, double *res)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res[i * cols + j] = 0;
            for (int k = 0; k < cols; k++)
            {
                res[i * cols + j] += m[i * cols + k] * m[k * cols + j];
            }
        }
    }
}

double calculate_square_time(int n, int rows, int cols, double *m, double *res)
{
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        square_matrix(rows, cols, m, res);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - start;
    return time.count() / n;
}

void print_time(double avg_ms)
{
    int ms = static_cast<int>(avg_ms);       
    double mins = avg_ms / 60000.0;    
    cout << ms << " ms (";
    cout << fixed << setprecision(3);
    cout << mins << " minutes)" << '\n';
}

int main()
{
    srand(time(nullptr));
    fill_randomly(50, 50, &m1[0][0]);
    fill_randomly(100, 100, &m2[0][0]);
    fill_randomly(200, 200, &m3[0][0]);
    
    double time1, time2, time3;
    time1 = calculate_square_time(10000, 50, 50, &m1[0][0], &res1[0][0]);
    time2 = calculate_square_time(100, 100, 100, &m2[0][0], &res2[0][0]);
    time3 = calculate_square_time(100, 200, 200, &m3[0][0], &res3[0][0]);

    cout << "Time for 50x50 matrix: ";
    print_time(time1);
    cout << "Time for 100x100 matrix: ";
    print_time(time2);
    cout << "Time for 200x200 matrix: ";
    print_time(time3);
    return 0;
}