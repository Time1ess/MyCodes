import sys
import random
import logging

from time import time, sleep
from uuid import uuid4
from collections import defaultdict


logging.basicConfig(
    stream=sys.stdout,
    level=logging.INFO)

TYPES = ['basic', 'small', 'medium', 'large']
LEAVE_PROB = 0.4
GENERATION_PROB = 0.5
CAR_GENERATION_NUM = 10
CAR_GENERATION_TYPES_WEIGHTS = [50, 10, 2]


class Car:
    def __init__(self, license):
        self.license = license
        self.acceptable_types()

    def __str__(self):
        return str(self.license)

    def __repr__(self):
        return '<{} {}>'.format(self.get_type(), self.license)

    def get_type(self):
        return str(type(self).__name__)

    def acceptable_types(self):
        raise NotImplementedError('Abstract class Car couldn\'t be '
                                  'instantiated')

    def get_license(self):
        return self.license


class SmallCar(Car):
    def acceptable_types(self):
        return ['small', 'basic', 'medium']


class MediumCar(Car):
    def acceptable_types(self):
        return ['medium', 'large']


class LargeCar(Car):
    def acceptable_types(self):
        return ['large']


class ParkingSpace:
    def get_type(self):
        return "basic"

    def park(self, car):
        self.start_time = time()

    def get_parking_time(self):
        return (time() - self.start_time) * 10  # For debug

    def get_price(self, car):
        """Get parking price based on used_time(minutes) * 0.1"""
        return self.get_parking_time() * 0.1


class SmallParkingSpace(ParkingSpace):
    def get_type(self):
        return "small"

    def get_price(self, car):
        return self.get_parking_time() * 0.15


class MediumParkingSpace(ParkingSpace):
    def get_type(self):
        return "medium"

    def get_price(self, car):
        return self.get_parking_time() * 0.2

class LargeParkingSpace(ParkingSpace):
    def get_type(self):
        return "large"

    def get_price(self, car):
        return self.get_parking_time() * 0.3


class ParkingLot:
    __SPACES = defaultdict(list)
    __AVAILABLE_SPACES = defaultdict(set)
    __CARS = {}

    def __init__(self, spaces):
        for sp in spaces:
            self.__SPACES[sp.get_type()].append(sp)
            self.__AVAILABLE_SPACES[sp.get_type()].add(sp)

    def park(self, car):
        for type in car.acceptable_types():  # Ordered
            if self.__AVAILABLE_SPACES[type]:
                sp = self.__AVAILABLE_SPACES[type].pop()
                sp.park(car)
                self.__CARS[car.get_license()] = sp
                logging.info("{!r} parked.".format(car))
                return True
        logging.info("No ParkingSpace for {!r}.".format(car))
        return False

    def charge(self, car, price):
        logging.info('Charge {!r} for {}'.format(car, price))

    def unpark(self, car):
        sp = self.__CARS[car.get_license()]
        price = sp.get_price(car)
        self.charge(car, price)
        self.__AVAILABLE_SPACES[sp.get_type()].add(sp)
        del self.__CARS[car.get_license()]
        logging.info("{!r} leaved.".format(car))

    def status(self):
        """Return available spaces of the whole parking lot."""
        cnts = defaultdict(int)
        for type, spaces in self.__AVAILABLE_SPACES.items():
            cnts[type] = len(spaces)
        return cnts


def main():
    spaces = [ParkingSpace() for _ in range(10)]
    spaces.extend(SmallParkingSpace() for _ in range(8))
    spaces.extend(MediumParkingSpace() for _ in range(6))
    spaces.extend(LargeParkingSpace() for _ in range(2))
    parking_lot = ParkingLot(spaces)
    cars = [SmallCar(uuid4()) for _ in range(6)]
    cars.extend(MediumCar(uuid4()) for _ in range(5))
    cars.extend(LargeCar(uuid4()) for _ in range(2))
    unparked_cars = set(cars)
    parked_cars = set()
    while True:
        # Leave
        processed_cars = set()
        for car in parked_cars:
            if random.random() < LEAVE_PROB:
                processed_cars.add(car)
                parking_lot.unpark(car)
        for car in processed_cars:
            parked_cars.remove(car)

        # Generate new cars
        types = random.choices(
            [SmallCar, MediumCar, LargeCar],
            weights=CAR_GENERATION_TYPES_WEIGHTS,
            k=CAR_GENERATION_NUM)
        for type in types:
            if random.random() < GENERATION_PROB:
                car = type(uuid4())
                logging.info('New Car {!r}'.format(car))
                unparked_cars.add(car)

        # Park cars
        processed_cars = set()
        for car in unparked_cars:
            if parking_lot.park(car):
                processed_cars.add(car)
        for car in processed_cars:
            unparked_cars.remove(car)
            parked_cars.add(car)

        logging.info('Parked cars: {}'.format(parked_cars))
        logging.info('Unparked cars: {}'.format(unparked_cars))
        logging.info(parking_lot.status())
        sleep(0.5)


if __name__ == '__main__':
    main()
