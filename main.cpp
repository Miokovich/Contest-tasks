#include <iostream>
#include <string>
#include <cmath>
#include <vector>

struct Student{
    int name_index;
    int middle = 0;
};

void Merge_(Student* a, const int &beg_a, const int &mid, const int &end_a) {
    int indexA = beg_a;
    int indexB = mid;
    int indexC = beg_a;
    std::vector<Student> result;
    result.reserve(end_a);
    while (indexA < mid && indexB <= end_a) {
        if (a[indexA].middle >= a[indexB].middle) {
            result.push_back(a[indexA]);
            ++indexC;
            ++indexA;
        }
        else {
            result.push_back(a[indexB]);
            ++indexC;
            ++indexB;
        }
    }
    while (indexA < mid) {
        result.push_back(a[indexA]);
        ++indexC;
        ++indexA;
    }
    while (indexB <= end_a) {
        result.push_back(a[indexB]);
        ++indexC;
        ++indexB;
    }
    for (int i = 0; i < indexC - beg_a; ++i){
        std::swap(a[beg_a + i], result[i]);
    }
}


void sort(Student* a, int l, int r){
    int mid = (l + r) / 2;
    if (l < mid) sort(a, l, mid);
    if (mid + 1  < r) sort(a, mid + 1, r);
    Merge_(a, l, mid + 1, r);

}


int main() {
    int n;
    double inf, rus, math;
    std::cin >> n;
    Student* a = new Student[n];
    std::vector<std::string> student_names;
    student_names.reserve(n);
    std::string temp_str_name, temp_str_surname;
    for (int i = 0; i < n; ++i){
        std::cin >> temp_str_name >> temp_str_surname;
        student_names.push_back(temp_str_name + " " + temp_str_surname);
        std::cin >> inf >> math >> rus;
        a[i].middle = inf + rus + math;
        a[i].name_index = i;
    }
    sort(a, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        std::cout << student_names[a[i].name_index] << '\n';
    }
    delete[]a;
    return 0;
}
