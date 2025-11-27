#!/usr/bin/env python3
"""
Swarmic Data Export JSON to CSV Converter

This script converts a Swarmic JSON export file into separate CSV files for each data category.
Each category (sleep, calories, exercise, bodyweight, finance, net worth) gets its own CSV file.

Author: Pi Ko (pi.ko@nyu.edu)
Created: October 24, 2025
Version: v1.1

Changelog:
    v1.1 - 27 November 2025
        - Fixed JSON structure normalization to handle new export format with success wrapper
        - Added support for nested data structure (success → data → data)
        - Maintains backward compatibility with older flat JSON exports
    
    v1.0 - 24 October 2025
        - Initial release with basic JSON to CSV conversion

Requirements:
    - pandas
    - tqdm

Usage:
    python swarmic_json_to_csv.py <json_file_path> [output_directory]

Example:
    python swarmic_json_to_csv.py swarmic_export_2025-10-24.json ./csv_exports
"""

import json
import pandas as pd
import argparse
import sys
from pathlib import Path
from datetime import datetime
from typing import Dict, Any, Optional, List
from tqdm import tqdm
import warnings

# Suppress pandas future warnings for cleaner output
warnings.filterwarnings('ignore', category=FutureWarning)


class SwarmicJSONToCSVConverter:
    """
    Converter class for transforming Swarmic JSON export data into CSV files.

    This class handles the parsing of the JSON export file and creates individual
    CSV files for each data category with proper formatting and data types.
    """

    def __init__(self, json_file_path: str, output_dir: Optional[str] = None):
        """
        Initialize the converter with input file and output directory.

        Args:
            json_file_path (str): Path to the Swarmic JSON export file
            output_dir (Optional[str]): Directory to save CSV files. If None, uses same directory as JSON file
        """
        self.json_file_path = Path(json_file_path)

        # Validate input file exists
        if not self.json_file_path.exists():
            raise FileNotFoundError(f"JSON file not found: {json_file_path}")

        # Set output directory
        if output_dir:
            self.output_dir = Path(output_dir)
        else:
            self.output_dir = self.json_file_path.parent

        # Create output directory if it doesn't exist
        self.output_dir.mkdir(parents=True, exist_ok=True)

        # Load JSON data
        self.data = self._load_json()

        # Define export configurations for each data type
        self.export_configs = {
            'sleep_sessions': {
                'filename': 'sleep_sessions.csv',
                'date_columns': ['session_date', 'sleep_time', 'wake_time', 'created_at', 'updated_at'],
                'description': 'Sleep tracking sessions with bedtime and wake times'
            },
            'calories_entries': {
                'filename': 'calories_entries.csv',
                'date_columns': ['log_date', 'logged_at', 'created_at'],
                'description': 'Calorie intake log entries'
            },
            'exercise_sessions': {
                'filename': 'exercise_sessions.csv',
                'date_columns': ['session_date', 'start_time', 'end_time', 'created_at', 'updated_at'],
                'description': 'Exercise sessions with duration and calories burned'
            },
            'bodyweight_entries': {
                'filename': 'bodyweight_entries.csv',
                'date_columns': ['log_date', 'logged_at', 'created_at', 'updated_at'],
                'description': 'Body weight and body mass percentage measurements'
            },
            'transactions': {
                'filename': 'finance_transactions.csv',
                'date_columns': ['transaction_date', 'created_at', 'updated_at'],
                'description': 'Financial transactions (income and expenses)'
            },
            'net_worth_daily': {
                'filename': 'net_worth_daily.csv',
                'date_columns': ['snapshot_date', 'created_at'],
                'description': 'Daily net worth snapshots'
            }
        }

    def _load_json(self) -> Dict[str, Any]:
        """
        Load and parse the JSON file, and normalize it into the expected structure:
            {
              "version": "...",
              "exported_at": "...",
              "data": { ...categories... }
            }

        This method handles both old and new Swarmic export formats:
        - Old format: Direct structure with version, exported_at, and data
        - New format: Wrapped in success object with nested data structure

        Returns:
            Dict[str, Any]: Parsed and normalized JSON data

        Raises:
            json.JSONDecodeError: If JSON file is malformed
        """
        print(f"📂 Loading JSON file: {self.json_file_path}")
        try:
            with open(self.json_file_path, 'r', encoding='utf-8') as f:
                raw = json.load(f)

            # Handle newer Swarmic export shape:
            # {
            #   "success": true,
            #   "data": {
            #       "version": "...",
            #       "exported_at": "...",
            #       "data": { ... categories ... }
            #   }
            # }
            if isinstance(raw, dict) and "success" in raw and isinstance(raw.get("data"), dict):
                inner = raw["data"]
                if isinstance(inner, dict) and "data" in inner and isinstance(inner["data"], dict):
                    data = {
                        "version": inner.get("version"),
                        "exported_at": inner.get("exported_at"),
                        "data": inner["data"],
                    }
                else:
                    # Fallback: treat inner as already normalized
                    data = inner
            else:
                # Older / already-normalized exports
                data = raw

            print(f"✅ Successfully loaded JSON (version: {data.get('version', 'unknown')})")
            return data
        except json.JSONDecodeError as e:
            print(f"❌ Error parsing JSON file: {e}")
            raise

    def _format_dates(self, df: pd.DataFrame, date_columns: List[str]) -> pd.DataFrame:
        """
        Convert date columns to proper datetime format and create readable date strings.

        Args:
            df (pd.DataFrame): DataFrame to process
            date_columns (List[str]): List of column names containing dates

        Returns:
            pd.DataFrame: DataFrame with formatted date columns
        """
        for col in date_columns:
            if col in df.columns:
                # Convert to datetime
                df[col] = pd.to_datetime(df[col], errors='coerce')

                # Create human-readable version
                readable_col = f"{col}_readable"
                df[readable_col] = df[col].dt.strftime('%Y-%m-%d %H:%M:%S')

                # For date-only columns, create a simpler format
                if 'date' in col.lower() and not 'time' in col.lower():
                    df[col] = df[col].dt.date
                    df[readable_col] = df[col].astype(str) if not df[col].isna().all() else ''

        return df

    def _calculate_sleep_duration(self, df: pd.DataFrame) -> pd.DataFrame:
        """
        Calculate sleep duration in hours for sleep sessions.

        Args:
            df (pd.DataFrame): Sleep sessions DataFrame

        Returns:
            pd.DataFrame: DataFrame with added duration column
        """
        if 'sleep_time' in df.columns and 'wake_time' in df.columns:
            # Convert to datetime if not already
            df['sleep_time'] = pd.to_datetime(df['sleep_time'], errors='coerce')
            df['wake_time'] = pd.to_datetime(df['wake_time'], errors='coerce')

            # Calculate duration
            df['duration_hours'] = (df['wake_time'] - df['sleep_time']).dt.total_seconds() / 3600

            # Round to 2 decimal places
            df['duration_hours'] = df['duration_hours'].round(2)

            # Handle negative durations (sleep crossing midnight)
            df.loc[df['duration_hours'] < 0, 'duration_hours'] += 24

        return df

    def _add_financial_summaries(self, df: pd.DataFrame) -> pd.DataFrame:
        """
        Add income/expense classification for transactions.

        Args:
            df (pd.DataFrame): Transactions DataFrame

        Returns:
            pd.DataFrame: DataFrame with added classification
        """
        if 'amount' in df.columns:
            # Convert amount to numeric, handling string values
            df['amount'] = pd.to_numeric(df['amount'], errors='coerce')

            # Add transaction type based on positive/negative
            df['transaction_type'] = df['amount'].apply(
                lambda x: 'Income' if x > 0 else 'Expense' if x < 0 else 'Unknown'
            )

            # Add absolute amount
            df['amount_absolute'] = df['amount'].abs()

        return df

    def export_to_csv(self) -> Dict[str, str]:
        """
        Export all data categories to separate CSV files.

        Returns:
            Dict[str, str]: Dictionary mapping data type to output file path
        """
        # Check if data section exists
        if 'data' not in self.data:
            raise ValueError("Invalid JSON structure: 'data' section not found")

        exported_files = {}
        export_data = self.data['data']

        print(f"\n📊 Found {len(export_data)} data categories to export")

        # Progress bar for overall export process
        with tqdm(total=len(self.export_configs), desc="Exporting to CSV", unit="file") as pbar:

            for data_key, config in self.export_configs.items():
                # Update progress bar description
                pbar.set_description(f"Exporting {data_key}")

                if data_key in export_data and export_data[data_key]:
                    # Convert to DataFrame
                    df = pd.DataFrame(export_data[data_key])

                    # Get record count
                    record_count = len(df)

                    # Format date columns
                    if 'date_columns' in config:
                        df = self._format_dates(df, config['date_columns'])

                    # Apply specific processing based on data type
                    if data_key == 'sleep_sessions':
                        df = self._calculate_sleep_duration(df)
                    elif data_key == 'transactions':
                        df = self._add_financial_summaries(df)

                    # Sort by ID or date
                    if 'id' in df.columns:
                        df = df.sort_values('id')
                    elif any(col in df.columns for col in
                             ['session_date', 'log_date', 'transaction_date', 'snapshot_date']):
                        date_col = next(col for col in ['session_date', 'log_date', 'transaction_date', 'snapshot_date']
                                        if col in df.columns)
                        df = df.sort_values(date_col, ascending=False)

                    # Generate output file path
                    output_file = self.output_dir / config['filename']

                    # Export to CSV
                    df.to_csv(output_file, index=False, encoding='utf-8')

                    exported_files[data_key] = str(output_file)

                    # Update progress with details
                    tqdm.write(f"  ✅ {data_key}: {record_count} records → {config['filename']}")

                else:
                    tqdm.write(f"  ⚠️  {data_key}: No data found (skipped)")

                # Update progress bar
                pbar.update(1)

        return exported_files

    def generate_summary_report(self, exported_files: Dict[str, str]) -> None:
        """
        Generate a summary report of the export process.

        Args:
            exported_files (Dict[str, str]): Dictionary of exported file paths
        """
        print("\n" + "=" * 60)
        print("📈 EXPORT SUMMARY REPORT")
        print("=" * 60)

        # Original file info
        print(f"\n📂 Source File: {self.json_file_path}")
        print(f"📅 Export Date: {self.data.get('exported_at', 'Unknown')}")
        print(f"🔢 Version: {self.data.get('version', 'Unknown')}")

        # Export statistics
        print(f"\n📊 Export Statistics:")
        total_records = 0

        for data_key, config in self.export_configs.items():
            if data_key in self.data['data']:
                count = len(self.data['data'][data_key])
                total_records += count
                if count > 0:
                    print(f"  • {data_key}: {count:,} records")
                    print(f"    {config['description']}")

        print(f"\n📝 Total Records Exported: {total_records:,}")

        # Output files
        print(f"\n💾 Output Directory: {self.output_dir}")
        print("📄 Generated Files:")
        for data_key, filepath in exported_files.items():
            file_size = Path(filepath).stat().st_size / 1024  # Size in KB
            print(f"  • {Path(filepath).name} ({file_size:.1f} KB)")

        print("\n✅ Export completed successfully!")
        print("=" * 60)


def main():
    """
    Main function to handle command-line arguments and run the converter.
    """
    # Set up argument parser
    parser = argparse.ArgumentParser(
        description='Convert Swarmic JSON export to CSV files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python swarmic_json_to_csv.py swarmic_export_2025-10-24.json
  python swarmic_json_to_csv.py export.json ./csv_output
  python swarmic_json_to_csv.py ~/Downloads/swarmic_export.json ~/Documents/Swarmic/CSV
        """
    )

    parser.add_argument(
        'json_file',
        help='Path to the Swarmic JSON export file'
    )

    parser.add_argument(
        'output_dir',
        nargs='?',
        default=None,
        help='Output directory for CSV files (default: same as JSON file)'
    )

    parser.add_argument(
        '--no-summary',
        action='store_true',
        help='Skip the summary report after export'
    )

    # Parse arguments
    args = parser.parse_args()

    try:
        # Create converter instance
        print("🚀 Swarmic JSON to CSV Converter")
        print("=" * 60)

        converter = SwarmicJSONToCSVConverter(
            json_file_path=args.json_file,
            output_dir=args.output_dir
        )

        # Export to CSV files
        exported_files = converter.export_to_csv()

        # Generate summary report unless disabled
        if not args.no_summary:
            converter.generate_summary_report(exported_files)

    except FileNotFoundError as e:
        print(f"❌ Error: {e}")
        sys.exit(1)
    except ValueError as e:
        print(f"❌ Error: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"❌ Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)


if __name__ == "__main__":
    main()