-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the description of the crime according to given date and street name.
SELECT description FROM crime_scene_reports
WHERE year = 2020 and month = 7 and day = 28 and street = 'Chamberlin Street'
-- Find out: three witnesses gave interview; crime time - 10:15am;

-- Find the interviews of witnesses
SELECT name, transcript FROM interviews
WHERE year = 2020 and month = 7 and day = 28 and transcript LIKE '%courthouse%'
-- Find out:
    -- thief was spotted in the car in the court house parking 10 minutes after crime;
    -- thief was spotted withdrawing money from ATM on Fifer Street earlier that morning;
    -- thiefs accomplice likely bought earliest ticket out of Fiftyville on next day;
    -- thief and accomplice had phone call for less than minute when thief was leaving court house.

-- Check security logs of court house parking 
SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25;
-- Find out license plates of possible thiefs 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, 
-- G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- Find out suspects names according to license plates
SELECT name FROM people
WHERE license_plate IN ('5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7',
'L93JTIZ', '322W7JE', '0NTHK55')
-- Find out: Patrick, Amber, Elizabeth, Roger, Danielle, Russell, Evelyn, Ernest.

-- Find who withdraw money from ATM on Fifer Street on the crime day
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and
day = 28 and atm_location = 'Fifer Street' and transaction_type LIKE '%withdraw%'))
-- Narrowed down list of suspects to: Elizabeth, Danielle, Russell, Ernest.

-- Find out information about call between thief and accomplice.
SELECT caller, receiver FROM phone_calls
WHERE year = 2020 and month = 7 and day = 28 and duration < 60 and
caller IN (SELECT phone_number FROM people WHERE name IN
('Elizabeth', 'Danielle', 'Russell', 'Ernest'))
-- There were 2 calls according to description:
    -- 1 - caller | receiver: (367) 555-5533 | (375) 555-8161;
    -- 2 - caller | receiver: (770) 555-1861 | (725) 555-3243.

-- Find out suspected thiefs by phone number.
SELECT name FROM people
WHERE phone_number IN ('(367) 555-5533', '(770) 555-1861')
-- Suspected thiefs Russell, Ernest

-- Find out suspected accomplices by phone number.
SELECT name FROM people
WHERE phone_number IN ('(375) 555-8161', '(725) 555-3243')
-- SUspected accomplices: Philip, Berthold.
-- Russell called Philip; Ernest called Berthold.

-- Check if possible acomplices called someone after talking to thief
SELECT * FROM phone_calls
WHERE caller IN ('(725) 555-3243')

-- Find out passport numbers of suspected thiefs
SELECT name, passport_number FROM people
WHERE name IN ('Russell', 'Ernest')
-- Russell - 3592750733, Ernest - 5773159633.

-- Check for flights of suspected thieves
SELECT * FROM passengers
WHERE passport_number IN (3592750733, 5773159633) and flight_id IN
(SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29)
-- Find out flights and seats of suspected thiefs: Russell - flight 18, seat 4C
-- Ernest - flight 36, seat 4A

-- Check what origin airport was
SELECT city FROM airports
WHERE id IN (SELECT origin_airport_id FROM flights WHERE year = 2020 and month = 7 and day = 29
and id IN (18, 36))
-- Find out that both flies were from Fiftyville on the 29th of July

-- Check flight information in order to find out time of departure
SELECT * FROM flights
WHERE id IN (18, 36)
-- THIEF is Ernest. His flight was in the morning, while other at 16pm.
-- Since Ernest talked only to one person after the crime, ACCOMPLICE is Berthold.

-- Find where thief went to
SELECT city FROM airports
WHERE id IN (SELECT destination_airport_id FROM flights WHERE id = 36)
-- Thief ESCAPED TO London
