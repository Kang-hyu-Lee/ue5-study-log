#!/bin/bash
# Run from the ROOT of your ue5-study-log repo (where Study/ lives).
# Uses plain mv (not git mv) so untracked files don't cause a hard failure.
# Missing files are reported, not fatal.

safe_mv() {
  if [ -f "$1" ]; then
    mv -v "$1" "$2"
  else
    echo "SKIP (not found): $1"
  fi
}

echo "== Concepts =="
cd Study/Concepts
safe_mv "arrays-indexing.md"                 "day08-arrays-indexing-concept.md"
safe_mv "arrays.md"                          "day04-arrays-concept.md"
safe_mv "big-o.md"                           "day09-big-o-concept.md"
safe_mv "conditionals-boolean-logic.md"      "day03-conditionals-boolean-logic-concept.md"
safe_mv "day01-algebra-basics.md"            "day01-algebra-basics-concept.md"
safe_mv "day01-cpp-intro-concept.md.md"      "day01-cpp-intro-concept.md"
safe_mv "day2-algorithms-bigO.md"            "day02-algorithms-bigo-concept.md"
safe_mv "day2-operators-casting.md"          "day02-operators-casting-concept.md"
safe_mv "dot-cross-product.md"               "day08-dot-cross-product-concept.md"
safe_mv "exponents-logarithms-trig.md"       "day03-exponents-logarithms-trig-concept.md"
safe_mv "functions.md"                       "day05-functions-concept.md"
safe_mv "geometry-trig-basics.md"            "day01-geometry-trig-basics-concept.md"
safe_mv "linked-list-insert-delete.md"       "day12-linked-list-insert-delete-concept.md"
safe_mv "linked-lists-intro.md"              "day11-linked-lists-intro-concept.md"
safe_mv "loops.md"                           "day04-loops-concept.md"
safe_mv "pointer-arithmetic.md"              "day11-pointer-arithmetic-concept.md"
safe_mv "pointers-intro.md"                  "day10-pointers-intro-concept.md"
safe_mv "references-vs-pointers.md"          "day12-references-vs-pointers-concept.md"
safe_mv "strings-io.md"                      "day09-strings-io-concept.md"
safe_mv "vectors-intro.md"                   "day05-vectors-intro-concept.md"
cd ../..

echo "== Exercises =="
cd Study/Exercises
safe_mv "algebra-basics-exercises.md"              "day01-algebra-basics-exercise.md"
safe_mv "arrays-indexing-exercises.cpp"             "day08-arrays-indexing-exercise.cpp"
safe_mv "arrays.cpp"                                "day04-arrays-exercise.cpp"
safe_mv "big-o-exercises.md"                        "day09-big-o-exercise.md"
safe_mv "conditionals-boolean-logic-exercises.cpp"  "day03-conditionals-boolean-logic-exercise.cpp"
safe_mv "cpp-intro-exercises.cpp"                   "day01-cpp-intro-exercise.cpp"
safe_mv "day2-algorithms-bigO.cpp"                  "day02-algorithms-bigo-exercise.cpp"
safe_mv "day2-operators-casting.cpp"                "day02-operators-casting-exercise.cpp"
safe_mv "dot-cross-product-exercises (1).md"        "day08-dot-cross-product-exercise.md"
safe_mv "exponents-logarithms-trig-exercises.md"    "day03-exponents-logarithms-trig-exercise.md"
safe_mv "functions-exercises.cpp"                   "day05-functions-exercise.cpp"
safe_mv "geometry-trig-basics-exercises.md"         "day01-geometry-trig-basics-exercise.md"
safe_mv "linked-list-insert-delete-exercises.cpp"   "day12-linked-list-insert-delete-exercise.cpp"
safe_mv "linked-lists-intro-exercises.cpp"          "day11-linked-lists-intro-starter.cpp"
safe_mv "linked-lists-intro-exercises.md"           "day11-linked-lists-intro-exercise.md"
safe_mv "loops.cpp"                                 "day04-loops-exercise.cpp"
safe_mv "pointer-arithmetic-exercises-extra.cpp"    "day11-pointer-arithmetic-extra-exercise.cpp"
safe_mv "pointer-arithmetic-exercises.cpp"          "day11-pointer-arithmetic-exercise.cpp"
safe_mv "pointers-intro-exercises.cpp"              "day10-pointers-intro-exercise.cpp"
safe_mv "references-vs-pointers-exercises.cpp"      "day12-references-vs-pointers-exercise.cpp"
safe_mv "strings-io-exercises.cpp"                  "day09-strings-io-exercise.cpp"
safe_mv "vectors-intro-exercises.md"                "day05-vectors-intro-exercise.md"

echo "-- removing stray compiled binaries (g++ build output, not source) --"
rm -fv arrays-indexing.exe arrays.exe cond-bool.exe cpp-exercise.exe \
       extra-pointer-exercises.exe functions.exe linked-list-exercises.exe \
       linked-list-insert-delete-exercises.exe loops.exe operators-casting-exercise.exe \
       pointer-exercises.exe pointers-intro.exe strings-io.exe
cd ../..

echo "== Solutions =="
cd Study/Solutions
safe_mv "algebra-basics-solutions.md"              "day01-algebra-basics-solution.md"
safe_mv "arrays-indexing.cpp"                       "day08-arrays-indexing-solution.cpp"
safe_mv "arrays.cpp"                                "day04-arrays-solution.cpp"
safe_mv "big-o-solutions.md"                        "day09-big-o-solution.md"
safe_mv "conditionals-boolean-logic-solutions.cpp"  "day03-conditionals-boolean-logic-solution.cpp"
safe_mv "cpp-intro-solutions.cpp"                   "day01-cpp-intro-solution.cpp"
safe_mv "day2-algorithmsbigO (1).cpp"               "day02-algorithms-bigo-solution.cpp"
safe_mv "day2-operators-casting (1).cpp"            "day02-operators-casting-solution.cpp"
safe_mv "dot-cross-product-solutions.md"            "day08-dot-cross-product-solution.md"
safe_mv "exponents-logarithms-trig-solutions.cpp"   "day03-exponents-logarithms-trig-solution.md"
safe_mv "functions-solutions.cpp"                   "day05-functions-solution.cpp"
safe_mv "geometry-trig-basics-solutions.md"         "day01-geometry-trig-basics-solution.md"
safe_mv "linked-list-insert-delete-solutions.cpp"   "day12-linked-list-insert-delete-solution.cpp"
safe_mv "loops.cpp"                                 "day04-loops-solution.cpp"
safe_mv "matrices-intro-solutions.md"               "day10-matrices-intro-solution.md"
safe_mv "pointer-arithmetic-solutions-extra.cpp"    "day11-pointer-arithmetic-extra-solution.cpp"
safe_mv "pointer-arithmetic-solutions.cpp"          "day11-pointer-arithmetic-solution.cpp"
safe_mv "pointers-intro-solutions.cpp"              "day10-pointers-intro-solution.cpp"
safe_mv "references-vs-pointers-solutions.cpp"      "day12-references-vs-pointers-solution.cpp"
safe_mv "strings-io-solutions.cpp"                  "day09-strings-io-solution.cpp"
safe_mv "vectors-intro-solutions.md"                "day05-vectors-intro-solution.md"
cd ../..

echo ""
echo "Done. Now run: git add -A && git status"
echo "(using -A instead of individual git add, since this is a bulk mechanical rename)"
