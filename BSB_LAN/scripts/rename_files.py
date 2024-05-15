import os

def rename_default_to_target(default_file, target_file):
    """Rename the default file to the target if the target doesn't exist."""
    if not os.path.isfile(target_file):
        if os.path.isfile(default_file):
            os.rename(default_file, target_file)
            print(f"Renamed '{default_file}' to '{target_file}'.")
        else:
            print(f"Error: '{default_file}' does not exist.")
    else:
        print(f"'{target_file}' already exists.")

# Print the current working directory for debugging purposes
current_path = os.getcwd()
print(f"Current working directory: {current_path}")

# List of default-to-target file pairs
file_pairs = [
    ("src/BSB-LAN/BSB_LAN_config.h.default", "BSB_LAN_config.h"),
    ("BSB_LAN_custom_defs.h.default", "BSB_LAN_custom_defs.h")
]

# Process each file pair
for default, target in file_pairs:
    rename_default_to_target(default, target)
