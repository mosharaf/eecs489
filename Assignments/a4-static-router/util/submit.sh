#!/bin/bash

# Define commonly ignored files and directories
IGNORED_FILES_AND_DIRS=(".git" ".vscode" ".idea" "build" "__pycache__" ".DS_Store" "*.pyc" "*.pyo" "submit.tar")

# Check if a file or directory should be ignored
should_ignore() {
  local file_name="$1"
  for pattern in "${IGNORED_FILES_AND_DIRS[@]}"; do
    if [[ $pattern == "*"* ]]; then
      # Match file extensions
      if [[ $file_name == $pattern ]]; then
        return 0
      fi
    else
      # Check for an exact match or if the file is in a directory that should be ignored
      if [[ "$file_name" == "$pattern" ]] || [[ "$file_name" == "$pattern/"* ]]; then
        return 0
      fi
    fi
  done
  return 1
}

# Create a tarball from the contents of base_dir, excluding ignored files and directories
create_tar() {
  local base_dir="$1"
  local output_file="$2"
  local current_dir

  current_dir=$(pwd)
  pushd "$base_dir" > /dev/null || exit 1

  # Find files and exclude ignored patterns
  find ./cpp -type f | while read -r file; do
    relative_path="${file#./}"
    if ! should_ignore "$relative_path"; then
      echo "$relative_path"
    fi
  done | tar -cf "$current_dir/$output_file" -T -

  popd > /dev/null || exit 1
}

# Main script
if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

base_dir="$1"
output_file="submit.tar"

if [[ ! -d $base_dir ]]; then
  echo "Error: $base_dir is not a valid directory."
  exit 1
fi

create_tar "$base_dir" "$output_file"
echo "Tarball created: $output_file"