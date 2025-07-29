#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test counters
GOOD_TESTS=0
BAD_TESTS=0
GOOD_PASSED=0
BAD_PASSED=0
SEGFAULTS=0

# Function to print header
print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}    CUB3D PARSER TESTING SCRIPT${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo
}

# Function to test a single map
test_map() {
    local map_file="$1"
    local expected_result="$2"  # "good" or "bad"
    local test_name=$(basename "$map_file")
    
    echo -n "Testing $test_name... "
    
    # Run the program and capture output and exit code
    local output
    local exit_code
    
    # Use timeout to prevent hanging and capture segfaults
    output=$(timeout 5s ./cub3D "$map_file" 2>&1)
    exit_code=$?
    
    # Check for segmentation fault
    if [ $exit_code -eq 139 ] || [ $exit_code -eq 11 ]; then
        echo -e "${RED}SEGFAULT${NC}"
        SEGFAULTS=$((SEGFAULTS + 1))
        return 1
    fi
    
    # Check for timeout
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}TIMEOUT${NC}"
        return 1
    fi
    
    # Check if output contains "Error:"
    if echo "$output" | grep -q "Error:"; then
        # Map produced an error
        if [ "$expected_result" = "bad" ]; then
            echo -e "${GREEN}PASS${NC}"
            if [ "$expected_result" = "bad" ]; then
                BAD_PASSED=$((BAD_PASSED + 1))
            fi
            return 0
        else
            echo -e "${RED}FAIL (should pass but failed)${NC}"
            return 1
        fi
    else
        # Map parsed successfully
        if [ "$expected_result" = "good" ]; then
            echo -e "${GREEN}PASS${NC}"
            if [ "$expected_result" = "good" ]; then
                GOOD_PASSED=$((GOOD_PASSED + 1))
            fi
            return 0
        else
            echo -e "${RED}FAIL (should fail but passed)${NC}"
            return 1
        fi
    fi
}

# Function to test good maps
test_good_maps() {
    echo -e "${YELLOW}Testing GOOD maps (should pass):${NC}"
    echo
    
    for map_file in maps/good/*.cub; do
        if [ -f "$map_file" ]; then
            test_map "$map_file" "good"
            GOOD_TESTS=$((GOOD_TESTS + 1))
        fi
    done
    
    echo
}

# Function to test bad maps
test_bad_maps() {
    echo -e "${YELLOW}Testing BAD maps (should fail):${NC}"
    echo
    
    for map_file in maps/bad/*.cub; do
        if [ -f "$map_file" ]; then
            test_map "$map_file" "bad"
            BAD_TESTS=$((BAD_TESTS + 1))
        fi
    done
    
    # Also test files without .cub extension
    for map_file in maps/bad/*; do
        if [ -f "$map_file" ] && [[ ! "$map_file" =~ \.cub$ ]]; then
            test_map "$map_file" "bad"
            BAD_TESTS=$((BAD_TESTS + 1))
        fi
    done
    
    echo
}

# Function to print summary
print_summary() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}              TEST SUMMARY${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo
    
    echo -e "Good maps: ${GREEN}$GOOD_PASSED/$GOOD_TESTS passed${NC}"
    echo -e "Bad maps:  ${GREEN}$BAD_PASSED/$BAD_TESTS passed${NC}"
    echo -e "Segfaults: ${RED}$SEGFAULTS${NC}"
    echo
    
    local total_tests=$((GOOD_TESTS + BAD_TESTS))
    local total_passed=$((GOOD_PASSED + BAD_PASSED))
    
    if [ $SEGFAULTS -eq 0 ] && [ $total_passed -eq $total_tests ]; then
        echo -e "${GREEN}🎉 ALL TESTS PASSED! 🎉${NC}"
        exit 0
    else
        echo -e "${RED}❌ SOME TESTS FAILED ❌${NC}"
        exit 1
    fi
}

# Main execution
main() {
    print_header
    
    # Check if cub3D executable exists
    if [ ! -f "./cub3D" ]; then
        echo -e "${RED}Error: cub3D executable not found. Run 'make' first.${NC}"
        exit 1
    fi
    
    # Check if maps directory exists
    if [ ! -d "./maps" ]; then
        echo -e "${RED}Error: maps directory not found.${NC}"
        exit 1
    fi
    
    # Run tests
    test_good_maps
    test_bad_maps
    print_summary
}

# Run main function
main "$@"