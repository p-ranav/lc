import argparse
import os


def get_file_size(size_in_units, unit):
    if unit == 'MB':
        file_size_in_bytes = size_in_units * 1024 * 1024
    elif unit == 'GB':
        file_size_in_bytes = size_in_units * 1024 * 1024 * 1024

    return file_size_in_bytes


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Make large files of arbitrary size to test lc')
    parser.add_argument('-s', '--size', help='size of file in Gigabytes', type=int, default=1)
    parser.add_argument('-m', '--megabytes', help='specify the size in Megabytes', action='store_true')
    args = parser.parse_args()

    if args.megabytes:
        unit = 'MB'
    else:
        unit = 'GB'

    size = get_file_size(args.size, unit)
    file_name = f'large_file_{args.size}{unit}'

    with open(file_name, 'wb') as fout:
        fout.write(os.urandom(size))
