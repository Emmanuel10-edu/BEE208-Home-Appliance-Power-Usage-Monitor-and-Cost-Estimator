# Algorithm — Home Appliance Power Usage Monitor and Cost Estimator

> **Imagine this like a recipe.** A recipe tells you the steps to bake a
> cake, in order, one at a time. An algorithm is the same idea, but for
> a computer program: it's the list of steps the program follows from
> start to finish.

## Step-by-Step Algorithm

1. **Start** the programme.
2. **Show the title** "Home Appliance Power Usage Monitor and Cost
   Estimator" on the screen, so the user knows what app they opened.
3. **Load saved data** (if any exists from before) — like opening your
   saved game instead of starting over.
4. **Ask the user** to type in:
   - the electricity **tariff** (price per kWh, in GHS)
   - the **high-consumption threshold** (the kWh/month line that means
     "this appliance uses too much power!")
5. **Show the menu** with 7 choices (Add, View, Search, Delete, View
   Report, Save Report, Exit).
6. **Repeat** (loop) the following until the user chooses Exit:
   - If the user chooses **Add Appliance**:
     a. Ask for ID, name, power rating, hours per day, and quantity.
     b. **Check** the numbers make sense (nothing negative, hours
        between 0 and 24). If something is wrong, say so and don't
        save it.
     c. **Calculate**:
        - Daily Energy = (Power × Hours × Quantity) ÷ 1000
        - Monthly Energy = Daily Energy × 30
     d. **Store** the appliance in the list.
   - If the user chooses **View All Appliances**: show every stored
     appliance in a neat table.
   - If the user chooses **Search**: ask for an ID or name, then look
     through the list and show a match if found.
   - If the user chooses **Delete**: ask for an ID, then remove that
     appliance from the list.
   - If the user chooses **View Report**: add up all the daily and
     monthly energy, work out the total cost, and check which
     appliances are above the threshold ("High Consumption"). Show it
     on screen.
   - If the user chooses **Save Report**: do the same as View Report,
     but also write it into `home_appliance_report.txt`, and save all
     appliance data to a file so it isn't lost.
   - If the user chooses **Exit**: save everything and stop the loop.
7. **End** the programme.

## Why each step matters (in really simple words)

- **Asking questions first** (tariff & threshold) is like asking "what
  are the rules of the game?" before you start playing.
- **Checking the numbers** stops silly mistakes, like an appliance
  that "uses -50 watts," which isn't possible in real life.
- **The maths step** turns raw numbers (watts, hours) into something
  useful: kilowatt-hours, which is what your electricity bill actually
  charges you for.
- **Saving to a file** is like writing your homework in a notebook
  instead of on a whiteboard — it doesn't disappear when you close the
  program.
