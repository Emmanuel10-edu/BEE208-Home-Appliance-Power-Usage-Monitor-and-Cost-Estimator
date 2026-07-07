# BEE208-Home-Appliance-Power-Usage-Monitor-and-Cost-Estimator

**BEE 208 – C++ Programming | Mid-Semester Practical Project | Project Question 25**
Accra Technical University | Faculty of Engineering | Department of Electrical/Electronic Engineering
Lecturer: Douglas Ayitey

---

## 1. What is this project? (explained simply)

Imagine every appliance in your house — the fridge, the TV, the iron,
the light bulbs — is secretly "eating" electricity all day long. Some
eat a little, some eat a LOT. This program is like a **smart notebook**
that:

1. Lets you write down every appliance you own.
2. Does the maths to figure out how much electricity each one eats
   every day and every month.
3. Tells you how much money (in Ghana Cedis) you will have to pay.
4. Warns you which appliances are "eating too much" so you can be
   careful with them.
5. Saves everything in a file so you never lose your notes.

## 2. Group Members

| # | Name | Index Number | Responsibility |
|---|------|---------------|-----------------|
| 1 | Kotei Emmanuel | 01243391B | Project lead |
| 2 | Debrah Nana Kwesi  | 01245351B  | Problem statement presenter |
| 3 | Klu Martin | 01243185B | Algorithm developer |
| 4 | Obodai Joseph | 01242609B | Pseudocode writer |
| 5 | Owiredu George Antwi | 01241871B | Flowchart designer |
| 6 | Emmanuel Akwesi Abbam Egyin | 01246167B | C++ programmer |
| 7 | Zogli Emmanuel Eli | 01243075B | Calculation and decision logic |
| 8 | Sebbe Kwame Elorm | 01243004B  | Testing and debugging |
| 9 | Fuseini Abdul Salim  | 01242729B | GitHub repository and README documentation manager |
| 10 | Afful Kofi Baah  | 01243598B  | Presentation and defence preparation |

*(Fill in your team's names and index numbers before submitting.)*

## 3. Problem Statement

Many homes use several appliances every day without keeping a proper
record of energy consumption. Without a simple monitoring tool, users
don't know which appliances consume the most energy or how much their
estimated monthly electricity bill will be. This project solves that
by recording appliance data, calculating usage, estimating cost, and
generating a clear report.

## 4. Aim

To develop a C++ Home Appliance Power Usage Monitor and Cost Estimator
that calculates appliance energy consumption and estimates the daily
and monthly electricity cost for a household.

## 5. Objectives

- Record multiple household appliances (ID, name, power rating, daily
  usage hours, quantity).
- Calculate daily and monthly energy consumption per appliance.
- Calculate total household daily and monthly energy consumption.
- Estimate monthly electricity cost using a user-defined tariff
  (GHS/kWh).
- Identify appliances with high energy consumption.
- Generate and save a clear text report.
- Demonstrate use of C++ classes, functions, loops, conditionals, and
  file handling.

## 6. Formulae Used (explained like you're 6)

Think of **watts** as "how hungry" an appliance is every second, and
**kilowatt-hours (kWh)** as "how many meals" it ate in total. The
electricity company charges you per "meal" (per kWh), not per second.

```
Daily Energy (kWh)   = (Power Rating in Watts × Hours per Day × Quantity) / 1000
Monthly Energy (kWh) = Daily Energy × 30
Monthly Cost (GHS)   = Monthly Energy × Tariff per kWh
```

**Why divide by 1000?** Because "kilo" means 1000. Power is measured
in watts, but we want *kilo*watt-hours, so we shrink the big watt
number down by dividing by 1000 — like turning 1000 grams into 1
kilogram.

**Why multiply by 30?** Because we're guessing a typical month has 30
days, so "one day's worth" of eating × 30 gives "one month's worth."

### Decision Rule (the "warning light")

| Condition | Decision |
|---|---|
| Monthly energy > threshold | ⚠️ High Consumption Appliance |
| Monthly energy ≤ threshold | ✅ Normal Consumption Appliance |
| Any negative value entered | ❌ Invalid input (rejected) |

This is just like a traffic light: if an appliance eats *more*
electricity than the line you drew (the threshold), the light turns
red and the program warns you.

## 7. C++ Concepts Used

- **cin / cout** – how the program talks to you and listens to your
  answers, like a conversation.
- **Variables and data types** (`string`, `double`, `int`) – labeled
  boxes that hold different kinds of information (words vs. numbers).
- **Operators** (`+`, `-`, `*`, `/`, `>`, `<`, `==`) – the tools used
  to do maths and comparisons.
- **if / else if / else** – "if this is true, do this, otherwise do
  that" — like choosing what to wear based on the weather.
- **Loops** (`while`, `for`) – doing the same job over and over
  without retyping it, like reading every name on a class list one by
  one.
- **Functions** – mini named "helpers" that do one job each (e.g.
  `calculateEnergyUsage()` only does the maths, nothing else).
- **Classes and objects** – a blueprint (`Appliance`) used to create
  many similar "boxes" of data, each holding its own ID, name, power,
  etc.
- **Vectors** – a growable list that holds as many appliances as you
  want, without needing to know the number in advance.
- **File handling** (`ifstream`, `ofstream`) – saving to and reading
  from files, like writing in — and later reading from — a notebook.
- **Search** – looking through the list to find one specific item by
  its name or ID.

## 8. How the Program Works (Menu Overview)

| Option | What it does |
|---|---|
| 1. Add Appliance | Asks questions and stores a new appliance |
| 2. View All Appliances | Shows every stored appliance in a table |
| 3. Search Appliance | Finds one appliance by ID or name |
| 4. Delete Appliance | Removes one appliance by ID |
| 5. View Report | Shows totals, cost, and high-consumption warnings on screen |
| 6. Save Report to File | Same as above, but also writes to `home_appliance_report.txt` |
| 7. Exit | Saves all data and closes the program |

## 9. Files in this Repository

```
BEE208-Home-Appliance-Power-Usage-Monitor-and-Cost-Estimator/
│
│-- main.cpp                     # the C++ source code
│-- README.md                    # this file
│-- algorithm.md                 # step-by-step algorithm
│-- pseudocode.md                # pseudocode of the program logic
│-- flowchart.png                # visual flowchart
│-- home_appliance_report.txt    # sample generated report
│-- screenshots/
│     │-- sample_input.png
│     │-- sample_output.png
```

## 10. How to Compile and Run

```bash
g++ -std=c++17 -Wall -o home_app main.cpp
./home_app
```

On Windows (with MinGW):
```bash
g++ -std=c++17 -Wall -o home_app.exe main.cpp
home_app.exe
```

## 11. Sample Test Case

Using tariff **GHS 1.50/kWh** and threshold **100 kWh/month**, adding
the 5 appliances from the project brief produces:

- Total Daily Energy: **6.10 kWh**
- Total Monthly Energy: **183.00 kWh**
- Estimated Monthly Cost: **GHS 274.50**
- High Consumption Appliance: **A001 – Refrigerator – 108.00 kWh/month**

This matches the expected sample output in the project question exactly. ✅

## 12. Testing Results

| Test Case | Input | Expected Result | Actual Result | Pass/Fail |
|---|---|---|---|---|
| Add valid appliance | Power=150W, Hours=24, Qty=1 | Daily=3.60 kWh | 3.60 kWh | ✅ Pass |
| Reject negative power | Power=-50 | "Value cannot be negative" | Rejected, re-asks | ✅ Pass |
| Reject hours > 24 | Hours=30 | "Hours must be between 0 and 24" | Rejected, re-asks | ✅ Pass |
| High-consumption flag | Monthly=108, Threshold=100 | Flagged as High Consumption | Flagged correctly | ✅ Pass |
| Search by ID | "A001" | Shows Refrigerator | Shown correctly | ✅ Pass |
| Delete appliance | "A002" | A002 removed from list | Removed correctly | ✅ Pass |
| Save report | Save option | File `home_appliance_report.txt` created | File created with correct totals | ✅ Pass |
| Reload saved data | Restart program | Previously saved appliances reappear | Reloaded correctly | ✅ Pass |

## 13. Challenges Faced and Solutions

- **Challenge:** Handling users typing letters where numbers were
  expected (e.g. typing "abc" for power rating) could crash the
  program.
  **Solution:** Used `cin.fail()` checks combined with `cin.clear()`
  and `cin.ignore()` to detect bad input and ask again, instead of
  letting the program crash.

- **Challenge:** Keeping appliance data between program runs.
  **Solution:** Added a simple CSV-style save/load system using
  `ofstream` and `ifstream` so data is remembered next time the
  program starts.

- **Challenge:** Deciding how to store many appliances without knowing
  in advance how many the user will add.
  **Solution:** Used a `vector<Appliance>` which grows automatically
  as new appliances are added.
