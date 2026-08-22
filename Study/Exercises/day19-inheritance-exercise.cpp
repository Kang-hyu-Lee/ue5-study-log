// DAY 19 — C++: INHERITANCE — EXERCISES
// Type everything yourself. Predict output/behavior in a comment BEFORE running where asked.
// Reference: day19-inheritance-concept.md for syntax patterns.

#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------------------------------
// Q1 — Base/derived basics
// Create a base class `Vehicle` with:
//   protected: string Make, int TopSpeed
//   public: constructor taking both, and a function PrintInfo() that prints both fields
// Create a derived class `Car` : public Vehicle with:
//   private: int NumDoors
//   public: constructor that takes Make, TopSpeed, NumDoors (call the base constructor explicitly
//           in the initializer list — see concept file), and PrintCarInfo() that calls PrintInfo()
//           then prints NumDoors
//
// class Vehicle
// {
//     // TODO
// };
//
// class Car : public Vehicle
// {
//     // TODO
// };

class Vehicle
{
    protected:
    string Make;
    int TopSpeed;

    public:
    Vehicle(string m, int s) : Make(m), TopSpeed(s) {cout << "Vehicle constructed" << endl;}
    ~Vehicle() {cout << "Vehicle destroyed" << endl;}

    void PrintInfo(){
        cout << "Make: " << Make << " Top Speed: " << TopSpeed << endl;
    }

};

class Car :  public Vehicle
{
    private:
    int NumDoors;

    public:
    Car(string m, int s, int d) : Vehicle(m,s), NumDoors(d) {cout << "Car constructed" << endl;}
    ~Car(){ cout << "Car destroyed" << endl;}
    void PrintCarInfo(){
        PrintInfo();
        cout << "Number of Doors: " << NumDoors << endl;
    }
};


// -----------------------------------------------------------------
// Q2 — A second derived class from the SAME base
// Create `Motorcycle` : public Vehicle with:
//   private: bool HasSidecar
//   public: constructor + PrintMotorcycleInfo() (same pattern as Q1)
// This demonstrates ONE base, MULTIPLE independent derived classes — a common real hierarchy shape.
//
// class Motorcycle : public Vehicle
// {
//     // TODO
// };

class Motorcycle : public Vehicle
{
    private:
    bool HasSidecar;

    public:
    Motorcycle(string m, int s, bool b) : Vehicle(m, s), HasSidecar(b){cout << "Motorcycle constructed" << endl;}
    ~Motorcycle() {cout << "Motorcycle destroyed" << endl;}
    void PrintMotorcycleInfo()
    {
        PrintInfo();
        cout << "Has sidecar: " << HasSidecar << endl;
    }
};


// -----------------------------------------------------------------
// Q3 — Predict before running: protected access violation
// Uncomment the line below ONCE you've built Q1's Vehicle class. It will NOT compile.
// Write a one-line comment explaining WHY, referencing the access level involved.
//
// void BreakEncapsulation(Vehicle V) { cout << V.TopSpeed; }
// Your explanation: it is trying to access ToSpeed which is a protected field directly instead of using the internal functions or a getter(we don't have one at the moment)


// -----------------------------------------------------------------
// Q4 — Predict before running: object slicing
// Given this function (uses your Q1 Car class):
void DescribeVehicle(Vehicle& V)   // pass BY VALUE, not by reference — intentional
{
    V.PrintInfo();
}
// If you call DescribeVehicle(SomeCarObject), does NumDoors print anywhere? Why/why not?
// Your prediction: No by taking it by value, it will slice it down to the vehicle part because it only copies that portion
// Then fix DescribeVehicle so it would preserve full Car info if you wanted that
// (hint: change the parameter type — you already know the fix from the concept file).


// -----------------------------------------------------------------
// Q5 — Construction/destruction order, observed directly
// Add a print statement to the top of EVERY constructor and destructor you wrote in Q1/Q2
// (e.g. cout << "Vehicle constructed" << endl;).
// In main(), create one Car in a small nested scope { }, let it go out of scope, and observe
// the print order. Write the order you predict BEFORE running, then confirm.
// Your prediction: should print the constructed x then the info from each respective info printer function, then describe vehicle should correctly display for car but I'm not sure for the nested scope
//                  because we call PrintInfo(); the function itself won't print NumDoors because that's printed in the PrintCarInfo in the Car class


// -----------------------------------------------------------------
int main()
{
    // Q1 — construct a Car, call PrintCarInfo()
    Car car("KIA", 300, 4);
    car.PrintCarInfo();

    // Q2 — construct a Motorcycle, call PrintMotorcycleInfo()
    Motorcycle cycle("Harley Davidson", 200, false);
    cycle.PrintMotorcycleInfo();

    // Q4 — call DescribeVehicle() with your Car, observe/confirm your slicing prediction
    DescribeVehicle(car);

    // Q5 — nested scope construction/destruction order test
    {
        Car scopeCar("Tesla", 400, 4);
    }

    return 0;
}
