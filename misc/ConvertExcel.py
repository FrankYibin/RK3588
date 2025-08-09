import pandas as pd
import argparse
import os
from pathlib import Path

def main():
    parser = argparse.ArgumentParser(description='Convert CSV to Excel using pandas')
    parser.add_argument('csv_file', nargs='?', default='output.csv', 
                       help='Input CSV file path (default: output.csv)')
    parser.add_argument('excel_file', nargs='?', default=None,
                       help='Output Excel file path (optional, auto-generated if not specified)')
    parser.add_argument('-o', '--output', 
                       help='Alternative way to specify output Excel file path')
    
    args = parser.parse_args()
    
    csv_file = args.csv_file
    
    # 确定输出文件名的优先级：命令行第二个参数 > -o选项 > 自动生成
    if args.excel_file:
        excel_file = args.excel_file
    elif args.output:
        excel_file = args.output
    else:
        # 从CSV文件名生成Excel文件名
        csv_path = Path(csv_file)
        excel_file = csv_path.with_suffix('.xlsx').name
    
    print("CSV to Excel Converter")
    print("=" * 30)
    
    if not os.path.exists(csv_file):
        print(f"Error: {csv_file} not found!")
        return
    
    file_size = os.path.getsize(csv_file)
    print(f"Input: {csv_file} ({file_size/1024:.1f} KB)")
    print(f"Output: {excel_file}")
    print()
    
    try:
        # 读取 CSV 文件
        df = pd.read_csv(csv_file)
        print(f"Loaded CSV: {df.shape[0]} rows × {df.shape[1]} columns")
        
        # 保存为 Excel 文件
        df.to_excel(excel_file, index=False)  # index=False 表示不保存行索引
        print(f"CSV文件已成功转换为Excel文件：{excel_file}")
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    main()
