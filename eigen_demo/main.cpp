#include <Eigen/Core>
#include <Eigen/Dense>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {
  /*
  std::cout << "hello world\n";
  {
    Eigen::Matrix<int, 100, 100> m;
    m.setZero();
    std::cout << "end\n";
  }
  */
 
  /*
  // Eigen::RowMajor
  std::array<std::array<double, 4>, 4> data{1, 2,  3,  4,  5,  6,  7,  8,
                                            9, 10, 11, 12, 13, 14, 15, 16};
  Eigen::Matrix<double, 4, 4> matrix44;
  matrix44.setZero();
  std::cout << matrix44.rows() << std::endl;
  matrix44 << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;
  std::cout << matrix44 << std::endl;
  std::cout << matrix44.row(0)[0] << " " << matrix44.row(0)[1] << std::endl;

  std::array<std::array<double, 4>, 4> data1;
  std::cout << std::endl;
  std::cout << matrix44.row(0) << std::endl;

  for (size_t i = 0; i < matrix44.rows(); ++i) {
    memcpy(data1[i].data(), matrix44.row(i).data(),
           sizeof(double) * matrix44.row(i).size());
  }

  std::for_each(data1.begin(), data1.end(), [](std::array<double, 4>& elem) {
    for (const auto& e : elem) { std::cout << e << " "; }
    std::cout << std::endl;
  });

  Eigen::Matrix<double, 6, 1> matri61;
  matri61 << 0, 1, 2, 3, 4, 5;
  std::array<double, 6> test;
  // test = matri61.data();
  memcpy(test.data(), matri61.data(), sizeof(double) * matri61.size());
  std::for_each(test.begin(), test.end(),
                [](double elem) { std::cout << elem << " "; });
*/
  /*
    Eigen::Matrix<double, Eigen::Dynamic, 1> matriN1;
    matriN1.resize(4, 1);
    matriN1 << 1, 2, 3, 4;
    std::vector<double> v;
    v.resize(matriN1.size());
    memcpy(v.data(), matriN1.data(), sizeof(double) * matriN1.size());
    std::for_each(v.begin(), v.end(), [](double e) { std::cout << e << " "; });
    std::cout << std::endl;

    Eigen::Matrix<double, Eigen::Dynamic, 2> matriN4;
    matriN1.resize(4, 2);
    matriN1 << 1, 2, 3, 4, 5, 6, 7, 8;
    std::vector<std::array<double, 2>> v1;
    v1.resize(matriN1.rows());

    memcpy(v.data(), matriN1.data(), sizeof(double) * matriN1.size());
    std::for_each(v.begin(), v.end(), [](double e) { std::cout << e << " "; });
    std::cout << std::endl;
  */

  Eigen::Matrix<double, 6, 1> joint(0);
}
