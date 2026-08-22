// DAY 19 — C++: INHERITANCE — SOLUTIONS

#include <iostream>
#include <string>
using namespace std;

// -----------------------------------------------------------------
// Q1
class Vehicle
{
public:
    Vehicle(string InMake, int InTopSpeed) : Make(InMake), TopSpeed(InTopSpeed)
    {
        cout << "Vehicle constructed" << endl;   // for Q5
    }
    ~Vehicle() { cout << "Vehicle destroyed" << endl; }  // for Q5

    void PrintInfo() { cout << Make << ", top speed " << TopSpeed << endl; }

protected:
    string Make;
    int TopSpeed;
};

class Car : public Vehicle
{
public:
    Car(string InMake, int InTopSpeed, int InNumDoors)
        : Vehicle(InMake, InTopSpeed), NumDoors(InNumDoors)   // base constructor called explicitly, FIRST
    {
        cout << "Car constructed" << endl;
    }
    ~Car() { cout << "Car destroyed" << endl; }

    void PrintCarInfo()
    {
        PrintInfo();                          // inherited, no Vehicle:: prefix needed
        cout << "Doors: " << NumDoors << endl;
    }

private:
    int NumDoors;
};

// -----------------------------------------------------------------
// Q2
class Motorcycle : public Vehicle
{
public:
    Motorcycle(string InMake, int InTopSpeed, bool InHasSidecar)
        : Vehicle(InMake, InTopSpeed), HasSidecar(InHasSidecar) {}

    void PrintMotorcycleInfo()
    {
        PrintInfo();
        cout << "Sidecar: " << (HasSidecar ? "yes" : "no") << endl;
    }

private:
    bool HasSidecar;
};

// -----------------------------------------------------------------
// Q3
// void BreakEncapsulation(Vehicle V) { cout << V.TopSpeed; }
// Explanation: TopSpeed is `protected`, not `public`. Protected members are accessible from
// INSIDE the class and from DERIVED classes only — never from free functions or code outside
// the class hierarchy, even if that code takes a Vehicle by value. `BreakEncapsulation` is not
// a member of Vehicle or any class derived from it, so this is exactly as illegal as if
// TopSpeed were private.

// -----------------------------------------------------------------
// Q4
void DescribeVehicle(Vehicle V)   // BY VALUE — copies only the Vehicle portion
{
    V.PrintInfo();
}
// Prediction/answer: NumDoors does NOT print, and cannot even be accessed inside this function —
// V's static type here is Vehicle, so the compiler only knows about Vehicle's members. The Car's
// NumDoors data is sliced off during the copy into the by-value parameter. No error, no warning —
// this is what makes slicing dangerous in real code.
//
// Fix — take by reference (or pointer) instead, which binds to the ORIGINAL object rather than
// copying a truncated slice of it:
void DescribeVehicleFixed(const Vehicle& V) { V.PrintInfo(); }
// This still only gives you Vehicle's interface (you can't call PrintCarInfo() through it without
// a cast), but at minimum no data is destroyed — the full Car object still exists in memory,
// untouched. Accessing the Car-only parts through a base reference is exactly the problem
// `virtual` functions (Day 22) and polymorphism solve.

// -----------------------------------------------------------------
// Q5
// Predicted/actual order for:
//   { Car C("Test", 120, 4); }
// Construction: "Vehicle constructed" -> "Car constructed"   (base always finishes first)
// Destruction:  "Car destroyed" -> "Vehicle destroyed"        (exact reverse — derived cleans up
//               its own stuff first, while the Vehicle part underneath it is still valid, THEN
//               Vehicle tears down what's left)

// -----------------------------------------------------------------
int main()
{
    Car MyCar("Toyota", 180, 4);
    MyCar.PrintCarInfo();

    Motorcycle MyBike("Harley", 200, false);
    MyBike.PrintMotorcycleInfo();

    DescribeVehicle(MyCar);        // prints Make/TopSpeed only — NumDoors is gone, silently

    cout << "--- entering scope ---" << endl;
    {
        Car ScopedCar("Honda", 150, 2);
    }
    cout << "--- scope exited ---" << endl;
    // Expected console output for the scoped block:
    // Vehicle constructed
    // Car constructed
    // Car destroyed
    // Vehicle destroyed

    return 0;
}
