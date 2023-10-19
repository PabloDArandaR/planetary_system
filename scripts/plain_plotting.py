import matplotlib.pyplot as plt
import json
import logging

metadata_filename = "metadata.json"

def load_metadata() -> dict:
    try:
        with open(metadata_filename, "r") as f:
            meta = json.load(f)
            return meta
    except FileNotFoundError:
        logging.error("Metadata file not found")

def main():
    meta = load_metadata()

if __name__ == "__main__":
    main()