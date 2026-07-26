#include <iostream>
#include <exception>
#include <unordered_map>
#include <stdexcept>

class LotFullError : public std::exception
{
public:
    LotFullError(std::string msg) : msg{std::move(msg)} {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

class InvalidCapacityError : public std::exception
{
public:
    InvalidCapacityError(std::string msg) : msg{std::move(msg)} {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

class PlateParkedError : public std::exception
{
public:
    PlateParkedError(std::string msg) : msg{std::move(msg)} {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

class PlateNotParkedError : public std::exception
{
public:
    PlateNotParkedError(std::string msg) : msg{std::move(msg)} {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

class ParkingLot
{
public:
    ParkingLot(int cap)
    {
        if (0 >= cap) {
            throw InvalidCapacityError{"InvalidCapacityError @ ParkingLot(int cap)"};
        }
        capacity = cap;
    }

    void park(std::string plate)
    {
        if (parked.size() == capacity) {
            throw LotFullError{"LotFullError @ park(std::string plate)"};
        }
        if (!parked.count(plate)) {
            parked[plate] = true;
        } else {
            throw PlateParkedError{"PlateParkedError @ park(std::string plate)"};
        }
    }

    void leave(std::string plate)
    {
        if (!parked.count(plate)) {
            throw PlateNotParkedError{"PlateNotParkedError @ leave(std::string plate)"};
        }
        parked.erase(plate);
    }

    bool is_full() const
    {
        return int(parked.size()) == capacity;
    }

    int spots_available() const
    {
        return capacity - int(parked.size());
    }

    bool is_parked(std::string plate) const
    {
        if (!parked.count(plate)) {
            return false;
        }
        return true;
    }

private:
    int capacity;
    std::unordered_map<std::string, bool> parked;
};

void run_valid_tests()
{
    ParkingLot lot(3);
    std::cout << "capacity 3, expect available=3: " << lot.spots_available() << '\n';
    std::cout << "expect is_full=false: " << std::boolalpha << lot.is_full() << '\n';

    lot.park("AAA111");
    std::cout << "after 1 park, expect available=2: " << lot.spots_available() << '\n';
    std::cout << "expect is_parked(AAA111)=true: " << lot.is_parked("AAA111") << '\n';
    std::cout << "expect is_parked(ZZZ999)=false: " << lot.is_parked("ZZZ999") << '\n';

    lot.park("BBB222");
    lot.park("CCC333");
    std::cout << "after 3 parks, expect available=0: " << lot.spots_available() << '\n';
    std::cout << "expect is_full=true: " << lot.is_full() << '\n';

    lot.leave("BBB222");
    std::cout << "after 1 leave, expect available=1: " << lot.spots_available() << '\n';
    std::cout << "expect is_parked(BBB222)=false: " << lot.is_parked("BBB222") << '\n';
    std::cout << "expect is_full=false: " << lot.is_full() << '\n';

    lot.park("DDD444");
    std::cout << "after re-park, expect available=0: " << lot.spots_available() << '\n';
    std::cout << "expect is_full=true: " << lot.is_full() << '\n';

    ParkingLot empty_lot(1);
    std::cout << "capacity 1 lot, expect is_parked(anything)=false: "
              << empty_lot.is_parked("NOPE") << '\n';
}

void run_exception_tests()
{
    try {
        ParkingLot bad_lot(-5);
        std::cout << "FAILED: expected exception for negative capacity\n";
    }
    catch (const InvalidCapacityError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    try {
        ParkingLot zero_lot(0);
        std::cout << "FAILED: expected exception for zero capacity\n";
    }
    catch (const InvalidCapacityError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    ParkingLot lot(1);
    lot.park("AAA111");
    try {
        lot.park("BBB222");
        std::cout << "FAILED: expected exception for full lot\n";
    }
    catch (const LotFullError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    ParkingLot lot2(3);
    lot2.park("CCC333");
    try {
        lot2.park("CCC333");
        std::cout << "FAILED: expected exception for duplicate plate\n";
    }
    catch (const PlateParkedError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    ParkingLot lot3(3);
    try {
        lot3.leave("ZZZ999");
        std::cout << "FAILED: expected exception for unknown plate\n";
    }
    catch (const PlateNotParkedError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    ParkingLot lot4(3);
    lot4.park("DDD444");
    lot4.leave("DDD444");
    try {
        lot4.leave("DDD444");
        std::cout << "FAILED: expected exception for double-leave\n";
    }
    catch (const PlateNotParkedError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
}

int main()
{
    run_valid_tests();
    run_exception_tests();
}