import glob
import logging
import os
from pathlib import Path
from typing import List

import pandas as pd

logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s")


def load_and_align_data(file_pattern: str, read_func, file_type: str, common_cols: List[str], **kwargs) -> pd.DataFrame:
    """Read matching file, align columns, and append source metadata."""
    files = glob.glob(file_pattern)
    if not files:
        logging.warning(f"{file_type} file not found. Skipping {file_type} data load.")
        return pd.DataFrame()
        
    logging.info(f"Found {file_type} file: {files[0]}")
    try:
        df = read_func(files[0], **kwargs)
    except Exception as e:
        logging.error(f"Failed to read {file_type} file {files[0]}: {e}")
        return pd.DataFrame()

    missing_cols = [col for col in common_cols if col not in df.columns]
    if missing_cols:
         logging.warning(f"File {files[0]} is missing columns: {missing_cols}")
         return pd.DataFrame()

    df_aligned = df[common_cols].copy()
    df_aligned['Source'] = file_type
    return df_aligned


def main() -> None:
    """Main execution of data integration."""
    print("=" * 50)
    print(" LAB 3: DATA PREPROCESSING - DATA INTEGRATION ")
    print("=" * 50)

    common_cols = ['StockCode', 'Description', 'Quantity', 'UnitPrice', 'CustomerID', 'Country']
    dataframes = []

    # 1. Load Excel Data
    df_excel = load_and_align_data("*Online*.xlsx", pd.read_excel, "Excel", common_cols)
    if not df_excel.empty:
        dataframes.append(df_excel)

    # 2. Load CSV Data
    df_csv = load_and_align_data("*Online*.csv", pd.read_csv, "CSV", common_cols, encoding="unicode_escape")
    if not df_csv.empty:
        dataframes.append(df_csv)

    # 3. Integrate
    if not dataframes:
        logging.error("No datasets available to integrate.")
        return

    df_integrated = pd.concat(dataframes, ignore_index=True)
    df_integrated.drop_duplicates(inplace=True)

    logging.info("Integration Successful!")
    print(df_integrated.head(8))
    
    print(f"\nTotal rows integrated: {len(df_integrated)}")
    print(f"Unique customers count  : {df_integrated['CustomerID'].nunique()}")
    print(f"Unique countries count  : {df_integrated['Country'].nunique()}")
    
    # Simple analytics
    df_integrated['Revenue'] = df_integrated['Quantity'] * df_integrated['UnitPrice']
    revenue_by_country = df_integrated.groupby('Country')['Revenue'].sum().sort_values(ascending=False).head()
    print("\n[ANALYTICS] Top 5 Countries by Revenue:")
    print(revenue_by_country)


if __name__ == "__main__":
    main()
