#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

echo -e "${BLUE}===============================================${NC}"
echo -e "${BLUE}       CUB3D MAP PARSER TEST SUITE           ${NC}"
echo -e "${BLUE}===============================================${NC}"
echo

# Function to run a single test
run_test() {
    local map_file="$1"
    local expected_result="$2"  # "pass" or "fail"
    local test_description="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${YELLOW}Test $TOTAL_TESTS: $test_description${NC}"
    echo -e "File: $map_file"
    
    # Run the program and capture output
    output=$(./cub3D "$map_file" 2>&1)
    exit_code=$?
    
    # Check if the result matches expectation
    if [ "$expected_result" = "pass" ]; then
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✅ PASSED${NC} - Map correctly accepted"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}❌ FAILED${NC} - Expected pass but got error:"
            echo -e "${RED}$output${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    else
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}✅ PASSED${NC} - Map correctly rejected:"
            echo -e "${GREEN}$output${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${RED}❌ FAILED${NC} - Expected error but map was accepted"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
    echo
}

# Build the project first
echo -e "${BLUE}Building project...${NC}"
make
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Build failed! Cannot run tests.${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Build successful${NC}"
echo

# Test argument validation
echo -e "${BLUE}=== ARGUMENT VALIDATION TESTS ===${NC}"
echo

run_test "" "fail" "No arguments provided"
run_test "maps/good/simple_valid.cub extra_arg" "fail" "Too many arguments"

# Test file extension validation
echo -e "${BLUE}=== FILE EXTENSION TESTS ===${NC}"
echo

run_test "maps/bad/no_extension.txt" "fail" "Wrong file extension (.txt instead of .cub)"
run_test "nonexistent_file.cub" "fail" "File does not exist"

# Test configuration element validation
echo -e "${BLUE}=== CONFIGURATION ELEMENT TESTS ===${NC}"
echo

run_test "maps/bad/missing_ceiling.cub" "fail" "Missing ceiling color (C)"
run_test "maps/bad/duplicate_texture.cub" "fail" "Duplicate texture definition (NO)"
run_test "maps/bad/invalid_texture_path.cub" "fail" "Invalid texture path (nonexistent file)"
run_test "maps/bad/invalid_color_range.cub" "fail" "Color value out of range (>255)"
run_test "maps/bad/invalid_color_format.cub" "fail" "Invalid color format (missing component)"
run_test "maps/bad/invalid_color_character.cub" "fail" "Invalid character in color (letter instead of number)"

# Test map validation
echo -e "${BLUE}=== MAP VALIDATION TESTS ===${NC}"
echo

run_test "maps/bad/empty_map.cub" "fail" "Empty map"
run_test "maps/bad/no_player.cub" "fail" "No player start position"
run_test "maps/bad/multiple_players.cub" "fail" "Multiple player start positions"
run_test "maps/bad/invalid_character.cub" "fail" "Invalid character in map (X)"

# Test wall validation
echo -e "${BLUE}=== WALL VALIDATION TESTS ===${NC}"
echo

run_test "maps/bad/not_closed_left.cub" "fail" "Map not closed on left side"
run_test "maps/bad/not_closed_right.cub" "fail" "Map not closed on right side"
run_test "maps/bad/not_closed_top.cub" "fail" "Map not closed on top"
run_test "maps/bad/not_closed_bottom.cub" "fail" "Map not closed on bottom"

# Test valid maps
echo -e "${BLUE}=== VALID MAP TESTS ===${NC}"
echo

run_test "maps/good/simple_valid.cub" "pass" "Simple valid map"
run_test "maps/good/rectangular_map.cub" "pass" "Rectangular map"
run_test "maps/good/different_order.cub" "pass" "Elements in different order"
run_test "maps/good/with_internal_spaces.cub" "pass" "Map with internal spaces"
run_test "maps/good/creepy.cub" "pass" "Existing creepy map"
run_test "maps/good/subject_map.cub" "pass" "Existing subject map"
run_test "maps/good/test_map.cub" "pass" "Existing test map"
run_test "maps/good/test_textures.cub" "pass" "Existing test textures map"

# Test different player orientations
echo -e "${BLUE}=== PLAYER ORIENTATION TESTS ===${NC}"
echo

# Create temporary test files for different player orientations
cat > /tmp/test_north.cub << EOF
NO ./sprites/N.png
SO ./sprites/S.png
WE ./sprites/W.png
EA ./sprites/E.png
F 220,100,0
C 225,30,0

11111
10N01
11111
EOF

cat > /tmp/test_south.cub << EOF
NO ./sprites/N.png
SO ./sprites/S.png
WE ./sprites/W.png
EA ./sprites/E.png
F 220,100,0
C 225,30,0

11111
10S01
11111
EOF

cat > /tmp/test_east.cub << EOF
NO ./sprites/N.png
SO ./sprites/S.png
WE ./sprites/W.png
EA ./sprites/E.png
F 220,100,0
C 225,30,0

11111
10E01
11111
EOF

cat > /tmp/test_west.cub << EOF
NO ./sprites/N.png
SO ./sprites/S.png
WE ./sprites/W.png
EA ./sprites/E.png
F 220,100,0
C 225,30,0

11111
10W01
11111
EOF

run_test "/tmp/test_north.cub" "pass" "Player facing North (N)"
run_test "/tmp/test_south.cub" "pass" "Player facing South (S)"
run_test "/tmp/test_east.cub" "pass" "Player facing East (E)"
run_test "/tmp/test_west.cub" "pass" "Player facing West (W)"

# Clean up temporary files
rm -f /tmp/test_north.cub /tmp/test_south.cub /tmp/test_east.cub /tmp/test_west.cub

# Final results
echo -e "${BLUE}===============================================${NC}"
echo -e "${BLUE}              TEST RESULTS                   ${NC}"
echo -e "${BLUE}===============================================${NC}"
echo -e "Total tests run: ${TOTAL_TESTS}"
echo -e "${GREEN}Passed: ${PASSED_TESTS}${NC}"
echo -e "${RED}Failed: ${FAILED_TESTS}${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed. Check the output above.${NC}"
    exit 1
fi