#!/usr/bin/env python3
"""
Demo script for testing the Swarmic JSON to CSV converter.
This script demonstrates how to use the converter programmatically.
"""

from swarmic_json_to_csv import SwarmicJSONToCSVConverter
from pathlib import Path

def demo_conversion():
    """
    Demonstrate the conversion process with a sample file.
    """
    # Example usage - replace with your actual file path
    json_file = "swarmic_export_2025-11-27 (1).json"
    
    # Check if file exists
    if not Path(json_file).exists():
        print(f"⚠️  Please place your JSON export file in the current directory")
        print(f"   Expected file: {json_file}")
        return
    
    # Create output directory
    output_dir = "./csv_exports"
    
    print("🎯 Starting Swarmic JSON to CSV conversion demo")
    print("-" * 50)
    
    try:
        # Initialize converter
        converter = SwarmicJSONToCSVConverter(
            json_file_path=json_file,
            output_dir=output_dir
        )
        
        # Perform conversion
        exported_files = converter.export_to_csv()
        
        # Generate summary
        converter.generate_summary_report(exported_files)
        
        print("\n💡 Tips:")
        print("  • Open CSV files in Excel, Google Sheets, or any spreadsheet app")
        print("  • Use pandas to analyze: pd.read_csv('csv_exports/sleep_sessions.csv')")
        print("  • Import to databases using CSV import features")
        
    except Exception as e:
        print(f"❌ Error during conversion: {e}")

if __name__ == "__main__":
    demo_conversion()
