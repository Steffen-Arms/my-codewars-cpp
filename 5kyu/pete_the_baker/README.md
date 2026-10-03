# my-codewars-cpp

# kata: 
https://www.codewars.com/kata/525c65e51bf619685c000059

## Task
Given two unordered_maps. one for ingredients and one for recipes. Return the maximum amount how often you can apply this recipes for this ingredients.


## What I learned
use "const auto& [x,y]" if iterate maps. This way it dont get copy and you have direct access to key and value. Don't have to compute it twice.
use more std::min instead of <
use std::numeric_limits<int>::max() for a minimum search
