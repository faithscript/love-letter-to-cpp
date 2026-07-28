#include <iostream>
#include <vector>
#include <variant>
#include <stdexcept>
#include <string>


enum class DoorStatus { Open, Closed };


struct Idle {
    DoorStatus door;
};

struct MovingUp {
    int destFloor;
};

struct MovingDown {
    int destFloor;
};

using ElevatorState = std::variant<Idle, MovingUp, MovingDown>;


enum class ElevatorStatus { Active, Maintenance, Removed };

struct ElevatorError : std::runtime_error {
    explicit ElevatorError(const std::string& msg) : std::runtime_error(msg) {}
};


class Elevator {
public:
    Elevator(int id, int startFloor)
        : id_(id), currentFloor_(startFloor),
          state_(Idle{DoorStatus::Closed}), status_(ElevatorStatus::Active) {}

    int id() const { return id_; }
    int currentFloor() const { return currentFloor_; }
    const ElevatorState& state() const { return state_; }
    ElevatorStatus status() const { return status_; }

    friend void openDoor(Elevator& e);
    friend void closeDoor(Elevator& e);
    friend void requestMove(Elevator& e, int destFloor, int buildingHeight);
    friend void arriveAtFloor(Elevator& e);
    friend void setStatus(Elevator& e, ElevatorStatus newStatus);

private:
    int id_;
    int currentFloor_;
    ElevatorState state_;
    ElevatorStatus status_;

 
    struct ArrivalVisitor {
        Elevator& e;

        void operator()(MovingUp& s) {
            e.currentFloor_ = s.destFloor;
            e.state_ = Idle{DoorStatus::Closed};
            std::cout << "Elevator " << e.id_ << ": arrived at floor " << e.currentFloor_ << "\n";
        }

        void operator()(MovingDown& s) {
            e.currentFloor_ = s.destFloor;
            e.state_ = Idle{DoorStatus::Closed};
            std::cout << "Elevator " << e.id_ << ": arrived at floor " << e.currentFloor_ << "\n";
        }

        void operator()(Idle&) {
            throw ElevatorError("arriveAtFloor called while not moving");
        }
    };
};


static void requireActive(const Elevator& e) {
    if (e.status() != ElevatorStatus::Active) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id()) + ": not active, cannot operate");
    }
}

void openDoor(Elevator& e) {
    requireActive(e);
    if (!std::holds_alternative<Idle>(e.state_)) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": cannot open door, not idle");
    }
    auto& idle = std::get<Idle>(e.state_);
    if (idle.door == DoorStatus::Open) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": door already open");
    }
    idle.door = DoorStatus::Open;
    std::cout << "Elevator " << e.id_ << ": door opened at floor " << e.currentFloor_ << "\n";
}

void closeDoor(Elevator& e) {
    requireActive(e);
    if (!std::holds_alternative<Idle>(e.state_)) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": cannot close door, not idle");
    }
    auto& idle = std::get<Idle>(e.state_);
    if (idle.door == DoorStatus::Closed) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": door already closed");
    }
    idle.door = DoorStatus::Closed;
    std::cout << "Elevator " << e.id_ << ": door closed at floor " << e.currentFloor_ << "\n";
}

void requestMove(Elevator& e, int destFloor, int buildingHeight) {
    requireActive(e);
    if (!std::holds_alternative<Idle>(e.state_)) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": cannot move, not idle");
    }
    const auto& idle = std::get<Idle>(e.state_);
    if (idle.door == DoorStatus::Open) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": cannot move, door open");
    }
    if (destFloor < 0 || destFloor >= buildingHeight) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": floor " + std::to_string(destFloor) +
            " out of range for building height " + std::to_string(buildingHeight));
    }
    if (destFloor == e.currentFloor_) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": already at floor " + std::to_string(destFloor));
    }

    if (destFloor > e.currentFloor_) {
        e.state_ = MovingUp{destFloor};
        std::cout << "Elevator " << e.id_ << ": moving up to floor " << destFloor << "\n";
    } else {
        e.state_ = MovingDown{destFloor};
        std::cout << "Elevator " << e.id_ << ": moving down to floor " << destFloor << "\n";
    }
}

void arriveAtFloor(Elevator& e) {
    requireActive(e);
    std::visit(Elevator::ArrivalVisitor{e}, e.state_);
}

void setStatus(Elevator& e, ElevatorStatus newStatus) {
    if (!std::holds_alternative<Idle>(e.state_)) {
        throw ElevatorError(
            "Elevator " + std::to_string(e.id_) + ": cannot change status mid-move");
    }
    e.status_ = newStatus;
    std::cout << "Elevator " << e.id_ << ": status changed\n";
}


class Building {
public:
    Building(int capacity, int height) : capacity_(capacity), height_(height) {}

    int height() const { return height_; }

    int addElevator(int startFloor) {
        if (static_cast<int>(elevators_.size()) >= capacity_) {
            throw ElevatorError("Building: at capacity, cannot add elevator");
        }
        if (startFloor < 0 || startFloor >= height_) {
            throw ElevatorError("Building: start floor out of range");
        }
        int id = static_cast<int>(elevators_.size()); 
        elevators_.emplace_back(id, startFloor);
        return id;
    }

    Elevator& get(int id) {
        if (id < 0 || id >= static_cast<int>(elevators_.size())) {
            throw ElevatorError("Building: invalid elevator id " + std::to_string(id));
        }
        return elevators_[id];
    }

private:
    int capacity_;
    int height_;
    std::vector<Elevator> elevators_;
};


int main() {
    Building building(2, 10); 
    int e0 = building.addElevator(0);

    requestMove(building.get(e0), 5, building.height());
    arriveAtFloor(building.get(e0));
    openDoor(building.get(e0));
    closeDoor(building.get(e0));

    try {
        openDoor(building.get(e0));
        openDoor(building.get(e0)); 
    } catch (const ElevatorError& ex) {
        std::cout << "Caught: " << ex.what() << "\n";
    }

    closeDoor(building.get(e0));

    try {
        requestMove(building.get(e0), 20, building.height()); 
    } catch (const ElevatorError& ex) {
        std::cout << "Caught: " << ex.what() << "\n";
    }

    try {
        setStatus(building.get(e0), ElevatorStatus::Maintenance);
        requestMove(building.get(e0), 8, building.height()); 
    } catch (const ElevatorError& ex) {
        std::cout << "Caught: " << ex.what() << "\n";
    }

    return 0;
}