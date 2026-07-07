# Pseudocode — Home Appliance Power Usage Monitor and Cost Estimator

> **Pseudocode is like writing a recipe in half-English, half-code.**
> It's not a real programming language, it's just a clear way of
> planning what the code will do, before we actually type real C++.

```
BEGIN
    DISPLAY system title
    LOAD saved appliance records from file (if any)

    INPUT tariff
    INPUT highConsumptionThreshold

    DISPLAY menu

    WHILE user has not selected Exit DO

        IF user selects Add Appliance THEN
            INPUT applianceID, applianceName, powerRating, hoursPerDay, quantity

            IF powerRating < 0 OR hoursPerDay < 0 OR quantity < 0 THEN
                DISPLAY "Invalid input"
            ELSE
                dailyEnergy = (powerRating * hoursPerDay * quantity) / 1000
                monthlyEnergy = dailyEnergy * 30
                STORE appliance record in list
            END IF

        ELSE IF user selects View All Appliances THEN
            FOR EACH appliance IN list DO
                DISPLAY appliance details
            END FOR

        ELSE IF user selects Search Appliance THEN
            INPUT keyword (ID or Name)
            FOR EACH appliance IN list DO
                IF appliance.ID == keyword OR appliance.Name == keyword THEN
                    DISPLAY appliance details
                END IF
            END FOR

        ELSE IF user selects Delete Appliance THEN
            INPUT applianceID
            REMOVE matching appliance FROM list

        ELSE IF user selects View Report THEN
            totalDaily = SUM of all dailyEnergy in list
            totalMonthly = SUM of all monthlyEnergy in list
            totalCost = totalMonthly * tariff

            DISPLAY all appliance records
            DISPLAY totalDaily, totalMonthly, totalCost

            FOR EACH appliance IN list DO
                IF appliance.monthlyEnergy > highConsumptionThreshold THEN
                    DISPLAY appliance AS "High Consumption"
                END IF
            END FOR

        ELSE IF user selects Save Report THEN
            (same calculations as View Report)
            SAVE report TO home_appliance_report.txt
            SAVE appliance list TO data file

        ELSE IF user selects Exit THEN
            SAVE appliance list TO data file
            STOP LOOP
        END IF

    END WHILE

END
```

## Plain-English walkthrough

Think of the `WHILE` loop as a merry-go-round that keeps spinning and
showing the menu again and again. Every time the user picks a number
(1 to 7), the program jumps to that part of the "recipe" and does that
one job, then comes back around to show the menu again — until the
user picks **7 (Exit)**, which makes the merry-go-round stop.
