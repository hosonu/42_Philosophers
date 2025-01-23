# Philosophers

This project is a solution to the classic dining philosophers problem, implemented in C using threads and mutexes.

## Overview

The dining philosophers problem is a classic computer science problem that illustrates synchronization issues and techniques for resolving them. The problem consists of N philosophers sitting around a circular table, where each philosopher needs two forks to eat. The challenge is to design a solution that avoids deadlock and ensures fair resource sharing.

## Features

- Simulates N philosophers dining at a circular table
- Each philosopher alternates between eating, thinking, and sleeping
- Uses threads to represent philosophers
- Implements mutex locks to handle fork access
- Monitors philosophers' states and detects death conditions
- Supports custom time settings for various actions
- Handles specified number of times each philosopher must eat

### Compilation

To compile the program, use the following command:

```bash
make
```

### Running the Program

To run the program, use the following command:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```
