import logging
from pathlib import Path
from typing import Optional

import pandas as pd

logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s")


def clean_dataset(df: pd.DataFrame) -> pd.DataFrame:
    """Clean dataset: handle NaNs, impute, convert types, cap outliers, and deduplicate."""
    df_clean = df.copy()

    # 2. Fill missing Calories with Mean
    if "Calories" in df_clean.columns:
        mean_calories = df_clean["Calories"].mean()
        df_clean["Calories"] = df_clean["Calories"].fillna(mean_calories)
        logging.info(f"Mean Calories ({mean_calories:.2f}) imputed in 'Calories' column.")

    # 3. Convert Date and drop invalid dates
    if "Date" in df_clean.columns:
        df_clean["Date"] = pd.to_datetime(df_clean["Date"], errors="coerce")
        df_clean.dropna(subset=["Date"], inplace=True)
        logging.info("Converted 'Date' to proper datetime format and dropped invalid rows.")

    # 4. Cap Outliers in 'Duration' (Max 120)
    if "Duration" in df_clean.columns:
        df_clean.loc[df_clean["Duration"] > 120, "Duration"] = 120
        logging.info("Outliers capped: Max 'Duration' set to 120 minutes.")

    # 5. Remove Duplicates
    duplicates_count = df_clean.duplicated().sum()
    df_clean.drop_duplicates(inplace=True)
    logging.info(f"Removed {duplicates_count} duplicate rows.")

    return df_clean


def main(file_path: str = "DataCleaning.csv") -> None:
    """Main execution of data cleaning."""
    print("=" * 50)
    print(" LAB 2: DATA PREPROCESSING - DATA CLEANING ")
    print("=" * 50)

    path = Path(file_path)
    if not path.exists():
        logging.error(f"'{file_path}' not found. Please ensure the dataset exists.")
        return

    # Load dataset
    try:
        df = pd.read_csv(path)
        logging.info("Original Dataset loaded:")
        print(df.head())
        print(f"Total rows: {len(df)}")
    except Exception as e:
        logging.error(f"Failed to load dataset: {e}")
        return

    # Clean dataset
    df_imputed = clean_dataset(df)

    logging.info("Fully Cleaned Dataset Preview:")
    print(df_imputed.head(10))
    print(f"Final Total rows: {len(df_imputed)}")


if __name__ == "__main__":
    main()
