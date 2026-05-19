#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class Complex {
private:
    double re;
    double im;

public:
    Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}
    Complex(const Complex& other) : re(other.re), im(other.im) {}
    ~Complex() {}

    Complex add(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }

    Complex subtract(const Complex& other) const {
        return Complex(re - other.re, im - other.im);
    }

    Complex multiply(const Complex& other) const {
        return Complex(re * other.re - im * other.im,
            re * other.im + im * other.re);
    }

    Complex divide(const Complex& other) const {
        double denom = other.re * other.re + other.im * other.im;
        if (denom == 0) {
            throw runtime_error("Division by zero");
        }
        return Complex((re * other.re + im * other.im) / denom,
            (im * other.re - re * other.im) / denom);
    }

    double modulus() const {
        return sqrt(re * re + im * im);
    }

    Complex power(int n) const {
        if (n < 0) {
            throw runtime_error("n must be non-negative");
        }
        if (n == 0) return Complex(1, 0);
        double r = modulus();
        double theta = atan2(im, re);
        double newR = pow(r, n);
        return Complex(newR * cos(n * theta), newR * sin(n * theta));
    }

    double getRe() const { return re; }
    double getIm() const { return im; }
    void setRe(double r) { re = r; }
    void setIm(double i) { im = i; }

    void print() const {
        cout << re;
        if (im >= 0) cout << " + " << im << "i";
        else cout << " - " << -im << "i";
    }

    Complex operator+(const Complex& other) const { return add(other); }
    Complex operator-(const Complex& other) const { return subtract(other); }
    Complex operator*(const Complex& other) const { return multiply(other); }
    Complex operator/(const Complex& other) const { return divide(other); }

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            re = other.re;
            im = other.im;
        }
        return *this;
    }
};

class ComplexArray {
private:
    Complex* data;
    int size;

public:
    ComplexArray(int s) : size(s) {
        if (s < 0) throw runtime_error("Negative size");
        data = new Complex[s];
    }

    ComplexArray(const ComplexArray& other) : size(other.size) {
        data = new Complex[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~ComplexArray() {
        delete[] data;
    }

    ComplexArray& operator=(const ComplexArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new Complex[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    int getSize() const { return size; }

    void set(int index, const Complex& value) {
        if (index < 0 || index >= size) {
            throw runtime_error("Index out of range");
        }
        data[index] = value;
    }

    Complex get(int index) const {
        if (index < 0 || index >= size) {
            throw runtime_error("Index out of range");
        }
        return data[index];
    }

    ComplexArray adjacentSumsModuli() const {
        if (size < 2) {
            throw runtime_error("Array must have at least 2 elements");
        }
        ComplexArray result(size - 1);
        for (int i = 0; i < size - 1; i++) {
            Complex sum = data[i] + data[i + 1];
            double mod = sum.modulus();
            result.set(i, Complex(mod, 0.0));
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            data[i].print();
            if (i < size - 1) cout << "; ";
        }
        cout << endl;
    }
};

int main() {
    system("chcp 65001 > nul");

    cout << "Complex Class" << endl;

    Complex z1(3, 4);
    Complex z2(1, 2);

    cout << "z1 = "; z1.print(); cout << endl;
    cout << "z2 = "; z2.print(); cout << endl;

    Complex sum = z1 + z2;
    cout << "Addition: "; sum.print(); cout << endl;

    Complex diff = z1 - z2;
    cout << "Subtraction: "; diff.print(); cout << endl;

    Complex prod = z1 * z2;
    cout << "Multiplication: "; prod.print(); cout << endl;

    Complex quot = z1 / z2;
    cout << "Division: "; quot.print(); cout << endl;

    cout << "Modulus of z1: " << z1.modulus() << endl;

    Complex z3(1, 1);
    Complex z3_pow3 = z3.power(3);
    cout << "(1+i)^3 = "; z3_pow3.print(); cout << endl;

    cout << endl;

    cout << "ComplexArray Class" << endl;

    ComplexArray A(4);
    A.set(0, Complex(1, 1));
    A.set(1, Complex(2, 2));
    A.set(2, Complex(3, 3));
    A.set(3, Complex(4, 4));

    cout << "Array A: "; A.print();

    ComplexArray C = A.adjacentSumsModuli();
    cout << "Array C: "; C.print();

    cout << endl;

    return 0;
}