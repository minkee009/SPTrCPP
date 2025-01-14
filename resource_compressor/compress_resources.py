# -*- coding: utf-8 -*-

import os
import zipfile
import argparse

def compress_resources(resource_folder, output_file):
    with zipfile.ZipFile(output_file, 'w') as zipf:
        for root, _, files in os.walk(resource_folder):
            for file in files:
                full_path = os.path.join(root, file)
                relative_path = os.path.relpath(full_path, resource_folder)
                zipf.write(full_path, relative_path)
                print(f"Compressing: {relative_path}")

def main():
    parser = argparse.ArgumentParser(description='Compress resources into a zip file')
    parser.add_argument('--input', '-i', default='resources', help='Input resource folder')
    parser.add_argument('--output', '-o', default='resources.dat', help='Output zip file')
    args = parser.parse_args()
    
    try:
        compress_resources(args.input, args.output)
        print(f"Successfully created {args.output}")
    except Exception as e:
        print(f"Error: {e}")
        input("Press Enter to exit...")

if __name__ == '__main__':
    main()