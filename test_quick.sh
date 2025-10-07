#!/bin/bash

# Simple test script for Cub3D
# Tests a selection of key error cases and valid maps

echo "🧪 Running Cub3D Parser Tests..."
echo

# Build first
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi

echo "✅ Build successful"
echo

# Test function
test_map() {
    local file="$1"
    local description="$2"
    local expected="$3"  # "PASS" or "FAIL"
    
    echo -n "Testing $description... "
    
    ./cub3D "$file" > /dev/null 2>&1
    result=$?
    
    if [ "$expected" = "PASS" ]; then
        if [ $result -eq 0 ]; then
            echo "✅ PASS"
        else
            echo "❌ FAIL (should have passed)"
        fi
    else
        if [ $result -ne 0 ]; then
            echo "✅ PASS (correctly rejected)"
        else
            echo "❌ FAIL (should have been rejected)"
        fi
    fi
}

echo "🔍 Testing invalid maps (should be rejected):"
test_map "maps/bad/no_extension.txt" "wrong file extension" "FAIL"
test_map "maps/bad/missing_ceiling.cub" "missing ceiling color" "FAIL"
test_map "maps/bad/empty_map.cub" "empty map" "FAIL"
test_map "maps/bad/no_player.cub" "no player" "FAIL"
test_map "maps/bad/multiple_players.cub" "multiple players" "FAIL"
test_map "maps/bad/not_closed_left.cub" "map not closed" "FAIL"
test_map "maps/bad/invalid_character.cub" "invalid character" "FAIL"
test_map "maps/bad/invalid_color_range.cub" "invalid color range" "FAIL"

echo
echo "✅ Testing valid maps (should be accepted):"
test_map "maps/good/simple_valid.cub" "simple valid map" "PASS"
test_map "maps/good/rectangular_map.cub" "rectangular map" "PASS"
test_map "maps/good/different_order.cub" "different element order" "PASS"
test_map "maps/good/with_internal_spaces.cub" "map with spaces" "PASS"

echo
echo "🏁 Test complete!"