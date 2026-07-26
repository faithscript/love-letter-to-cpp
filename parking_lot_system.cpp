#include <iostream>
#include <stdexcept> 
#include <unordered_map>
class ParkingLot
{
public:
    ParkingLot(int cap)
    {
        if(0 >= cap){
            throw std::length_error("ParkingLot(int cap)");
        }
        capacity = cap;
    }

    void park(std::string plate)
    {
        if(parked.size() == capacity){
            throw std::out_of_range("park(std::string plate)");
        }
        if(!parked.count(plate)){
            parked[plate] = true;
        }else{
            throw std::invalid_argument("park(std::string plate)");
        } 
    }

    void leave(std::string plate)
    {   
        if(!parked.count(plate)){
            throw std::invalid_argument("leave(std::string plate)");
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
        if(!parked.count(plate)){
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
    // 1. Fresh lot
    ParkingLot lot(3);
    std::cout << "capacity 3, expect available=3: " << lot.spots_available() << '\n';
    std::cout << "expect is_full=false: " << std::boolalpha << lot.is_full() << '\n';

    // 2. Park one car
    lot.park("AAA111");
    std::cout << "after 1 park, expect available=2: " << lot.spots_available() << '\n';
    std::cout << "expect is_parked(AAA111)=true: " << lot.is_parked("AAA111") << '\n';
    std::cout << "expect is_parked(ZZZ999)=false: " << lot.is_parked("ZZZ999") << '\n';

    // 3. Park up to capacity
    lot.park("BBB222");
    lot.park("CCC333");
    std::cout << "after 3 parks, expect available=0: " << lot.spots_available() << '\n';
    std::cout << "expect is_full=true: " << lot.is_full() << '\n';

    // 4. Leave a car
    lot.leave("BBB222");
    std::cout << "after 1 leave, expect available=1: " << lot.spots_available() << '\n';
    std::cout << "expect is_parked(BBB222)=false: " << lot.is_parked("BBB222") << '\n';
    std::cout << "expect is_full=false: " << lot.is_full() << '\n';

    // 5. Re-park in the freed spot
    lot.park("DDD444");
    std::cout << "after re-park, expect available=0: " << lot.spots_available() << '\n';
    std::cout << "expect is_full=true: " << lot.is_full() << '\n';

    // 6. Fresh empty lot, immediate query
    ParkingLot empty_lot(1);
    std::cout << "capacity 1 lot, expect is_parked(anything)=false: "
              << empty_lot.is_parked("NOPE") << '\n';
}

void run_exception_tests()
{
    // 1. Invalid capacity
    try {
        ParkingLot bad_lot(-5);
        std::cout << "FAILED: expected exception for negative capacity\n";
    }
    catch (const std::length_error& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    try {
        ParkingLot zero_lot(0);
        std::cout << "FAILED: expected exception for zero capacity\n";
    }
    catch (const std::length_error& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    // 2. Parking when full
    ParkingLot lot(1);
    lot.park("AAA111");
    try {
        lot.park("BBB222");   // lot only has 1 spot, already taken
        std::cout << "FAILED: expected exception for full lot\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    // 3. Double-parking the same plate
    ParkingLot lot2(3);
    lot2.park("CCC333");
    try {
        lot2.park("CCC333");   // already parked
        std::cout << "FAILED: expected exception for duplicate plate\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    // 4. Leaving a plate that was never parked
    ParkingLot lot3(3);
    try {
        lot3.leave("ZZZ999");   // never parked
        std::cout << "FAILED: expected exception for unknown plate\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }

    // 5. Leaving a plate twice
    ParkingLot lot4(3);
    lot4.park("DDD444");
    lot4.leave("DDD444");
    try {
        lot4.leave("DDD444");   // already left
        std::cout << "FAILED: expected exception for double-leave\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
}

int main()
{
    run_exception_tests();
}