# CUB3D Parser Test Suite

This directory contains comprehensive tests for the CUB3D map parser to validate that it correctly handles various valid and invalid map configurations according to the project requirements.

## Test Structure

### `/maps/good/` - Valid Maps (Should Pass)
- `simple_valid.cub` - Basic valid map with minimal requirements
- `rectangular_map.cub` - Rectangular shaped map
- `complex_with_spaces.cub` - Complex map with spaces and empty lines in config
- `different_order.cub` - Configuration elements in different order
- `with_internal_spaces.cub` - Map containing internal space characters
- `large_map.cub` - Large map to test performance
- `creepy.cub`, `subject_map.cub`, `test_map.cub`, `test_textures.cub` - Existing valid maps

### `/maps/bad/` - Invalid Maps (Should Fail)

#### File Extension & Basic Validation
- `no_extension.txt` - Wrong file extension
- `missing_ceiling.cub` - Missing required ceiling color (C)
- `duplicate_texture.cub` - Duplicate texture definition

#### Texture & Path Validation  
- `invalid_texture_path.cub` - Non-existent texture file
- `invalid_identifier.cub` - Invalid configuration identifier (XX instead of NO/SO/WE/EA)

#### Color Validation
- `invalid_color_range.cub` - Color value > 255
- `invalid_color_format.cub` - Missing color component (only R,G instead of R,G,B)
- `invalid_color_character.cub` - Letter in color value instead of number
- `negative_color.cub` - Negative color value

#### Map Content Validation
- `empty_map.cub` - No map provided
- `no_player.cub` - Map without player start position
- `multiple_players.cub` - Map with multiple player positions
- `invalid_character.cub` - Invalid character (X) in map
- `too_small_map.cub` - Map too small to be valid

#### Wall Boundary Validation
- `not_closed_left.cub` - Map not closed on left side
- `not_closed_right.cub` - Map not closed on right side  
- `not_closed_top.cub` - Map not closed on top
- `not_closed_bottom.cub` - Map not closed on bottom
- `hole_in_wall.cub` - Hole in boundary wall
- `space_in_boundary.cub` - Space character in boundary area

## Test Scripts

### `test_comprehensive.sh`
Complete test suite that runs all test cases with detailed output:
- Tests all invalid maps (should be rejected)
- Tests all valid maps (should be accepted)
- Tests different player orientations (N, S, E, W)
- Tests argument validation
- Provides colored output and detailed results

Usage:
```bash
./test_comprehensive.sh
```

### `test_quick.sh`
Quick test script for essential validation:
- Tests key error cases
- Tests basic valid maps
- Faster execution for development

Usage:
```bash
./test_quick.sh
```

## Requirements Tested

The test suite validates all requirements from the subject:

✅ **File Extension**: Must be `.cub`  
✅ **Map Characters**: Only `0`, `1`, `N`, `S`, `E`, `W` allowed  
✅ **Player Position**: Exactly one player start position required  
✅ **Wall Closure**: Map must be completely surrounded by walls  
✅ **Configuration Elements**: All 6 required (NO, SO, WE, EA, F, C)  
✅ **Element Order**: Elements can be in any order (except map last)  
✅ **Spaces**: Proper handling of spaces in configuration and map  
✅ **Color Format**: RGB values in range [0,255]  
✅ **Texture Paths**: Valid file paths for textures  
✅ **Error Handling**: Proper error messages for all invalid cases  

## Running the Tests

1. Make sure your project builds successfully:
   ```bash
   make
   ```

2. Run the comprehensive test suite:
   ```bash
   ./test_comprehensive.sh
   ```

3. Or run the quick test for development:
   ```bash
   ./test_quick.sh
   ```

## Expected Behavior

- **Valid maps**: Program should initialize successfully and display the 3D view
- **Invalid maps**: Program should exit with error code 1 and display "Error: [description]"

## Adding New Tests

To add new test cases:

1. Create new `.cub` files in appropriate directory (`good/` or `bad/`)
2. Add test calls to the test scripts
3. Ensure test descriptions clearly explain what is being tested

The test system helps ensure your parser correctly implements all the CUB3D requirements and handles edge cases properly.