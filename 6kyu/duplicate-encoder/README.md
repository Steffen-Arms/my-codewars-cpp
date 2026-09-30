# my-codewars-cpp

# kata: Duplicate Encoder: 
https://www.codewars.com/kata/54b42f9314d9229fd6000d9c

## Task
For a given string create a new string with the symblos ")" and "(". For each character in the old string that only appear once use "(" otherwise use ")".


## What I learned
use map for frequency counting if the key range is big.
for char its only 256 possible characters so a std::array is even better for access the counting
in c++23 use flat_map for sorted keys as loop up are faster than in std::map
