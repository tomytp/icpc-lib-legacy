import os
import yaml
from pathlib import Path
from typing import Dict, List, Set

def format_name(name: str) -> str:
    """Format a filename or directory name for display."""
    # Remove extension if present
    name = name.replace('.cpp', '')
    # Replace separators with spaces
    name = name.replace('-', ' ').replace('_', ' ')
    # Capitalize each word
    return ' '.join(word.capitalize() for word in name.split())

def get_existing_structure(yaml_path: Path) -> tuple[dict, dict]:
    """Read existing YAML file and return structure and a map of known files."""
    if not yaml_path.exists():
        return {}, {}
    
    try:
        with open(yaml_path) as f:
            structure = yaml.safe_load(f) or {}
    except:
        return {}, {}
    
    # Create a map of known files and their positions
    known_files = {}
    
    # Track root files
    if 'root_files' in structure:
        for file in structure['root_files']:
            known_files[file['path']] = ('root_files', len(known_files))
    
    # Track files in directories
    for dir_name, content in structure.items():
        if dir_name != 'root_files' and 'files' in content:
            for file in content['files']:
                known_files[file['path']] = (dir_name, len(known_files))
    
    return structure, known_files

def scan_directory(base_path: str, root_dir: str = 'src') -> tuple[list[tuple[str, str, str]], set[str]]:
    """
    Scan directory and return:
    - List of (directory, filename, full_path)
    - Set of all existing file paths for existence checking
    """
    root = Path(base_path) / root_dir
    files = []
    existing_files = set()
    
    for path in root.rglob('*.cpp'):
        rel_path = path.relative_to(root)
        if len(rel_path.parts) == 1:
            # Root file
            files.append(('root_files', str(rel_path), str(rel_path)))
            existing_files.add(str(rel_path))
        else:
            # File in subdirectory
            dir_name = rel_path.parts[0]
            files.append((dir_name, rel_path.name, str(rel_path)))
            existing_files.add(rel_path.name)
    
    return files, existing_files

def build_structure(
    files: list[tuple[str, str, str]], 
    known_files: dict,
    existing_files: set[str]
) -> dict:
    """Build directory structure maintaining existing order and removing non-existent files."""
    structure = {}
    
    # Sort files based on known positions, putting new files at the end
    def get_sort_key(file_info):
        dir_name, filename, full_path = file_info
        if dir_name == 'root_files':
            key_path = filename
        else:
            key_path = filename
        
        if key_path in known_files:
            return known_files[key_path][1]  # Use existing position
        return float('inf')  # New files go to the end
    
    sorted_files = sorted(files, key=get_sort_key)
    
    # Build new structure with only existing files
    for dir_name, filename, full_path in sorted_files:
        # Only add files that exist
        if dir_name == 'root_files':
            if filename in existing_files:
                if 'root_files' not in structure:
                    structure['root_files'] = []
                structure['root_files'].append({
                    'path': filename,
                    'name': format_name(filename)
                })
        else:
            if filename in existing_files:
                if dir_name not in structure:
                    structure[dir_name] = {
                        'name': format_name(dir_name),
                        'path': dir_name,
                        'files': []
                    }
                structure[dir_name]['files'].append({
                    'path': filename,
                    'name': format_name(filename)
                })
    
    # Remove empty directories
    structure = {k: v for k, v in structure.items() 
                if k == 'root_files' or 
                (v.get('files') and len(v['files']) > 0)}
    
    return structure

def main():
    # Get the directory where the script is located
    script_dir = Path(__file__).parent
    yaml_path = script_dir / 'structure.yaml'
    
    # Get existing structure and known files
    existing_structure, known_files = get_existing_structure(yaml_path)
    
    # Scan the src directory
    files, existing_files = scan_directory(script_dir)
    
    # Build new structure preserving order and removing non-existent files
    structure = build_structure(files, known_files, existing_files)
    
    # Write to structure.yaml
    with open(yaml_path, 'w') as f:
        yaml.dump(structure, f, sort_keys=False, default_flow_style=False)

if __name__ == '__main__':
    main()